#include "mesero_cambiar_cuenta_mesa.h"
#include "ui_mesero_cambiar_cuenta_mesa.h"

mesero_cambiar_cuenta_mesa::mesero_cambiar_cuenta_mesa(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mesero_cambiar_cuenta_mesa)
{
    ui->setupUi(this);
}

mesero_cambiar_cuenta_mesa::~mesero_cambiar_cuenta_mesa()
{
    delete ui;
}
