#include "admin_tarjeta_crud.h"
#include "ui_admin_tarjeta_crud.h"
#include "administrador/administrador_crud_platillos.h"

admin_tarjeta_crud::admin_tarjeta_crud(Platillo platillo, administrador_crud_platillos *parent) :
    QWidget(parent),
    ui(new Ui::admin_tarjeta_crud)
{
    ui->setupUi(this);

    this->platillo = platillo;
    this->padre = parent;
    llenarTarjeta();
}

admin_tarjeta_crud::~admin_tarjeta_crud()
{
    delete ui;
}

void admin_tarjeta_crud::llenarTarjeta()
{
    QPixmap img(this->platillo.foto);
    ui->nombrePlatillo->setText(this->platillo.nombrePlatillo);
    ui->precioPlatillo->setText(this->platillo.precioPlatillo);
    ui->imgPlatillo->setPixmap(img);
}

void admin_tarjeta_crud::on_btnMasPlatillo_clicked()
{
    this->padre->getPlatilloTarjeta(this->platillo);
}
