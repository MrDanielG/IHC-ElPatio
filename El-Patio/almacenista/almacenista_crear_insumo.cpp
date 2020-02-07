#include "almacenista_crear_insumo.h"
#include "ui_almacenista_crear_insumo.h"

almacenista_crear_insumo::almacenista_crear_insumo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::almacenista_crear_insumo)
{
    ui->setupUi(this);
}

almacenista_crear_insumo::~almacenista_crear_insumo()
{
    delete ui;
}
