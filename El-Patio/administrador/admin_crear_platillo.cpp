#include "admin_crear_platillo.h"
#include "ui_admin_crear_platillo.h"

#include <QDebug>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QFile>
#include <QFileDialog>

admin_crear_platillo::admin_crear_platillo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin_crear_platillo)
{
    ui->setupUi(this);
    conexionBD();
    actualizarDatos();
    ui->le_categoria->setHidden(true);
    ui->btn_canNueCategoria->setHidden(true);
}

void admin_crear_platillo::conexionBD()
{
    mDatabase = QSqlDatabase::database("Connection");
    if (!mDatabase.isOpen()){
        qDebug() << "ERROR con Base de Datos, esto es: CREAR PLATILLO";
        return;
    }
    else{
        qDebug() << "Base de datos continua abierta, esto es: CREAR PLATILLO";
    }
}

void admin_crear_platillo::actualizarDatos()
{
    QSqlQuery listaIngredientes(mDatabase);
    QSqlQuery listaCategoriaPaltillos(mDatabase);

    QString query = "select * from ingrediente order by nombre;";
    listaIngredientes.prepare(query);

    if(listaIngredientes.exec())
        qDebug() << "listaIngredientes [ejecutado] "    + query;
    else
        qDebug() << "listaIngredientes [no_ejecutado]"  + query;

    while (listaIngredientes.next())
        ui->list_ingreExistente->addItem(listaIngredientes.value("nombre").toString());

    QString qCategoria = "select categoria from platillo group by categoria;";
    listaCategoriaPaltillos.prepare(qCategoria);

    if(listaCategoriaPaltillos.exec())
        qDebug() << "listaCategoriaPaltillos [ejecutado] "    + qCategoria;
    else
        qDebug() << "listaCategoriaPaltillos [no_ejecutado]"  + qCategoria;

    ui->cb_categoria->addItem("Elige una Categoria");
    while (listaCategoriaPaltillos.next())
        ui->cb_categoria->addItem(listaCategoriaPaltillos.value("categoria").toString());

}

bool admin_crear_platillo::validarCampos()
{
    if(imgRuta == "" && ui->le_nombrePlatillo->text() == "" &&
            ui->le_precio->text() == "" && ui->te_descripcion->toPlainText() == "")
    {
        QMessageBox::warning(this, "Datos del Platillo", tr("Campos incompletos"));
        return false;
    }
    else return true;

}

admin_crear_platillo::~admin_crear_platillo()
{
    delete ui;
}

void admin_crear_platillo::on_list_ingreExistente_itemDoubleClicked(QListWidgetItem *item)
{
    ui->list_ingrePlatillo->addItem(item->text());
    ui->list_ingreExistente->removeItemWidget(item);
    item->~QListWidgetItem();
}

void admin_crear_platillo::on_list_ingrePlatillo_itemDoubleClicked(QListWidgetItem *item)
{
    ui->list_ingreExistente->addItem(item->text());
    ui->list_ingrePlatillo->removeItemWidget(item);
    item->~QListWidgetItem();
}

void admin_crear_platillo::on_btnCrearPlatillo_clicked()
{
    if (validarCampos()) {
        QSqlQuery insertarPlatillo(mDatabase);
        QSqlQuery ultimoId(mDatabase);
        QSqlQuery idIngrediente(mDatabase);
        QSqlQuery insertPlatiIngre(mDatabase);
        QString rutaImg;
        QString nombre;
        QString categoria;
        QString estado = "disponible";
        QString precio;

        QString idPlatillo;
        QString idIngre;

        rutaImg = imgRuta;
        nombre = ui->le_nombrePlatillo->text();
        if (ui->cb_categoria->currentText() != "Elige una Categoria")
            categoria = ui->cb_categoria->currentText();
        else
            categoria = ui->le_categoria->text();

        precio = ui->le_precio->text();


        QString query = "INSERT INTO platillo (precio, nombre, categoria, estado, foto)"
                        "VALUES ('"+precio+"', '"+nombre+"', '"+categoria+"', '"+estado+"', '"+rutaImg+"');";
        insertarPlatillo.prepare(query);

        if(insertarPlatillo.exec())
            qDebug() << "insertarPlatillo [ejecutado] "    + query;
        else
            qDebug() << "insertarPlatillo [no_ejecutado]"  + query;

        insertarPlatillo.next();

        QString qUltimoId = "select * from platillo order by id_platillo desc;";
        ultimoId.prepare(qUltimoId);

        if(ultimoId.exec())
            qDebug() << "ultimoId [ejecutado] "    + qUltimoId;
        else
            qDebug() << "ultimoId [no_ejecutado]"  + qUltimoId;
        ultimoId.next();

        idPlatillo = ultimoId.value("id_platillo").toString();


        int iterador = 0;
        while (ui->list_ingrePlatillo->item(iterador)) {
            //este regresa constante y takeItem() no lo retorna constante
            QString qIdPlatillo = "select * from ingrediente where nombre = '"+
                    ui->list_ingrePlatillo->item(iterador)->text()+"';";
            idIngrediente.prepare(qIdPlatillo);

            if(idIngrediente.exec())
                qDebug() << "idIngrediente [ejecutado] "    + qIdPlatillo;
            else
                qDebug() << "idIngrediente [no_ejecutado]"  + qIdPlatillo;

            idIngrediente.next();
            idIngre = idIngrediente.value("id_ingrediente").toString();

            //INSERT INTO `el_patio`.`lista_ingrediente` (`id_platillo`, `id_ingrediente`) VALUES ('123', '123');
            QString insertPlatilloIngrediente = "INSERT INTO `el_patio`.`lista_ingrediente` "
                                                "(`id_platillo`, `id_ingrediente`) VALUES "
                                                "('"+idPlatillo+"', '"+idIngre+"');";
            insertPlatiIngre.prepare(insertPlatilloIngrediente);
            if(insertPlatiIngre.exec())
                qDebug() << "insertPlatiIngre [ejecutado] "    + insertPlatilloIngrediente;
            else
                qDebug() << "insertPlatiIngre [no_ejecutado]"  + insertPlatilloIngrediente;
            insertPlatiIngre.next();

            iterador++;
        }

    }

}

void admin_crear_platillo::on_btn_siguiente_clicked()
{
    ui->sW_datosPlatillo->setCurrentIndex(1);
}

void admin_crear_platillo::on_btn_atras_clicked()
{
    ui->sW_datosPlatillo->setCurrentIndex(0);
}

void admin_crear_platillo::on_btn_nuevaCategoria_clicked()
{
    ui->cb_categoria->setHidden(true);
    ui->le_categoria->setHidden(false);
    ui->btn_nuevaCategoria->setHidden(true);
    ui->btn_canNueCategoria->setHidden(false);
}

void admin_crear_platillo::on_btn_canNueCategoria_clicked()
{
    ui->cb_categoria->setHidden(false);
    ui->le_categoria->setHidden(true);
    ui->btn_nuevaCategoria->setHidden(false);
    ui->btn_canNueCategoria->setHidden(true);
}

void admin_crear_platillo::on_btn_editarFoto_clicked()
{
    imgRuta = QFileDialog::getOpenFileName(
                this, "Selecciona imagen para el platillo", "..//..//", "Image Files (*.png *.jpg )");
    QFile file(imgRuta);
    file.open(QIODevice::ReadOnly);
    QByteArray arregloImg = file.readAll();
    QPixmap pix;
    pix.loadFromData(arregloImg);
    int w=ui->lb_fotografia->width();
    int h=ui->lb_fotografia->height();
    ui->lb_fotografia->setPixmap(pix.scaled(w,h,Qt::AspectRatioMode::KeepAspectRatio));
    file.close();
}
