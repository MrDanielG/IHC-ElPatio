#include "cocinero_tarjeta.h"
#include "ui_cocinero_tarjeta.h"
#include "cocinero/cocinero_pedidos.h"

cocinero_tarjeta::cocinero_tarjeta(Pedido _pedido, cocinero_pedidos *parent) :
    QWidget(parent),
    ui(new Ui::cocinero_tarjeta)
{
    ui->setupUi(this);

    this->padre = parent;
    this->pedido = _pedido;
}

cocinero_tarjeta::~cocinero_tarjeta()
{
    delete ui;
}

void cocinero_tarjeta::on_btnInfoPedido_clicked()
{
    this->padre->sideBarInfo(this->pedido);
}
