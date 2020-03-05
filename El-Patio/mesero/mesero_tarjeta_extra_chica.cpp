#include "mesero_tarjeta_extra_chica.h"
#include "ui_mesero_tarjeta_extra_chica.h"
#include "mesero/mesero_editar_platillo.h"

mesero_tarjeta_extra_chica::mesero_tarjeta_extra_chica(extra _extraPlatillo,mesero_editar_platillo *parent) :
    QWidget(parent),
    ui(new Ui::mesero_tarjeta_extra_chica)
{
    ui->setupUi(this);

    this->padre = parent;
    this->extraPlatillo = _extraPlatillo;
    llenarTarjeta();
}

mesero_tarjeta_extra_chica::~mesero_tarjeta_extra_chica()
{
    delete ui;
}

void mesero_tarjeta_extra_chica::llenarTarjeta()
{
    ui->nombreExtra->setText(this->extraPlatillo.nombre);
    ui->precioExtra->setText("$" + this->extraPlatillo.precio);
    ui->cantidad->setText(QString::number(this->extraPlatillo.cantidad));
}
