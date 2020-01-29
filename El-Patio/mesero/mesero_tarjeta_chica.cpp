#include "mesero_tarjeta_chica.h"
#include "ui_mesero_tarjeta_chica.h"

#include <QSqlQuery>
#include <QDebug>
#include <QSqlRecord>

mesero_tarjeta_chica::mesero_tarjeta_chica(int _id_platillo, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mesero_tarjeta_chica)
{
    mDatabase = QSqlDatabase::database("Connection");
    if(!mDatabase.isOpen()){
        qDebug() << "ERROR, tarjeta platillo";
    }else {
        qDebug() << "conexion exitosa desde tarjeta_platillo";
    }
    ui->setupUi(this);
    ui->setupUi(this);

    this->id_platillo = _id_platillo;

    QSqlQuery datos_platillo(mDatabase);
    QString query_datos_platillo = "select * from platillo where id_platillo = " + QString::number(this->id_platillo) + ";";

    datos_platillo.exec(query_datos_platillo);
    datos_platillo.next();
    qDebug() << datos_platillo.record().value("id_platillo").toString();

    this->nombre = datos_platillo.record().value("nombre").toString();
    this->precio = datos_platillo.record().value("precio").toFloat();

    ui->nombrePlatillo_3->setText(this->nombre);
    QString precio;
    precio.setNum(this->precio);
    ui->precioPlatillo_3->setText("$"+precio);
    ui->imgPlatillo_3->pixmap();

}

float mesero_tarjeta_chica::get_precio()
{
    return this->precio;
}

mesero_tarjeta_chica::~mesero_tarjeta_chica()
{
    delete ui;
}
