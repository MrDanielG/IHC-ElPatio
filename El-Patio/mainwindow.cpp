#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mesero/mesero_menu_comandas.h"

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
    ui->stackedWidget->insertWidget(1, menuComandas);
    menuComandas->setMainWindow(this);
    ui->Mesas->setMainWindow(this);

    menuComandas->show();
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::cambiar_pagina(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}

void MainWindow::pasar_id_mesa(int _id_mesa_auxiliar)
{

    menuComandas->set_id_mesa(_id_mesa_auxiliar);
     qDebug() << "\n\nmesa" << _id_mesa_auxiliar;
}

MainWindow::~MainWindow()
{
    delete ui;
}
