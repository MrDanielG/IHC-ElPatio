#include "mesero_editar_platillo.h"
#include "ui_mesero_editar_platillo.h"
#include "mesero_tarjeta_extra.h"

#include "QDebug"

#include "models/extra.h"

mesero_editar_platillo::mesero_editar_platillo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mesero_editar_platillo)
{
    ui->setupUi(this);

    conexionBD();
    actualizarCatalogo();
//    ui->stackedWidget->insertWidget(1, &agregarExtra);
//    ui->stackedWidget->setCurrentIndex(1);
}

mesero_editar_platillo::~mesero_editar_platillo()
{
    delete ui;
}

void mesero_editar_platillo::conexionBD()
{
    mDatabase = QSqlDatabase::database("Connection");
    if (!mDatabase.isOpen()){
        qDebug() << "ERROR con Base de Datos, esto es: EDITAR PLATILLO";
        return;
    }
    else{
        qDebug() << "Base de datos continua abierta, esto es: EDITAR PLATILLO";
    }
}

void mesero_editar_platillo::actualizarCatalogo()
{
    QSqlQuery infoExtra(mDatabase);
    infoExtra.prepare("SELECT * FROM `extra`");
    infoExtra.exec();

    limiparCatalogo();

    int i = 0;
    int row = 0;
    int col = 0;

    while (infoExtra.next())
    {
        QString idExtra = infoExtra.value("id_extra").toString();
        QString nombreExtra = infoExtra.value("nombre").toString();
        QString precioExtra = infoExtra.value("precio").toString();

        extra extraPlatillo(idExtra, nombreExtra, precioExtra);

        row = i / 1;
        col = i % 1;

        mesero_tarjeta_extra *tarjeta =
                new mesero_tarjeta_extra(extraPlatillo, this);
        i++;
        ui->gridLayout->addWidget(tarjeta, row, col);
    }
}

void mesero_editar_platillo::limiparCatalogo()
{
    while (QLayoutItem *item = ui->gridLayout->takeAt(0))
    {
        Q_ASSERT(!item->layout());
        delete item->widget();
        delete item;
    }
}
