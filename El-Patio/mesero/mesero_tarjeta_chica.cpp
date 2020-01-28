#include "mesero_tarjeta_chica.h"
#include "ui_mesero_tarjeta_chica.h"

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
