#include "cocinero_landpage.h"
#include "ui_cocinero_landpage.h"
#include "cocinero/cocinero_pedidos.h"
#include "mainwindow.h"

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
