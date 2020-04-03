#include "cocinero_landpage.h"
#include "ui_cocinero_landpage.h"
#include "cocinero/cocinero_pedidos.h"
#include "mainwindow.h"
#include "QMessageBox"

cocinero_landpage::cocinero_landpage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cocinero_landpage)
{
    ui->setupUi(this);

    this->padre = qobject_cast<MainWindow*>(parent);
    pedidosCocina = new cocinero_pedidos(this);
    ui->stackedWidget->insertWidget(1, pedidosCocina);
    ui->stackedWidget->setCurrentIndex(0);
}

void cocinero_landpage::setCocineroId(QString _idCocina)
{
    this->idCocinero = _idCocina;
}

cocinero_landpage::~cocinero_landpage()
{
    delete ui;
}

void cocinero_landpage::on_btnInicio_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void cocinero_landpage::on_btnPlatillos_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void cocinero_landpage::on_btnCerrarSesion_clicked()
{
    QMessageBox::StandardButton respuesta = QMessageBox::question(this, tr("Salir"),
                                   tr("¿Seguro que desea Cerrar Sesión?"));

    if(respuesta == QMessageBox::Yes)
        this->padre->cambiar_pagina(0);
}
