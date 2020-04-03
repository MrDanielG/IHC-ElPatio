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
    llenarTarjeta();
}

void cocinero_tarjeta::llenarTarjeta()
{
    ui->numComanda->setText("Num. Pedido: #" + this->pedido.idPedido);
    ui->nombrePlatillo->setText(this->pedido.nombrePlatillo);
    ui->estadoPlatillo->setText("Estado: " + this->pedido.estado);
    ui->comentarioPlatillo->setText(this->pedido.comentario);
}

cocinero_tarjeta::~cocinero_tarjeta()
{
    delete ui;
}

void cocinero_tarjeta::on_btnInfoPedido_clicked()
{
    this->padre->sideBarInfo(this->pedido);
}
