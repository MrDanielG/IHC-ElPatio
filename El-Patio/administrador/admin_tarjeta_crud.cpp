#include "admin_tarjeta_crud.h"
#include "ui_admin_tarjeta_crud.h"

admin_tarjeta_crud::admin_tarjeta_crud(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admin_tarjeta_crud)
{
    ui->setupUi(this);
}

admin_tarjeta_crud::~admin_tarjeta_crud()
{
    delete ui;
}
