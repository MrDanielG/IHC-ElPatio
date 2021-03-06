#include "admin_edita_platillo.h"
#include "ui_admin_edita_platillo.h"
#include "QFile"
#include "QFileDialog"
#include "QDebug"
#include "QPixmap"
#include "QMessageBox"

admin_edita_platillo::admin_edita_platillo(Platillo platillo, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin_edita_platillo)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);
    ui->le_categoria->setHidden(true);
    ui->btn_canNueCategoria->setHidden(true);

    this->platillo = platillo;
    conexionBD();
    infoPlatilloDB();
    llenarInfo();
}

admin_edita_platillo::~admin_edita_platillo()
{
    delete ui;
}

void admin_edita_platillo::conexionBD()
{
    mDatabase = QSqlDatabase::database("Connection");
    if (!mDatabase.isOpen()){
        qDebug() << "ERROR con Base de Datos, esto es: EDITAR PLATILLO";
        return;
    } else{
        qDebug() << "Base de datos continua abierta, esto es: EDITAR PLATILLO";
    }
}

void admin_edita_platillo::llenarInfo()
{
    ui->le_nombrePlatillo->setText(this->platillo.nombrePlatillo);
    ui->spinBoxPrecio->setValue(this->platillo.precioPlatillo.toInt());
    //ui->cb_categoria->setCurrentText(this->platillo.categoria);
    llenarCategorias();
    llenarIngredientes();

    QPixmap imgPlato(this->platillo.foto);
    ui->lb_fotografia->setPixmap(imgPlato);
}

void admin_edita_platillo::infoPlatilloDB()
{
    QSqlQuery infoPlatillo(mDatabase);
    infoPlatillo.prepare("SELECT * FROM `platillo` WHERE id_platillo = " + this->platillo.id);

    if(infoPlatillo.exec()){
        infoPlatillo.next();

        this->platillo.nombrePlatillo = infoPlatillo.value("nombre").toString();
        this->platillo.precioPlatillo = infoPlatillo.value("precio").toString();
        this->platillo.categoria = infoPlatillo.value("categoria").toString();
        this->platillo.estado = infoPlatillo.value("estado").toString();
        this->platillo.foto = infoPlatillo.value("foto").toString();
    } else {
        qDebug()<<"Fallo Query infoPlatillo";
    }
}

void admin_edita_platillo::llenarCategorias()
{
    QSqlQuery listaCategoriaPaltillos(mDatabase);
    QString qCategoria = "SELECT categoria FROM platillo GROUP BY categoria;";
    listaCategoriaPaltillos.prepare(qCategoria);

    if(listaCategoriaPaltillos.exec()){
        while (listaCategoriaPaltillos.next())
            ui->cb_categoria->addItem(listaCategoriaPaltillos.value("categoria").toString());

        ui->cb_categoria->setCurrentText(this->platillo.categoria);
    } else {
        qDebug()<<"Query categorias FAIL";
    }
}

void admin_edita_platillo::llenarIngredientes()
{
    Ingrediente ingrediente;
    QSqlQuery listaIngredientesPlatillo(mDatabase);
    QString query2 = "SELECT * FROM `lista_ingrediente` INNER JOIN ingrediente ON "
                    " ingrediente.id_ingrediente = lista_ingrediente.id_ingrediente WHERE lista_ingrediente.id_platillo = " + this->platillo.id;
    listaIngredientesPlatillo.prepare(query2);

    if(listaIngredientesPlatillo.exec()){
        while (listaIngredientesPlatillo.next()){
            ingrediente.idIngrediente = listaIngredientesPlatillo.value("id_ingrediente").toString();
            ingrediente.nombreIngrediente = listaIngredientesPlatillo.value("nombre").toString();
            listaIngPlatillo.append(ingrediente);
            ui->list_ingrePlatillo->addItem(listaIngredientesPlatillo.value("nombre").toString());
        }
    } else {
        qDebug()<<"listaIngredientesPlatillo FAIL";
    }

    QSqlQuery listaIngredientes(mDatabase);
    QString query = "SELECT * FROM ingrediente ORDER BY nombre;";
    listaIngredientes.prepare(query);

    if(listaIngredientes.exec()){
        while (listaIngredientes.next()){
            ingrediente.idIngrediente = listaIngredientes.value("id_ingrediente").toString();
            ingrediente.nombreIngrediente = listaIngredientes.value("nombre").toString();
            listaIngGeneral.append(ingrediente);
        }
    } else {
        qDebug()<<"listaIngredientes FAIL";
    }

    //Elimina ingredientes repetidos de la Lista General
    foreach (Ingrediente ing, listaIngPlatillo) {
        if(listaIngGeneral.contains(ing)){
            listaIngGeneral.removeAll(ing);
        }
    }

    //Llena la lista
    foreach (Ingrediente ing, listaIngGeneral) {
        ui->list_ingreExistente->addItem(ing.nombreIngrediente);
    }

}

void admin_edita_platillo::updatePlatillo()
{
   QSqlQuery updatePlatillo(mDatabase);
   updatePlatillo.prepare("UPDATE `platillo` SET `precio`= '"+this->platillo.precioPlatillo+"' ,"
                                                "`nombre`= '"+this->platillo.nombrePlatillo+"',"
                                                "`categoria`= '"+this->platillo.categoria+"',"
                                                "`estado`= '"+this->platillo.estado+"',"
                                                "`foto`= '"+this->platillo.foto+"' "
                                                " WHERE id_platillo = " + this->platillo.id);

   if(updatePlatillo.exec()){
       qDebug()<<"Update Platillo Query DONE";
   } else {
       qDebug()<<"Update Platillo Query FAIL";
   }

   updateIngredientesPlatillo();
}

void admin_edita_platillo::updateIngredientesPlatillo()
{
    //Elimina TODOS los ingredientes del plato
    QSqlQuery deleteIngredientes(mDatabase);
    deleteIngredientes.prepare("DELETE FROM `lista_ingrediente` WHERE id_platillo = " + this->platillo.id);
    qDebug()<<"PRERRR Delete Ingredientes";

    if(deleteIngredientes.exec()){
        qDebug()<<"Delete Ingredientes DONE";
    } else {
        qDebug()<<"Delete Ingredientes FAIL";
    }

    //Inserta los nuevos ingredientes
    QSqlQuery insertIngredientes(mDatabase);

    foreach (Ingrediente ing, listaIngPlatillo) {
        insertIngredientes.prepare("INSERT INTO `lista_ingrediente`( `id_platillo`, `id_ingrediente`) "
                           "VALUES ('"+this->platillo.id+"','"+ing.idIngrediente+"')");

        if(insertIngredientes.exec()){
            qDebug()<<"INSERT Ingredientes DONE";

        } else {
            qDebug()<<"INSERT Ingredientes FAIL";
        }
    }

    QMessageBox msgBox(QMessageBox::Information,tr("Éxito"), tr("Se Actualizo el Platillo"), QMessageBox::Yes);
    msgBox.setButtonText(QMessageBox::Yes, tr("Entendido"));
    msgBox.exec();
}

void admin_edita_platillo::on_btn_siguiente_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void admin_edita_platillo::on_btn_atras_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void admin_edita_platillo::on_btnCancelar_2_clicked()
{
    this->close();
}

void admin_edita_platillo::on_btn_editarFoto_clicked()
{
    platillo.foto = QFileDialog::getOpenFileName(
                this, "Selecciona imagen para el platillo", "..//..//", "Image Files (*.png *.jpg )");
    QFile file(platillo.foto);
    file.open(QIODevice::ReadOnly);
    QByteArray arregloImg = file.readAll();
    QPixmap pix;
    pix.loadFromData(arregloImg);
    int w = ui->lb_fotografia->width();
    int h = ui->lb_fotografia->height();
    ui->lb_fotografia->setPixmap(pix.scaled(w,h,Qt::AspectRatioMode::KeepAspectRatio));
    file.close();
}

void admin_edita_platillo::on_list_ingreExistente_itemDoubleClicked(QListWidgetItem *item)
{
    Ingrediente ingTemp;
    QSqlQuery infoIngrediente(mDatabase);
    infoIngrediente.prepare("SELECT * FROM `ingrediente` WHERE nombre = '" +item->text()+ "'");
    infoIngrediente.exec();
    infoIngrediente.next();
    ingTemp.idIngrediente = infoIngrediente.value("id_ingrediente").toString();
    ingTemp.nombreIngrediente = infoIngrediente.value("nombre").toString();

    ui->list_ingrePlatillo->addItem(ingTemp.nombreIngrediente);
    this->listaIngPlatillo.append(ingTemp);

    ui->list_ingreExistente->removeItemWidget(item);
    this->listaIngGeneral.removeAll(ingTemp);

    item->~QListWidgetItem();
}

void admin_edita_platillo::on_list_ingrePlatillo_itemDoubleClicked(QListWidgetItem *item)
{
    Ingrediente ingTemp;
    QSqlQuery infoIngrediente(mDatabase);
    infoIngrediente.prepare("SELECT * FROM `ingrediente` WHERE nombre = '" +item->text()+ "'");
    infoIngrediente.exec();
    infoIngrediente.next();
    ingTemp.idIngrediente = infoIngrediente.value("id_ingrediente").toString();
    ingTemp.nombreIngrediente = infoIngrediente.value("nombre").toString();

    ui->list_ingreExistente->addItem(ingTemp.nombreIngrediente);
    this->listaIngGeneral.append(ingTemp);

    ui->list_ingrePlatillo->removeItemWidget(item);
    this->listaIngPlatillo.removeAll(ingTemp);

    item->~QListWidgetItem();
}

void admin_edita_platillo::on_btnActualizar_clicked()
{
    QMessageBox msgBox2(QMessageBox::Question,"Confimacion","¿Desea Actualizar éste Platillo?",QMessageBox::Yes|QMessageBox::No);
    msgBox2.setButtonText(QMessageBox::Yes,"Sí");
    msgBox2.setButtonText(QMessageBox::No,"No");

    if(msgBox2.exec()==QMessageBox::Yes){
        updatePlatillo();
    } else {
        QMessageBox msgBox(QMessageBox::Information,tr("Cancelación"), tr("NO se Actualizo el Platillo"), QMessageBox::Yes);
        msgBox.setButtonText(QMessageBox::Yes, tr("Entendido"));
        msgBox.exec();
    }

    this->close();
}

void admin_edita_platillo::on_le_nombrePlatillo_textChanged(const QString &arg1)
{
    this->platillo.nombrePlatillo = arg1;
}

void admin_edita_platillo::on_spinBoxPrecio_valueChanged(const QString &arg1)
{
    this->platillo.precioPlatillo = arg1;
}

void admin_edita_platillo::on_cb_categoria_activated(const QString &arg1)
{
    this->platillo.categoria = arg1;
}

void admin_edita_platillo::on_btn_nuevaCategoria_clicked()
{
    ui->cb_categoria->setHidden(true);
    ui->le_categoria->setHidden(false);
    ui->btn_nuevaCategoria->setHidden(true);
    ui->btn_canNueCategoria->setHidden(false);
}

void admin_edita_platillo::on_btn_canNueCategoria_clicked()
{
    ui->cb_categoria->setHidden(false);
    ui->le_categoria->setHidden(true);
    ui->btn_nuevaCategoria->setHidden(false);
    ui->btn_canNueCategoria->setHidden(true);
    this->platillo.categoria = ui->cb_categoria->currentText();
}

void admin_edita_platillo::on_le_categoria_textChanged(const QString &arg1)
{
    this->platillo.categoria = arg1;
}
