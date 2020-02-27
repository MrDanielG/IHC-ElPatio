#include "admin_tarjeta_usuario.h"
#include "ui_admin_tarjeta_usuario.h"

admin_tarjeta_usuario::admin_tarjeta_usuario(QString id, QString nombre, QString paterno,
                                             QString materno, QString tipo, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admin_tarjeta_usuario)
{
    ui->setupUi(this);

    ui->nombreUsuario->setText(nombre + " " + paterno + " " + materno);
    ui->tipoUsuario->setText("Puesto: " + tipo);
}

admin_tarjeta_usuario::~admin_tarjeta_usuario()
{
    delete ui;
}
