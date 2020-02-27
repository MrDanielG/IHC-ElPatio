#include "admin_tarjeta_usuario.h"
#include "ui_admin_tarjeta_usuario.h"
#include "administrador/admin_gestion_usuarios.h"
#include "QDebug"
admin_tarjeta_usuario::admin_tarjeta_usuario(QString id, QString nombre, QString paterno,
                                             QString materno, QString tipo, admin_gestion_usuarios *parent) :
    QWidget(parent),
    ui(new Ui::admin_tarjeta_usuario)
{
    ui->setupUi(this);
    this->padre = parent;
    this->claveUsuario = id;
    ui->nombreUsuario->setText(nombre + " " + paterno + " " + materno);
    ui->tipoUsuario->setText("Puesto: " + tipo);
}

admin_tarjeta_usuario::~admin_tarjeta_usuario()
{
    delete ui;
}

void admin_tarjeta_usuario::on_label_linkActivated(const QString &link)
{
    qDebug()<<"le picaste we";
}

void admin_tarjeta_usuario::on_btnEdit_clicked()
{
    this->padre->userSideBar(this->claveUsuario);
}
