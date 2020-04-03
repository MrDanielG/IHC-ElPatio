#include "cocinero_pedidos.h"
#include "ui_cocinero_pedidos.h"
#include "QMessageBox"
#include "QDebug"
#include "QSqlQuery"
#include "models/pedido.h"
#include "cocinero/cocinero_tarjeta.h"

cocinero_pedidos::cocinero_pedidos(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cocinero_pedidos)
{
    ui->setupUi(this);

    conexionBD();
    actualizarCatalogo();
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
    infoPedidos.prepare("SELECT * FROM `pedido` INNER JOIN platillo ON pedido.Platillo_id_platillo = platillo.id_platillo");
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

cocinero_pedidos::~cocinero_pedidos()
{
    delete ui;
}
