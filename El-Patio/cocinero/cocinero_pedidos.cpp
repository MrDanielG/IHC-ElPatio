#include "cocinero_pedidos.h"
#include "ui_cocinero_pedidos.h"

cocinero_pedidos::cocinero_pedidos(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cocinero_pedidos)
{
    ui->setupUi(this);
}

cocinero_pedidos::~cocinero_pedidos()
{
    delete ui;
}
