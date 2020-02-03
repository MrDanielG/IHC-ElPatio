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
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget->insertWidget(1, menuComandas);
    menuComandas->show();

    menuComandas->setMainWindow(this);
    ui->Mesas->setMainWindow(this);
}

void MainWindow::cambiar_pagina(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}

MainWindow::~MainWindow()
{
    delete ui;
}
