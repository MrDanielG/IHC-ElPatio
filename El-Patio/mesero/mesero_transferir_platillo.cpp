#include "mesero_transferir_platillo.h"
#include "ui_mesero_transferir_platillo.h"

#include "mainwindow.h"
#include "mesero_tarjeta_transferir.h"

#include <QDebug>
#include <QMessageBox>
#include <QSqlQuery>

mesero_transferir_platillo::mesero_transferir_platillo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mesero_transferir_platillo)
{
    ui->setupUi(this);

    mDatabase = QSqlDatabase::database("Connection");
    if (!mDatabase.isOpen()){
        qDebug() << "ERROR con Base de Datos, esto es: Transferir Platillos";
        return;
    }
    else{
        qDebug() << "Base de datos continua abierta, esto es: Transferir Platillos";
    }
}

mesero_transferir_platillo::~mesero_transferir_platillo()
{
    delete ui;
}

void mesero_transferir_platillo::setMainWindow(MainWindow *_mainwindow)
{
    mainWindow = _mainwindow;
}

void mesero_transferir_platillo::set_idComanda(int _idComanda)
{
    this->id_comanda = _idComanda;
    this->actualizarDatos();
}

void mesero_transferir_platillo::mover_platillo(QString id_pedido)
{
    int posicionLista = 0;
    while(posicionLista < this->copia_listaPlatillos.size() &&
          copia_listaPlatillos.at(posicionLista)->get_idPedido() != id_pedido)
        posicionLista++;

    //se agrega a la lista a transferir y al mism timepo de la lista
    mesero_tarjeta_transferir *aux = copia_listaPlatillos.takeAt(posicionLista);
    this->transferir_listPlatillos.append(aux);


    int posicionLista2 = 0;
    //saco elementos grid
    while(posicionLista2 < this->transferir_listPlatillos.size())
    {
        ui->grid_comandaNueva->addWidget(transferir_listPlatillos.value(posicionLista2), posicionLista2, 0);
        posicionLista2++;
    }

}

void mesero_transferir_platillo::sacar_platillo(QString id_pedido)
{
    int posicionLista = 0;

    while(posicionLista < this->transferir_listPlatillos.size() &&
          transferir_listPlatillos.at(posicionLista)->get_idPedido() != id_pedido)
        posicionLista++;

    //se agrega a la lista a transferir y al mism timepo de la lista
    mesero_tarjeta_transferir *aux = transferir_listPlatillos.takeAt(posicionLista);
    this->copia_listaPlatillos.append(aux);


    int posicionLista2 = 0;
    //saco elementos grid
    while(posicionLista2 < this->copia_listaPlatillos.size())
    {
        ui->grid_comandaActual->addWidget(copia_listaPlatillos.value(posicionLista2), posicionLista2, 0);
        posicionLista2++;
    }
}


void mesero_transferir_platillo::actualizarDatos()
{
    //obtengo el numero de la mesa
    QSqlQuery datosComando(mDatabase);
    QSqlQuery mesasLibres(mDatabase);
    QSqlQuery ultima_comanda(mDatabase);

    QString query_datosComanda = "SELECT * FROM comanda WHERE id_comanda = " + QString::number(this->id_comanda) + ";";
    if(datosComando.exec(query_datosComanda))
        qDebug() << "datosComando [ejecutado] " + query_datosComanda;
    else
        qDebug() << "datosComando [no_ejecutado]";
    datosComando.next();

    QString query_mesasLibres = "select * from mesa where estado = 'Libre';";
    if(mesasLibres.exec(query_mesasLibres))
        qDebug() << "query_mesasLibres [ejecutado] " + query_mesasLibres;
    else
        qDebug() << "query_mesasLibres [no_ejecutado]";

    QString query_platillos =
            "select * from pedido "
            "where Comanda_id_comanda = " + QString::number(this->id_comanda) + ";";

    if(ultima_comanda.exec(query_platillos))
        qDebug() << "query_platillos [ejecutado]" + query_platillos;
    else
        qDebug() << "query_platillos [no_ejecutado]" ;

    while(ultima_comanda.next())
    {
        int id_platillo = ultima_comanda.value("Platillo_id_platillo").toInt();
        int id_pedidio = ultima_comanda.value("id_Pedido").toInt();
        mesero_tarjeta_transferir *nuevo_platillo = new mesero_tarjeta_transferir(id_pedidio, id_platillo, this);
        nuevo_platillo->setPadre(this);
        nuevo_platillo->setMinimumHeight(80);
        nuevo_platillo->setMinimumWidth(410);
        this->lista_platillos.append(nuevo_platillo);
    }

    //hago de la lista completa, por en caso de querer cancelar nada se vea afectado
    copia_listaPlatillos = lista_platillos;

    int posicion_lista = 0;
    while (posicion_lista < lista_platillos.size())
    {
        ui->grid_comandaActual->addWidget(lista_platillos.at(posicion_lista), posicion_lista, 0);
        posicion_lista++;
    }

    while (mesasLibres.next())
        ui->cbox_mesasAbiertas->addItem(mesasLibres.value("numero_mesa").toString());

    ui->lb_numeroMesa->setText(datosComando.value("Mesa_numero_mesa").toString());
}

void mesero_transferir_platillo::on_btnRegresarMenu_clicked()
{
    if(this->transferir_listPlatillos.size())
    {
        if (QMessageBox::question(this, "Regresar a Menú", "¿Cancelar transferencia?")
                == QMessageBox::Yes)
            mainWindow->cambiar_pagina(1);
    }
    else
    {
        mainWindow->cambiar_pagina(1);
    }


}


