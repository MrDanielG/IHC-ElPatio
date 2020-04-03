#include "administrador_crud_platillos.h"
#include "ui_administrador_crud_platillos.h"
#include "administrador/admin_tarjeta_crud.h"
#include "models/platillo.h"
#include "administrador/admin_crear_platillo.h"
#include "administrador/admin_edita_platillo.h"

#include "QMessageBox"
#include "QDebug"
#include "QSqlQuery"

administrador_crud_platillos::administrador_crud_platillos(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::administrador_crud_platillos)
{
    ui->setupUi(this);

    conexionBD();
    actualizarCatalogo();
}

administrador_crud_platillos::~administrador_crud_platillos()
{
    delete ui;
}

void administrador_crud_platillos::conexionBD()
{
    mDatabase = QSqlDatabase::database("Connection");
    if (!mDatabase.isOpen()){
        qDebug() << "ERROR con Base de Datos, esto es: CRUD PLATILLOS";
        return;
    } else{
        qDebug() << "Base de datos continua abierta, esto es: CRUD PLATILLOS";
    }
}

void administrador_crud_platillos::actualizarCatalogo()
{
    QSqlQuery infoPlatillo(mDatabase);
    infoPlatillo.prepare("SELECT * FROM `platillo` WHERE estado = 'disponibles'");
    infoPlatillo.exec();
    limiparCatalogo();

    int i = 0;
    int row = 0;
    int col = 0;

    Platillo platoTarjeta;

    while (infoPlatillo.next())
    {
        platoTarjeta.id = infoPlatillo.value("id_platillo").toString();
        platoTarjeta.foto = infoPlatillo.value("foto").toString();
        platoTarjeta.nombrePlatillo = infoPlatillo.value("nombre").toString();
        platoTarjeta.precioPlatillo = infoPlatillo.value("precio").toString();
        platoTarjeta.categoria = infoPlatillo.value("categoria").toString();
        platoTarjeta.estado = infoPlatillo.value("estado").toString();

        //El numero de columnas en las que se dividira el grid
        row = i / 2;
        col = i % 2;

        admin_tarjeta_crud *tarjeta =
                new admin_tarjeta_crud(platoTarjeta, this);
        i++;
        ui->gridLayout->addWidget(tarjeta, row, col);
    }
}

void administrador_crud_platillos::limiparCatalogo()
{
    while (QLayoutItem *item = ui->gridLayout->takeAt(0))
    {
        Q_ASSERT(!item->layout());
        delete item->widget();
        delete item;
    }
}

void administrador_crud_platillos::getPlatilloTarjeta(Platillo platillo)
{
    this->platilloTemporal = platillo;
    infoPlatillo();
}

void administrador_crud_platillos::infoPlatillo()
{
    ui->nombrePlatillo->setText(this->platilloTemporal.nombrePlatillo);
    ui->categoriaPlatillo->setText(this->platilloTemporal.categoria);
    ui->precioPlatillo->setText("$" + this->platilloTemporal.precioPlatillo);
    ui->estadoPlatillo->setText("Estado: " + this->platilloTemporal.estado);
    listaIngredientes();
}

void administrador_crud_platillos::listaIngredientes()
{
    QSqlQuery ingredientes(mDatabase);
    ingredientes.prepare("SELECT ingrediente.id_ingrediente, ingrediente.nombre FROM ingrediente INNER JOIN lista_ingrediente ON ingrediente.id_ingrediente = lista_ingrediente.id_ingrediente INNER JOIN platillo ON platillo.id_platillo = lista_ingrediente.id_platillo WHERE platillo.id_platillo = " + this->platilloTemporal.id);
    ingredientes.exec();
    limpiarIngredientes();

    int i = 0;
    int row = 0;
    int col = 0;

    QString estilo = "color: rgb(133, 133, 133);";
    QFont fuente("Roboto",12,-2,false);

    while (ingredientes.next())
    {
        QString nombreIngrediente = ingredientes.value("nombre").toString();

        //El numero de columnas en las que se dividira el grid
        row = i / 1;
        col = i % 1;

        QLabel *label = new QLabel(this);
        label->setText(nombreIngrediente);
        label->setStyleSheet(estilo);
        label->setFont(fuente);

        i++;
        ui->gridIngredientes->addWidget(label, row, col);
    }
}

void administrador_crud_platillos::limpiarIngredientes()
{
    while (QLayoutItem *item = ui->gridIngredientes->takeAt(0))
    {
        Q_ASSERT(!item->layout());
        delete item->widget();
        delete item;
    }
}

void administrador_crud_platillos::on_btnCrearPlatillo_clicked()
{
//    admin_crear_usuario crearUsuario;
//    crearUsuario.exec();
//    actualizarCatalogo(auxTipoUsuario);
    admin_crear_platillo crearPlatillo;
    crearPlatillo.exec();
}

void administrador_crud_platillos::on_btnEditarPlatillo_clicked()
{
    admin_edita_platillo editarPlatillo(this->platilloTemporal, this);
    editarPlatillo.exec();
    actualizarCatalogo();
    getPlatilloTarjeta(editarPlatillo.platillo);
}
