#include "mesero_tarjeta_chica.h"
#include "ui_mesero_tarjeta_chica.h"

#include <QSqlQuery>
#include <QDebug>
#include <QSqlRecord>

mesero_tarjeta_chica::mesero_tarjeta_chica(QString id, QString nombrePlatillo, QString precioPlatillo, QString foto, int cantidad, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mesero_tarjeta_chica)
{
    ui->setupUi(this);

    this->id = id;
    this->nombrePlatillo = nombrePlatillo;
    this->precioPlatillo = precioPlatillo;
    this->foto = foto;
    this->cantidad = cantidad;

    llenarTarjeta();
}

mesero_tarjeta_chica::mesero_tarjeta_chica(int id_platillo, QWidget *parent):
    QWidget(parent),
    ui(new Ui::mesero_tarjeta_chica)
{
    ui->setupUi(this);

    mDatabase = QSqlDatabase::database("Connection");
       if(!mDatabase.isOpen()){
           qDebug() << "ERROR, tarjeta platillo";
       }else {
           qDebug() << "conexion exitosa desde tarjeta_platillo";
       }

       this->id = QString::number(id_platillo);

       QSqlQuery datos_platillo(mDatabase);
       QString query_datos_platillo = "select * from platillo where id_platillo = " + this->id + ";";

       datos_platillo.exec(query_datos_platillo);
       datos_platillo.next();

    this->nombrePlatillo = datos_platillo.record().value("nombre").toString();
    this->precioPlatillo = datos_platillo.record().value("precio").toString();
    this->foto = datos_platillo.record().value("foto").toString();
    this->cantidad = 1;

    llenarTarjeta();
}

mesero_tarjeta_chica::~mesero_tarjeta_chica()
{
    delete ui;
}

void mesero_tarjeta_chica::llenarTarjeta()
{
    QPixmap img(this->foto);
    ui->nombrePlatillo->setText(this->nombrePlatillo);
    ui->precioPlatillo->setText("$ " + this->precioPlatillo);
    ui->cantidad->setText(QString::number(this->cantidad));
    ui->imgPlatillo->setPixmap(img);
}

float mesero_tarjeta_chica::get_precio()
{
    return this->precioPlatillo.toFloat();
}
