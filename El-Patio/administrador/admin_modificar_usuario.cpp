#include "admin_modificar_usuario.h"
#include "ui_admin_modificar_usuario.h"

admin_modificar_usuario::admin_modificar_usuario(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin_modificar_usuario)
{
    ui->setupUi(this);
}

admin_modificar_usuario::~admin_modificar_usuario()
{
    delete ui;
}
