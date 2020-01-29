#include "mainwindow.h"
#include "ui_mainwindow.h"
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

    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget->insertWidget(1, &menuComandas);
    //Mesas.setMainWindow(this);
    //ui->stackedWidget->insertWidget(0, &Mesas);
    //ui->stackedWidget->setCurrentIndex(1);

    //connect(&CatalogoMesas, &CatalogoMesas::cambiarStackedWidget, this, &MainWindow::cambiarStacked_indice);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cambiarStacked_indice(int P)
{
    ui->stackedWidget->setCurrentIndex(P);
}
