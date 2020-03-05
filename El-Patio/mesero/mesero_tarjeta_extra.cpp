#include "mesero_tarjeta_extra.h"
#include "ui_mesero_tarjeta_extra.h"
#include "mesero/mesero_editar_platillo.h"

mesero_tarjeta_extra::mesero_tarjeta_extra(extra extraPlatillo, mesero_editar_platillo *parent) :
    QWidget(parent),
    ui(new Ui::mesero_tarjeta_extra)
{
    ui->setupUi(this);

    this->extraPlatillo = extraPlatillo;
    this->padre = parent;
    llenarTarjeta();
}

mesero_tarjeta_extra::~mesero_tarjeta_extra()
{
    delete ui;
}

void mesero_tarjeta_extra::llenarTarjeta()
{
    ui->nombreExtra->setText(this->extraPlatillo.nombre);
    ui->precioExtra->setText("$" + this->extraPlatillo.precio);
}

void mesero_tarjeta_extra::on_btnMasExtra_clicked()
{
    this->extraPlatillo.cantidad++;
    this->padre->actualizarSideBar(this->extraPlatillo, 1);
    ui->btnMasExtra->setEnabled(false);
}
