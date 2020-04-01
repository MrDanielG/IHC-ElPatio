#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mesero/mesero_menu_comandas.h"
#include "mesero/mesero_transferir_platillo.h"
#include "almacenista/almacenista_menu.h"
#include "administrador/admin_gestion_usuarios.h"
#include "dividircuenta.h"
#include "administrador/administrador_crud_platillos.h"
#include "administrador/admin_reportes.h"
#include "login.h"
#include "administrador/admin_landpage.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mDatabase = QSqlDatabase::database("Connection");
    if (!mDatabase.isOpen())
    {
        qDebug() << "ERROR";
    }
    else
    {
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

    gestionUsuarios = new admin_gestion_usuarios(this);
    crudPlatillos = new administrador_crud_platillos(this);
    inicioSesion = new login(this);
    cuentas = new DividirCuenta(this);
    adminLandpage = new admin_landpage(this);

    reportes = new admin_reportes(this);
    reportes->show();

    ui->Mesas->setMainWindow(this);

    ui->stackedWidget->insertWidget(1, menuComandas);
    ui->stackedWidget->insertWidget(2, menuAlmacenista);
    ui->stackedWidget->insertWidget(3, transferirPlatillo);
    ui->stackedWidget->insertWidget(4, gestionUsuarios);
    ui->stackedWidget->insertWidget(5, cuentas);
    ui->stackedWidget->insertWidget(6, crudPlatillos);
    ui->stackedWidget->insertWidget(7, reportes);
    ui->stackedWidget->insertWidget(8, inicioSesion);
    ui->stackedWidget->insertWidget(9, adminLandpage);

    ui->stackedWidget->setCurrentIndex(0); //Por mietras xd
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

void MainWindow::setAdmin(QString _idAdmin)
{
    ui->stackedWidget->setCurrentIndex(9);
    adminLandpage->setIdAdmin(_idAdmin);
}
