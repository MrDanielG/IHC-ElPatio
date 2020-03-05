#include "mesero_tarjeta_cancelar.h"
#include "ui_mesero_tarjeta_cancelar.h"

#include <QDebug>

mesero_tarjeta_cancelar::mesero_tarjeta_cancelar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mesero_tarjeta_cancelar)
{
    ui->setupUi(this);
}

mesero_tarjeta_cancelar::mesero_tarjeta_cancelar(QString _pedido,QString _nombrePlatillo, QString _extra, QString _precio,  mesero_cancela_platillos *_padre, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mesero_tarjeta_cancelar)
{
    ui->setupUi(this);

    padre = _padre;

    pedido          = _pedido;
    nombrePlatillo  = _nombrePlatillo;
    extra           = _extra;
    precio          = _precio;
    cancelada        = false;

    ui->lb_nombrePlatillo->setText(nombrePlatillo);
    ui->lb_precioPlatillo->setText(precio);
    ui->lb_extraPlatillo->setText(extra);

    estadoTarjeta(cancelada);
}

void mesero_tarjeta_cancelar::estadoTarjeta(bool estado)
{
    QString estilo              = "#tarjetaCancelar{ background-color: white; border-radius: 5px; }";
    QString estilo_selecionado  = "#tarjetaCancelar{ background-color: white;  border: 1px solid #C56E68; border-radius: 5px; }";

    if(estado){
        ui->tarjetaCancelar->setStyleSheet(estilo_selecionado);
        ui->btn_cambiar->setHidden(true);
        ui->btn_cancelar->setHidden(false);
    }else{
        ui->tarjetaCancelar->setStyleSheet(estilo);
        ui->btn_cambiar->setHidden(false);
        ui->btn_cancelar->setHidden(true);
    }
}

bool mesero_tarjeta_cancelar::getEstado()
{
    return cancelada;
}

QString mesero_tarjeta_cancelar::getPedido()
{
    return pedido;
}

mesero_tarjeta_cancelar::~mesero_tarjeta_cancelar()
{
    delete ui;
}

void mesero_tarjeta_cancelar::on_btn_cambiar_clicked()
{
    cancelada = true;
    estadoTarjeta(cancelada);
}

void mesero_tarjeta_cancelar::on_btn_cancelar_clicked()
{
    cancelada = false;
    estadoTarjeta(cancelada);
}
