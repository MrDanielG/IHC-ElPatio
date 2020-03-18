#include "admin_edita_platillo.h"
#include "ui_admin_edita_platillo.h"
#include "QFile"
#include "QFileDialog"
#include "QDebug"
#include "QPixmap"

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

    //Llenar lista de Ingredientes
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

    QList<QString> ingPlatillos;
    QList<QString> ingGeneral;

    QSqlQuery listaIngredientesPlatillo(mDatabase);
    QString query2 = "SELECT * FROM `lista_ingrediente` INNER JOIN ingrediente ON "
                    " ingrediente.id_ingrediente = lista_ingrediente.id_ingrediente WHERE lista_ingrediente.id_platillo = " + this->platillo.id;
    listaIngredientesPlatillo.prepare(query2);

    if(listaIngredientesPlatillo.exec()){
        while (listaIngredientesPlatillo.next()){
            ui->list_ingrePlatillo->addItem(listaIngredientesPlatillo.value("nombre").toString());
            ingPlatillos.append(listaIngredientesPlatillo.value("nombre").toString());
        }
    }

    QSqlQuery listaIngredientes(mDatabase);
    QString query = "SELECT * FROM ingrediente ORDER BY nombre;";
    listaIngredientes.prepare(query);

    if(listaIngredientes.exec()){
        while (listaIngredientes.next()){
            ingGeneral.append(listaIngredientes.value("nombre").toString());
            //ui->list_ingreExistente->addItem(listaIngredientes.value("nombre").toString());
        }
    }

    //Elimina ingredientes repetidos
    foreach (QString ingrediente, ingPlatillos) {
        if(ingGeneral.contains(ingrediente)){
            ingGeneral.removeAll(ingrediente);
        }
    }

    //Llena la lista
    foreach (QString ingrediente, ingGeneral) {
        ui->list_ingreExistente->addItem(ingrediente);
    }

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

void admin_edita_platillo::on_btnCancelar2_clicked()
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
