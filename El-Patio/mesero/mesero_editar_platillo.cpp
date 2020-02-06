#include "mesero_editar_platillo.h"
#include "ui_mesero_editar_platillo.h"

mesero_editar_platillo::mesero_editar_platillo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mesero_editar_platillo)
{
    ui->setupUi(this);

    ui->stackedWidget->insertWidget(1, &agregarExtra);
    ui->stackedWidget->setCurrentIndex(1);
}

mesero_editar_platillo::~mesero_editar_platillo()
{
    delete ui;
}
