#include "admin_tarjeta_crud.h"
#include "ui_admin_tarjeta_crud.h"

admin_tarjeta_crud::admin_tarjeta_crud(Platillo platillo, administrador_crud_platillos *parent = nullptr) :
    QWidget(parent),
    ui(new Ui::admin_tarjeta_crud)
{
    ui->setupUi(this);

    this->platillo = platillo;
    this->padre = parent;
}

admin_tarjeta_crud::~admin_tarjeta_crud()
{
    delete ui;
}
