#include "mesero_tarjeta_transferir.h"
#include "ui_mesero_tarjeta_transferir.h"

#include "mesero_transferir_platillo.h"

#include <QSqlQuery>
#include <QDebug>
#include <QSqlRecord>

mesero_tarjeta_transferir::mesero_tarjeta_transferir(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mesero_tarjeta_transferir)
{
    ui->setupUi(this);

}

mesero_tarjeta_transferir::mesero_tarjeta_transferir(int id_pedido, int id_platillo, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mesero_tarjeta_transferir)
{
    ui->setupUi(this);

    mDatabase = QSqlDatabase::database("Connection");
    if(!mDatabase.isOpen())
        qDebug() << "ERROR, tarjeta [mesero_tarjeta_transferir]";
    else
        qDebug() << "conexion exitosa desde [mesero_tarjeta_transferir]";

    this->id = QString::number(id_platillo);
    this->id_pedido = QString::number(id_pedido);

    QSqlQuery datos_platillo(mDatabase);
    QString query_datos_platillo = "select * from platillo where id_platillo = " + this->id + ";";
    datos_platillo.exec(query_datos_platillo);
    datos_platillo.next();

    this->nombrePlatillo = datos_platillo.record().value("nombre").toString();
    this->precioPlatillo = datos_platillo.record().value("precio").toString();
    this->foto = datos_platillo.record().value("foto").toString();

    ui->btn_cancelar->setHidden(true);

    llenarTarjeta();
}

void mesero_tarjeta_transferir::llenarTarjeta()
{
    QPixmap img(this->foto);
    ui->lb_nombrePlatillo->setText(this->nombrePlatillo);
    ui->lb_precioPlatillo->setText(this->precioPlatillo);
    ui->lb_imgPlatillo->setPixmap(img);
}

void mesero_tarjeta_transferir::setPadre(mesero_transferir_platillo *_padre)
{
    this->padre = _padre;
}

void mesero_tarjeta_transferir::mover_transferir()
{
    qDebug() << "mueve a lista transferir" << this->posicion_lista;
}

void mesero_tarjeta_transferir::quitar_transferir()
{

}

QString mesero_tarjeta_transferir::get_idPedido()
{
    return this->id_pedido;
}

mesero_tarjeta_transferir::~mesero_tarjeta_transferir()
{
    delete ui;
}

void mesero_tarjeta_transferir::on_btn_cambiar_clicked()
{
    this->padre->mover_platillo(this->id_pedido);
    ui->btn_cambiar->setHidden(true);
    ui->btn_cancelar->setHidden(false);
}

void mesero_tarjeta_transferir::on_btn_cancelar_clicked()
{
    this->padre->sacar_platillo(this->id_pedido);
    ui->btn_cambiar->setHidden(false);
    ui->btn_cancelar->setHidden(true);
}
