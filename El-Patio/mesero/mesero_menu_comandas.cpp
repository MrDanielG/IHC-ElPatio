#include "mesero_menu_comandas.h"
#include "ui_mesero_menu_comandas.h"
#include "QMessageBox"
#include "QDebug"
#include "QSqlQuery"
#include "mesero/mesero_tarjeta_menu.h"

mesero_menu_comandas::mesero_menu_comandas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mesero_menu_comandas)
{
    ui->setupUi(this);

    mDatabase = QSqlDatabase::database("Connection");
    if (!mDatabase.isOpen()){
        qDebug() << "ERROR con Base de Datos, esto es: MENU COMANDAS";
        return;
    }
    else{
        qDebug() << "Base de datos continua abierta, esto es: MENU COMANDAS";
    }

    actualizarCatalogo();
}

mesero_menu_comandas::~mesero_menu_comandas()
{
    delete ui;
}

void mesero_menu_comandas::actualizarCatalogo()
{
    QSqlQuery infoPlatillo(mDatabase);
    infoPlatillo.prepare("SELECT nombre, precio FROM `platillo` WHERE estado = 'disponible'");
    infoPlatillo.exec();
    limiparCatalogo();

    int i = 0;
    int row = 0;
    int col = 0;

    while (infoPlatillo.next())
    {
        QString id = infoPlatillo.value("nombre").toString();
        QString foto = infoPlatillo.value("precio").toString();
        QString nombrePlatillo = infoPlatillo.value("nombre").toString();
        QString precioPlatillo = infoPlatillo.value("precio").toString();

        //El numero de columnas en las que se dividira el grid
        row = i / 2;
        col = i % 2;

        mesero_tarjeta_menu *tarjeta = new mesero_tarjeta_menu(id, nombrePlatillo, precioPlatillo, foto, this);
        i++;
        ui->gridLayout->addWidget(tarjeta, row, col);
    }
}

void mesero_menu_comandas::limiparCatalogo()
{
    while (QLayoutItem *item = ui->gridLayout->takeAt(0))
    {
        Q_ASSERT(!item->layout());
        delete item->widget();
        delete item;
    }
}
