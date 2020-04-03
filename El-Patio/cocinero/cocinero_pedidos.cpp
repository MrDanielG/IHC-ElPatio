#include "cocinero_pedidos.h"
#include "ui_cocinero_pedidos.h"
#include "QMessageBox"
#include "QDebug"
#include "QSqlQuery"
#include "QPixmap"
#include "models/pedido.h"
#include "cocinero/cocinero_tarjeta.h"

cocinero_pedidos::cocinero_pedidos(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cocinero_pedidos)
{
    ui->setupUi(this);

    conexionBD();
    actualizarCatalogo();
    if(this->isCocinero)
        qDebug()<<"Es cocinero";
}

void cocinero_pedidos::conexionBD()
{
    mDatabase = QSqlDatabase::database("Connection");
    if (!mDatabase.isOpen()){
        qDebug() << "ERROR con Base de Datos, esto es: COCINERO PEDIDOS";
        return;
    }else{
        qDebug() << "Base de datos continua abierta, esto es: COCINERO PEDIDOS";
    }
}

void cocinero_pedidos::actualizarCatalogo()
{
    QSqlQuery infoPedidos(mDatabase);
    if(this->isCocinero){
        infoPedidos.prepare("SELECT pe.id_Pedido, pe.Comanda_id_comanda, pl.nombre, pe.comentario, pe.estado FROM `pedido` AS pe INNER JOIN platillo AS pl ON pe.Platillo_id_platillo = pl.id_platillo WHERE pe.estado = 'En proceso' AND pl.categoria NOT LIKE '%BEBIDA%'");
    } else {
        infoPedidos.prepare("SELECT pe.id_Pedido, pe.Comanda_id_comanda, pl.nombre, pe.comentario, pe.estado FROM `pedido` AS pe INNER JOIN platillo AS pl ON pe.Platillo_id_platillo = pl.id_platillo WHERE pe.estado = 'En proceso' AND pl.categoria LIKE '%BEBIDA%'");
    }

    infoPedidos.exec();
    limiparCatalogo();

    int i = 0;
    int row = 0;
    int col = 0;

    Pedido pedidoTemp;
    while (infoPedidos.next())
    {
        pedidoTemp.idPedido = infoPedidos.value("id_Pedido").toString();
        pedidoTemp.idComanda = infoPedidos.value("Comanda_id_comanda").toString();
        pedidoTemp.nombrePlatillo = infoPedidos.value("nombre").toString();
        pedidoTemp.comentario = infoPedidos.value("comentario").toString();
        pedidoTemp.estado = infoPedidos.value("estado").toString();

        //El numero de columnas en las que se dividira el grid
        row = i / 2;
        col = i % 2;

        cocinero_tarjeta *tarjeta =
                new cocinero_tarjeta(pedidoTemp, this);
        i++;
        ui->gridLayout->addWidget(tarjeta, row, col);
    }
}

void cocinero_pedidos::limiparCatalogo()
{
    while (QLayoutItem *item = ui->gridLayout->takeAt(0))
    {
        Q_ASSERT(!item->layout());
        delete item->widget();
        delete item;
    }
}

void cocinero_pedidos::sideBarInfo(Pedido _pedido)
{
    qDebug() <<"Sidebar0";
    this->pedidoAux = _pedido;

    ui->numComanda->setText("Num. Comanda: " + _pedido.idComanda);
    ui->nombrePlatillo->setText(_pedido.nombrePlatillo);
    ui->estadoPlatillo->setText(_pedido.estado);
    ui->comentarioPlatillo->setText(_pedido.comentario);

    QSqlQuery imgPlatillo(mDatabase);
    imgPlatillo.prepare("SELECT foto FROM `platillo` WHERE nombre = '"+_pedido.nombrePlatillo+"'");
    imgPlatillo.exec();
    imgPlatillo.next();

    QString platilloImg = imgPlatillo.value(0).toString();

    QPixmap img(platilloImg);
    ui->imgPlatillo->setPixmap(img);
}

cocinero_pedidos::~cocinero_pedidos()
{
    delete ui;
}

void cocinero_pedidos::on_btnPedidoListo_clicked()
{
    QMessageBox::StandardButton respuesta = QMessageBox::question(this, tr("Confirmar"),
                                   tr("¿Seguro que desea Completar el Pedido?"));

    if(respuesta == QMessageBox::Yes){
        QSqlQuery updatePedido(mDatabase);
        updatePedido.prepare("UPDATE `pedido` SET `estado` = 'TERMINADO' WHERE `pedido`.`id_Pedido` = " + this->pedidoAux.idPedido);
        if(updatePedido.exec()){
            QMessageBox::information(this, tr("Exito"),
                                 "El pedido ha sido Cocinado");
        } else {
            QMessageBox::warning(this, tr("Error"),
                                 "No se ha actualizado el Pedido");
        }

        actualizarCatalogo();
    }
}

void cocinero_pedidos::on_btnActualizar_clicked()
{
    actualizarCatalogo();
}
