#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mesero/mesero_menu_comandas.h"
#include "mesero/mesero_transferir_platillo.h"
#include "almacenista/almacenista_menu.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mDatabase = QSqlDatabase::database("Connection");
    if(!mDatabase.isOpen()){
        qDebug() << "ERROR";
    }else{
        qDebug() << "Base de datos conectada en Main Window";
    }

    menuComandas = new mesero_menu_comandas(this);
    menuComandas->show();
    menuComandas->setMainWindow(this);

    menuAlmacenista = new almacenista_menu(this);
    menuAlmacenista->show();
    menuAlmacenista->setMainWindow(this);

    transferirPlatillo = new mesero_transferir_platillo(this);
    transferirPlatillo->show();
    transferirPlatillo->setMainWindow(this);


    //ui->Mesas->setMainWindow(this);


    ui->stackedWidget->insertWidget(1, menuComandas);
    ui->stackedWidget->insertWidget(2, menuAlmacenista);
    ui->stackedWidget->insertWidget(3, transferirPlatillo);

    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::cambiar_pagina(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}

void MainWindow::pasar_id_mesa(int _id_mesa_auxiliar)
{
    menuComandas->set_id_mesa(_id_mesa_auxiliar);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cambiarStacked_indice(int P)
{
    ui->stackedWidget->setCurrentIndex(P);
}

void MainWindow::pasar_is_comanda(int _id_comanda)
{
    this->transferirPlatillo->set_idComanda(_id_comanda);
}
