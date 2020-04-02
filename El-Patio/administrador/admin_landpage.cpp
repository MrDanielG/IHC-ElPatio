#include "admin_landpage.h"
#include "ui_admin_landpage.h"
#include "QMessageBox"
#include "mainwindow.h"
#include "administrador/administrador_crud_platillos.h"
#include "administrador/admin_gestion_usuarios.h"
#include "administrador/admin_reportes.h"
#include "administrador/admin_reservaciones.h"

admin_landpage::admin_landpage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admin_landpage)
{
    ui->setupUi(this);

    this->padre = qobject_cast<MainWindow*>(parent); //Casteo de QWidget a MainWindow

    gestionUsuarios = new admin_gestion_usuarios(this);
    crudPlatillos = new administrador_crud_platillos(this);
    reportes = new admin_reportes(this);

    ui->stackedWidget->insertWidget(1, crudPlatillos);
    ui->stackedWidget->insertWidget(2, gestionUsuarios);
    ui->stackedWidget->insertWidget(3, reportes);

    ui->stackedWidget->setCurrentIndex(0);
}

void admin_landpage::setIdAdmin(QString _idAdmin)
{
    this->idAdmin = _idAdmin;
}

admin_landpage::~admin_landpage()
{
    delete ui;
}

void admin_landpage::on_btnPlatillos_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void admin_landpage::on_btnUsuarios_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void admin_landpage::on_btnReportes_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void admin_landpage::on_btnCerrarSesion_clicked()
{
    QMessageBox::StandardButton respuesta = QMessageBox::question(this, tr("Salir"),
                                   tr("¿Seguro que desea Cerrar Sesión?"));

    if(respuesta == QMessageBox::Yes)
        this->padre->cambiar_pagina(0);
}

void admin_landpage::on_btnInicio_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
