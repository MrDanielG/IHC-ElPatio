#include "mesero_transferir_platillo.h"
#include "ui_mesero_transferir_platillo.h"

#include "mainwindow.h"
#include "mesero_tarjeta_transferir.h"
#include "mesero/confirmartransferencia.h"

#include <QDebug>
#include <QMessageBox>
#include <QSqlQuery>
#include <QDialog>

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
    limpiarGRidListas();
    //obtengo el numero de la mesa
    QSqlQuery datosComando(mDatabase);
    QSqlQuery mesasLibres(mDatabase);
    QSqlQuery ultima_comanda(mDatabase);
    QSqlQuery datosMesero(mDatabase);

    QString query_datosComanda = "SELECT * FROM comanda WHERE id_comanda = " + QString::number(this->id_comanda) + ";";
    if(datosComando.exec(query_datosComanda))
        qDebug() << "datosComando [ejecutado] " + query_datosComanda;
    else
        qDebug() << "datosComando [no_ejecutado]";
    datosComando.next();

    QString query_mesasLibres = "select * from mesa where estado = 'Ocupada';";
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
        nuevo_platillo->setMinimumWidth(320);
        this->lista_platillos.append(nuevo_platillo);
    }

    //hago de la lista completa, por en caso de querer cancelar nada se vea afectado
    copia_listaPlatillos = lista_platillos;

    int posicion_lista = 0;
    while (posicion_lista < copia_listaPlatillos.size())
    {
        ui->grid_comandaActual->addWidget(copia_listaPlatillos.at(posicion_lista), posicion_lista, 0);
        posicion_lista++;
    }

    while (mesasLibres.next())
        ui->cbox_mesasAbiertas->addItem(mesasLibres.value("numero_mesa").toString());

    ui->lb_numeroMesa->setText(datosComando.value("Mesa_numero_mesa").toString());

    //obtengo los datos del empleado
    QString claveMesero = datosComando.value("Usuario_clave").toString();
    QString query_datosMesero =
            "select clave, concat(nombre, ' ', apellido_paterno, ' ', apellido_materno) as nombre "
            "from usuario where clave = " + claveMesero + ";";

    if(datosMesero.exec(query_datosMesero))
        qDebug() << "query_datosMesero [ejecutado] "  + query_datosMesero;
    else
        qDebug() << "query_datosMesero [no_ejecutado] " + query_datosMesero;
    datosMesero.next();

    ui->lb_nombreMesero->setText(datosMesero.value("nombre").toString() +  "\n No. " +
                                 datosMesero.value("clave").toString());
}

void mesero_transferir_platillo::limpiarGRidListas()
{
    lista_platillos.clear();
    transferir_listPlatillos;

    int posicionLista = 0;
    while(posicionLista < this->copia_listaPlatillos.size())
    {
        ui->grid_comandaActual->removeWidget(copia_listaPlatillos.at(posicionLista));
        this->copia_listaPlatillos.at(posicionLista)->~mesero_tarjeta_transferir();
        posicionLista++;
    }
    this->copia_listaPlatillos.clear();

    posicionLista = 0;
    while(posicionLista < this->transferir_listPlatillos.size())
    {
        ui->grid_comandaNueva->removeWidget(transferir_listPlatillos.at(posicionLista));
        this->transferir_listPlatillos.at(posicionLista)->~mesero_tarjeta_transferir();
        posicionLista++;
    }
    this->transferir_listPlatillos.clear();
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
        QMessageBox::information(this, "Cancelación", "Se a cancelado la transferencia de platillos." );
        mainWindow->cambiar_pagina(1);
    }
}



void mesero_transferir_platillo::on_btn_transferirPlatillos_clicked()
{
    //obetener id de la comanda de la mesa a transferir
    QSqlQuery ultima_comanda(mDatabase);
    QString numero_mesa = ui->cbox_mesasAbiertas->currentText();
    QString id_comandaTransferir;
    QString query_ultima_comanda =
                "select * from comanda where Mesa_numero_mesa = "
            + numero_mesa + " order by hora_apertura DESC limit 1;";

    if(ultima_comanda.exec(query_ultima_comanda))
        qDebug() << "query_ultima_comanda [ejecutado]" + query_ultima_comanda;
    else
        qDebug() << "query_ultima_comanda [no_ejecutado]" + query_ultima_comanda;
    ultima_comanda.next();

    qDebug() << "id de la comanda de la mesa abierta: " << ultima_comanda.value("id_comanda").toString();
    id_comandaTransferir = ultima_comanda.value("id_comanda").toString();


    //hace la tranferencia de los platillos a la mesa
    //solo se actuliza el id de la comanda en la tablaplatillos
    ConfirmarTransferencia confirmar_admin;
    confirmar_admin.setModal(true);
    confirmar_admin.exec();
    if(confirmar_admin.result())
    {
        QSqlQuery validor_ClaveAdmin(mDatabase);
        QString query_validorClaveAdmin = "select * from usuario "
                                          "where clave = "+confirmar_admin.get_claveAdmin()+" ;";
        validor_ClaveAdmin.exec(query_validorClaveAdmin);
        if (!validor_ClaveAdmin.next()) {
            QMessageBox::warning(this, "Clave incorrecta", "la clave es incorrecta o no existe");
        }
        else
        {
            QSqlQuery transferirPlatillos(mDatabase);
            QString query_transferirPlatillos;

            if(transferirPlatillos.exec(query_transferirPlatillos))
                qDebug() << "query_transferirPlatillos [ejecutado]" + query_transferirPlatillos;
            else
                qDebug() << "query_transferirPlatillos [no_ejecutado]" + query_transferirPlatillos;

            int posicionLista=0;
            while (posicionLista < transferir_listPlatillos.size()) {
                query_transferirPlatillos = " UPDATE pedido"
                                            " SET Comanda_id_comanda = "+id_comandaTransferir+
                                            " WHERE Comanda_id_comanda = "+QString::number(this->id_comanda)+
                                            " AND id_pedido = " +transferir_listPlatillos.at(posicionLista)->get_idPedido() + ";";
                transferirPlatillos.exec(query_transferirPlatillos);
                posicionLista++;
            }

            transferirPlatillos.next();
            actualizarDatos();
            QMessageBox::information(this, "Completado", "Tranferencia completada.");

        }
    }
}

