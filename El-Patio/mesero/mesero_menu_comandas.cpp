#include "mesero_menu_comandas.h"
#include "ui_mesero_menu_comandas.h"

#include <QDebug>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>
#include "mesero_tarjeta_chica.h"

mesero_menu_comandas::mesero_menu_comandas(int _numero_mesa, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mesero_menu_comandas)
{
    mDatabase = QSqlDatabase::database("Connection");
    if(!mDatabase.isOpen()){
        qDebug()<<"ERROR, Mesas no conectado";
    }else {
        qDebug() << "conexion exitosa desde menu_comandas";
    }
    ui->setupUi(this);

    this->numero_mesa = _numero_mesa;
}


mesero_menu_comandas::~mesero_menu_comandas()
{
    delete ui;
}

void mesero_menu_comandas::on_btnBebidas_2_clicked()
{
    QSqlQuery ultima_comanda(mDatabase);
    QSqlQuery precio_total(mDatabase);
    QString query_ultima_comanda =
            "select * from comanda where Mesa_numero_mesa = " + QString::number(this->numero_mesa) + " "
            "order by hora_apertura DESC limit 1";

    if(ultima_comanda.exec(query_ultima_comanda))
        qDebug() << "query_ultima_comanda [ejecutado]" + query_ultima_comanda;
    else
        qDebug() << "query_ultima_comanda [no_ejecutado]";

    ultima_comanda.next();

    this->numero_comanda = ultima_comanda.record().value("id_comanda").toInt();

    QString query_platillos =
            "select * from pedido "
            "where Comanda_id_comanda = " + QString::number(this->numero_comanda) + ";";

    if(ultima_comanda.exec(query_platillos))
        qDebug() << "query_platillos [ejecutado]" + query_platillos;
    else
        qDebug() << "query_platillos [no_ejecutado]" ;

    while(ultima_comanda.next())
    {
        mesero_tarjeta_chica *nuevo_platillo = new mesero_tarjeta_chica(
            ultima_comanda.record().value("Platillo_id_platillo").toInt(), this);
        nuevo_platillo->setMinimumWidth(235);
        nuevo_platillo->setMinimumHeight(100);
        this->lista_platillos.append(nuevo_platillo);
        qDebug() << "qwe";
    }

    //cambiar dato propio de la clase

    int posicion_lista = 0;
    while (posicion_lista < lista_platillos.size())
    {
        ui->grid_lista_platillos->addWidget(lista_platillos.at(posicion_lista), posicion_lista, 0);
        posicion_lista++;
    }

    QString query_precio_total = "select sum(precio) from pedido inner join platillo on"
                                 " pedido.Platillo_id_platillo = platillo.id_platillo"
                                 " where Comanda_id_comanda = " + QString::number(this->numero_comanda) + ";";

    if(precio_total.exec(query_precio_total))
        qDebug() << "query_precio_total [ejecutado]" + query_precio_total;
    else
        qDebug() << "query_precio_total [no_ejecutado]" + query_precio_total;

    precio_total.next();
    QString s_precio_total = precio_total.record().value("sum(precio)").toString();
    qDebug() << s_precio_total;
    ui->lb_total->setText("Total $" + s_precio_total);
}
