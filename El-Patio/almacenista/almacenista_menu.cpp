#include "almacenista_menu.h"
#include "ui_almacenista_menu.h"

#include <QDebug>

almacenista_menu::almacenista_menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::almacenista_menu)
{
    ui->setupUi(this);

    //elementos a ocultar
    ui->spinBox_existencias->setHidden(true);
    ui->spinBox_precio->setHidden(true);
    ui->ln_presentacion->setHidden(true);
    ui->btn_cancelar->setHidden(true);
    ui->btn_guardar->setHidden(true);
}

almacenista_menu::~almacenista_menu()
{
    delete ui;
}

void almacenista_menu::setMainWindow(MainWindow *_mainwindow)
{
    this->mainwindow = _mainwindow;
}

void almacenista_menu::on_btn_editar_insumo_clicked()
{
    //Mostrar elementos ocultos
    ui->spinBox_existencias->setHidden(false);
    ui->spinBox_precio->setHidden(false);
    ui->ln_presentacion->setHidden(false);
    ui->btn_cancelar->setHidden(false);
    ui->btn_guardar->setHidden(false);
    //oculta elementos
    ui->lb_precio_insumo->setHidden(true);
    ui->lb_presentacion_insumo->setHidden(true);
    ui->lb_existencias_insumo->setHidden(true);
    ui->btn_editar_insumo->setHidden(true);

}

void almacenista_menu::on_btn_cancelar_clicked()
{
    //Mostrar elementos ocultos
    ui->spinBox_existencias->setHidden(true);
    ui->spinBox_precio->setHidden(true);
    ui->ln_presentacion->setHidden(true);
    ui->btn_cancelar->setHidden(true);
    ui->btn_guardar->setHidden(true);
    //oculta elementos
    ui->lb_precio_insumo->setHidden(false);
    ui->lb_presentacion_insumo->setHidden(false);
    ui->lb_existencias_insumo->setHidden(false);
    ui->btn_editar_insumo->setHidden(false);

}
