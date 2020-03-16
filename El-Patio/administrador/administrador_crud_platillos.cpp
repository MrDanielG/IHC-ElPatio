#include "administrador_crud_platillos.h"
#include "ui_administrador_crud_platillos.h"
#include "administrador/admin_tarjeta_crud.h"
#include "models/platillo.h"

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
