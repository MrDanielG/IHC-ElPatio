#include "admin_gestion_usuarios.h"
#include "ui_admin_gestion_usuarios.h"

admin_gestion_usuarios::admin_gestion_usuarios(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admin_gestion_usuarios)
{
    ui->setupUi(this);
}

admin_gestion_usuarios::~admin_gestion_usuarios()
{
    delete ui;
}
