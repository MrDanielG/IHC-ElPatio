#include "mesero_transferir_platillo.h"
#include "ui_mesero_transferir_platillo.h"

#include <QDebug>

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
