#include "mesero_menu_comandas.h"
#include "ui_mesero_menu_comandas.h"
#include "QMessageBox"
#include "QDebug"
#include "QSqlQuery"
#include "mesero/mesero_tarjeta_menu.h"
#include "mesero/mesero_tarjeta_chica.h"
#include "mainwindow.h"
#include "mesero_cambiar_cuenta_mesa.h"

#include <QSqlRecord>

mesero_menu_comandas::mesero_menu_comandas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mesero_menu_comandas)
{
    ui->setupUi(this);

    mDatabase = QSqlDatabase::database("Connection");
    if (!mDatabase.isOpen()){
        qDebug() << "ERROR con Base de Datos, esto es: MENU COMANDAS";
        return;
    }
    else{
        qDebug() << "Base de datos continua abierta, esto es: MENU COMANDAS";
    }
    actualizarCatalogo();

    ui->btnMandarCocina->setHidden(0);
    ui->lb_total->setHidden(1);
}

mesero_menu_comandas::~mesero_menu_comandas()
{
    delete ui;
}

void mesero_menu_comandas::actualizarCatalogo()
{
    QSqlQuery infoPlatillo(mDatabase);
    infoPlatillo.prepare("SELECT * FROM `platillo` WHERE estado = 'disponibles'");
    infoPlatillo.exec();
    limiparCatalogo();

    int i = 0;
    int row = 0;
    int col = 0;

    while (infoPlatillo.next())
    {
        QString id = infoPlatillo.value("id_platillo").toString();
        QString foto = infoPlatillo.value("foto").toString();
        QString nombrePlatillo = infoPlatillo.value("nombre").toString();
        QString precioPlatillo = infoPlatillo.value("precio").toString();
        //qDebug() << id << foto << nombrePlatillo << precioPlatillo;

        //El numero de columnas en las que se dividira el grid
        row = i / 2;
        col = i % 2;

        mesero_tarjeta_menu *tarjeta =
                new mesero_tarjeta_menu(id, nombrePlatillo, precioPlatillo, foto, this);
        i++;
        ui->gridLayout->addWidget(tarjeta, row, col);
    }
}

void mesero_menu_comandas::limiparCatalogo()
{
    while (QLayoutItem *item = ui->gridLayout->takeAt(0))
    {
        Q_ASSERT(!item->layout());
        delete item->widget();
        delete item;
    }
}

void mesero_menu_comandas::actualizarSideBar(Platillo plato, int operacion)
{
    if(this->pedidoPlatillos.contains(plato)){
        int Index = this->pedidoPlatillos.indexOf(plato);
        int sum = this->pedidoPlatillos.at(Index).cantidad;
        if(operacion > 0){
            sum++;
        }
        else{
            sum--;
        }
        if(sum == 0){
            this->pedidoPlatillos.removeAt(Index);
            while (QLayoutItem *item = ui->gridLayout_4->takeAt(0))
            {
                Q_ASSERT(!item->layout());
                delete item->widget();
                delete item;
            }
            actualizarSB();

        }
        else{
            Platillo Nuevo = this->pedidoPlatillos.at(Index);
            Nuevo.setCantidad(sum);
            this->pedidoPlatillos.replace(Index, Nuevo);
            actualizarSB();
        }
    }
    else{
        this->pedidoPlatillos.append(plato);
        actualizarSB();
    }
}

void mesero_menu_comandas::actualizarSB()
{
        int iterador = 0;
        int row = 0;
        int col = 0;

        for (int i = 0; i < this->pedidoPlatillos.size(); ++i) {

            QString id = this->pedidoPlatillos[i].id;
            QString nombrePlatillo = this->pedidoPlatillos[i].nombrePlatillo;
            QString precioPlatillo = this->pedidoPlatillos[i].precioPlatillo;
            QString fotoPlatillo = this->pedidoPlatillos[i].foto;
            int cantidad = this->pedidoPlatillos[i].cantidad;

            row = iterador / 1;
            col = iterador % 1;

            mesero_tarjeta_chica *tarjeta = new mesero_tarjeta_chica(id, nombrePlatillo, precioPlatillo, fotoPlatillo, cantidad);
            iterador++;
            ui->gridLayout_4->addWidget(tarjeta, row, col);
        }
}

void mesero_menu_comandas::on_btnMandarCocina_clicked()
{
    if(QMessageBox::question(this, tr("Enviar pedido"), tr("¿Está seguro que quiere hacer un pedido con estos platillos?"))==QMessageBox::Yes){
        //Necesito idComanda
        //INSERT INTO `pedido` (`id_Pedido`, `comentario`, `Comanda_id_comanda`, `Platillo_id_platillo`, `estado`) VALUES ('1', 'Sin cebolla', '1', '8', 'En proceso');
    }
    else{
        QMessageBox::information(this, tr("Cancelado"), tr("La orden no se ha enviado a cocina."));
    }
}

void mesero_menu_comandas::setMainWindow(MainWindow *_mainwindow)
{
    this->mainwindow = _mainwindow;
}

void mesero_menu_comandas::set_id_mesa(int _id_mesa_auxiliar)
{
    this->numero_mesa = _id_mesa_auxiliar;

    QSqlQuery ultima_comanda(mDatabase);
    QString query_ultima_comanda =
                "select * from comanda where Mesa_numero_mesa = " + QString::number(this->numero_mesa) + " "
                "order by hora_apertura DESC limit 1";

    if(ultima_comanda.exec(query_ultima_comanda))
        qDebug() << "query_ultima_comanda [ejecutado]" + query_ultima_comanda;
    else
        qDebug() << "query_ultima_comanda [no_ejecutado]";

    ultima_comanda.next();

    this->numero_comanda = ultima_comanda.record().value("id_comanda").toInt();
}

void mesero_menu_comandas::limpiar_grid4()
{
    int posicionLista = 0;
    while(posicionLista < this->lista_platillos.size())
    {
        ui->gridLayout_4->removeWidget(lista_platillos.at(posicionLista));
        this->lista_platillos.at(posicionLista)->~mesero_tarjeta_chica();
        posicionLista++;
    }
    this->lista_platillos.clear();
}

void mesero_menu_comandas::on_btnBebidas_2_clicked()
{
    ui->btnMandarCocina->setHidden(1);
    ui->lb_total->setHidden(0);

    //limpia el grid
    this->limpiar_grid4();

    QSqlQuery ultima_comanda(mDatabase);
    QSqlQuery precio_total(mDatabase);
//    QString query_ultima_comanda =
//                "select * from comanda where Mesa_numero_mesa = " + QString::number(this->numero_mesa) + " "
//                "order by hora_apertura DESC limit 1";

//    if(ultima_comanda.exec(query_ultima_comanda))
//        qDebug() << "query_ultima_comanda [ejecutado]" + query_ultima_comanda;
//    else
//        qDebug() << "query_ultima_comanda [no_ejecutado]";

//    ultima_comanda.next();

//    this->numero_comanda = ultima_comanda.record().value("id_comanda").toInt();

        QString query_platillos =
                "select * from pedido "
                "where Comanda_id_comanda = " + QString::number(this->numero_comanda) + ";";

        if(ultima_comanda.exec(query_platillos))
            qDebug() << "query_platillos [ejecutado]" + query_platillos;
        else
            qDebug() << "query_platillos [no_ejecutado]" ;

        while(ultima_comanda.next())
        {
            mesero_tarjeta_chica *nuevo_platillo = new mesero_tarjeta_chica(
                ultima_comanda.record().value("Platillo_id_platillo").toInt(), this);
            nuevo_platillo->setMinimumWidth(235);
            nuevo_platillo->setMinimumHeight(100);
            this->lista_platillos.append(nuevo_platillo);
        }

        //cambiar dato propio de la clase
        int posicion_lista = 0;
        while (posicion_lista < lista_platillos.size())
        {
            ui->gridLayout_4->addWidget(lista_platillos.at(posicion_lista), posicion_lista, 0);
            posicion_lista++;
        }

        QString query_precio_total = "select sum(precio) from pedido inner join platillo on"
                                     " pedido.Platillo_id_platillo = platillo.id_platillo"
                                     " where Comanda_id_comanda = " + QString::number(this->numero_comanda) + ";";

        if(precio_total.exec(query_precio_total))
            qDebug() << "query_precio_total [ejecutado]" + query_precio_total;
        else
            qDebug() << "query_precio_total [no_ejecutado]" + query_precio_total;

        precio_total.next();
        QString s_precio_total = precio_total.record().value("sum(precio)").toString();
        qDebug() << s_precio_total;
        ui->lb_total->setText("Total $" + s_precio_total);
}

void mesero_menu_comandas::on_btnPlatillos_2_clicked()
{
    ui->btnMandarCocina->setHidden(0);
    ui->lb_total->setHidden(1);


    //limpia el grid
    this->limpiar_grid4();
}

void mesero_menu_comandas::on_btn_transferir_clicked()
{
    this->mainwindow->pasar_is_comanda(this->numero_comanda);
    this->mainwindow->cambiar_pagina(3);
}



void mesero_menu_comandas::on_btnCambiarMesero_clicked()
{
    mesero_cambiar_cuenta_mesa *Cambio = new mesero_cambiar_cuenta_mesa();
    Cambio->exec();
}
