#include "mesero_transferir_platillo.h"
#include "ui_mesero_transferir_platillo.h"

#include "mainwindow.h"
#include "mesero_tarjeta_chica.h"

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
        mesero_tarjeta_chica *nuevo_platillo = new mesero_tarjeta_chica(
                    ultima_comanda.value("Platillo_id_platillo").toInt(), this);
        nuevo_platillo->setMinimumWidth(235);
        nuevo_platillo->setMinimumHeight(100);
        this->lista_platillos.append(nuevo_platillo);
    }

//    int posicion_lista = 0;
//    while (posicion_lista < lista_platillos.size())
//    {
//        ui->gridLayout_4->addWidget(lista_platillos.at(posicion_lista), posicion_lista, 0);
//        posicion_lista++;
//    }

    while (mesasLibres.next()) {
        ui->cbox_mesasAbiertas->addItem(mesasLibres.value("numero_mesa").toString());
    }

    ui->lb_numeroMesa->setText(datosComando.value("Mesa_numero_mesa").toString());
}

void mesero_transferir_platillo::on_btnRegresarMenu_clicked()
{
    if (QMessageBox::question(this, "Regresar a Menú", "¿Cancelar transferencia?")
            == QMessageBox::Yes)
    {
        mainWindow->cambiar_pagina(1);
    }

}


