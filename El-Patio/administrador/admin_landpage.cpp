#include "admin_landpage.h"
#include "ui_admin_landpage.h"
#include "administrador/administrador_crud_platillos.h"
#include "admin_gestion_usuarios.h"
#include "admin_reportes.h"
#include "admin_reservaciones.h"

admin_landpage::admin_landpage(QString _idAdmin, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admin_landpage)
{
    ui->setupUi(this);

    this->idAdmin = _idAdmin;
}

admin_landpage::~admin_landpage()
{
    delete ui;
}
