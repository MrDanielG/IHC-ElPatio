#include "mesero_menu_comandas.h"
#include "ui_mesero_menu_comandas.h"

mesero_menu_comandas::mesero_menu_comandas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mesero_menu_comandas)
{
    ui->setupUi(this);
}

mesero_menu_comandas::~mesero_menu_comandas()
{
    delete ui;
}
