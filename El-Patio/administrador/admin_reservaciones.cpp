#include "admin_reservaciones.h"
#include "ui_admin_reservaciones.h"

admin_reservaciones::admin_reservaciones(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin_reservaciones)
{
    ui->setupUi(this);
}

admin_reservaciones::~admin_reservaciones()
{
    delete ui;
}
