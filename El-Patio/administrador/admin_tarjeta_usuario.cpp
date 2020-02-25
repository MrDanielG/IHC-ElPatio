#include "admin_tarjeta_usuario.h"
#include "ui_admin_tarjeta_usuario.h"

admin_tarjeta_usuario::admin_tarjeta_usuario(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admin_tarjeta_usuario)
{
    ui->setupUi(this);
}

admin_tarjeta_usuario::~admin_tarjeta_usuario()
{
    delete ui;
}
