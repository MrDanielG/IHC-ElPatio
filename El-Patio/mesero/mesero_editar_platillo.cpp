#include "mesero_editar_platillo.h"
#include "ui_mesero_editar_platillo.h"
#include "mesero_tarjeta_extra.h"
#include "mesero/mesero_tarjeta_extra_chica.h"
#include "models/extra.h"

#include "QDebug"

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

void mesero_editar_platillo::actualizarSideBar(extra _extraPlatillo, int operacion)
{
    if(this->listaExtras.contains(_extraPlatillo)){

        int Index = this->listaExtras.indexOf(_extraPlatillo);
        int sum = this->listaExtras.at(Index).cantidad;

        if(operacion > 0){
            sum++;
        }
        else{
            sum--;
        }

        if(sum == 0){
            this->listaExtras.removeAt(Index);
            while (QLayoutItem *item = ui->gridLayoutExtras->takeAt(0))
            {
                Q_ASSERT(!item->layout());
                delete item->widget();
                delete item;
            }
            actualizarSB();
            actualizarCatalogo();
        }
        else{
            extra Nuevo = this->listaExtras.at(Index);
            Nuevo.setCantidad(sum);
            this->listaExtras.replace(Index, Nuevo);
            actualizarSB();
        }
    }
    else{
        this->listaExtras.append(_extraPlatillo);
        actualizarSB();
    }
}

void mesero_editar_platillo::actualizarSB()
{
    int iterador = 0;
    int row = 0;
    int col = 0;

    for (int i = 0; i < this->listaExtras.size(); ++i) {

//        QString id = this->listaExtras[i].idExtra;
//        QString nombrePlatillo = this->listaExtras[i].nombre;
//        QString precioPlatillo = this->listaExtras[i].precio;
//        int cantidad = this->listaExtras[i].cantidad;

        row = iterador / 1;
        col = iterador % 1;

        mesero_tarjeta_extra_chica *tarjeta = new mesero_tarjeta_extra_chica(listaExtras[i], this);
        iterador++;
        ui->gridLayoutExtras->addWidget(tarjeta, row, col);
    }
}

QList<extra> mesero_editar_platillo::getExtras()
{
    return this->listaExtras;
}

void mesero_editar_platillo::on_btnCancelar_clicked()
{
    this->close();
}

void mesero_editar_platillo::on_btnConfirmar_clicked()
{
    this->hide();
}
