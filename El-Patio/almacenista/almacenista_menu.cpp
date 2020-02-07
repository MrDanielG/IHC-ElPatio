#include "almacenista_menu.h"
#include "ui_almacenista_menu.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSortFilterProxyModel>
#include <QSqlRelationalTableModel>

almacenista_menu::almacenista_menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::almacenista_menu),
    almacenModel(new QSqlQueryModel(this)),
       almacenProxyModel(new QSortFilterProxyModel(this))
{
    ui->setupUi(this);

    mDatabase = QSqlDatabase::database("Connection");
    if(!mDatabase.isOpen()){
        qDebug()<<"ERROR, Almacen no conectado";
    }

    //elementos a ocultar
    ui->spinBox_existencias->setHidden(true);
    ui->spinBox_precio->setHidden(true);
    ui->ln_presentacion->setHidden(true);
    ui->btn_cancelar->setHidden(true);
    ui->btn_guardar->setHidden(true);

    script = "select ins.id_insumo,ins.nombre, ins.precio_compra, ins.existencias,"
                     " ins.presentacion, ing.fecha_almacenamiento, ing.dias_caducidad"
                     " from insumo as ins inner join ingrediente as ing"
                     " where ins.id_insumo = ing.id_insumo";
    llenarTabla(script);
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

void almacenista_menu::llenarTabla(QString query)
{
    almacenModel->setQuery(query, QSqlDatabase::database("Connection"));

    almacenProxyModel->setSourceModel(almacenModel);
    ui->tablaInsumos->setModel(almacenProxyModel);
}

void almacenista_menu::on_ln_nombre_insumo_textChanged(const QString &arg1)
{
    if (arg1.isEmpty()){ llenarTabla(script);
    }
    else{
        QString filtro = script + " && ins.nombre = '"+arg1+"'";
        llenarTabla(filtro);
    }
}

void almacenista_menu::on_tablaInsumos_clicked(const QModelIndex &index)
{
    QString id = ui->tablaInsumos->model()->data(index).toString();
    QSqlQuery query(mDatabase);
    QString scrp = "select ins.id_insumo,ins.nombre, ins.precio_compra,"
                   " ins.existencias, ins.presentacion from insumo"
                   " as ins inner join ingrediente as ing where ins.id_insumo = "+id+"";
    query.prepare(scrp);
    if(query.exec())
    {
        query.next();
        QString nombre = query.value(1).toString();
        QString clave = query.value(0).toString();
        QString precio = query.value(2).toString();
        QString existencias = query.value(3).toString();
        QString presentacion = query.value(4).toString();
        ui->lb_id_insumo->setText(clave);
        ui->lb_nombre_insumo->setText(nombre);
        ui->lb_precio_insumo->setText(precio);
        ui->lb_existencias_insumo->setText(existencias);
        ui->lb_presentacion_insumo->setText(presentacion);
    }
    query.finish();
}
