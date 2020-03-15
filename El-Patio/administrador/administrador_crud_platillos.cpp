#include "administrador_crud_platillos.h"
#include "ui_administrador_crud_platillos.h"

administrador_crud_platillos::administrador_crud_platillos(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::administrador_crud_platillos)
{
    ui->setupUi(this);
}

administrador_crud_platillos::~administrador_crud_platillos()
{
    delete ui;
}
