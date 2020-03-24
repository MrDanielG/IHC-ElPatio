#include "admin_reportes.h"
#include "ui_admin_reportes.h"

#include "administrador/admin_tarjeta_emeplado_reporte.h"

#include <QDebug>
#include <QSqlQuery>

//#include <QtCharts/QChartView>
//QT_CHARTS_USE_NAMESPACE

admin_reportes::admin_reportes(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admin_reportes)
{
    ui->setupUi(this);

    conexionBD();
    clicked_button(ui->btn_comandas);

    QDate aux = QDate::currentDate();
    int dia = aux.day(), mes = aux.month()-1, anio = aux.year();
    QDate auxDate(anio, mes, dia);
    ui->de_fin->setDate(aux);
    ui->de_incio->setDate(auxDate);

    actualizarDatos();
}

void admin_reportes::conexionBD()
{
    mDatabase = QSqlDatabase::database("Connection");
    if (!mDatabase.isOpen()){
        qDebug() << "ERROR con Base de Datos, esto es: REPORTES";
        return;
    }
    else{
        qDebug() << "Base de datos continua abierta, esto es: REPORTES";
    }
}

void admin_reportes::actualizarDatos()
{
    limpiarGridMeseros();
    //llenar tarjeta comanda
    QSqlQuery infoComandas(mDatabase);
    QString queryComandas = "select count(id_comanda) as 'numeroComandas' from comanda where hora_apertura "
                            "between '"+ui->de_incio->date().toString("yyyy-MM-dd")+"' "
                            "and '"+ui->de_fin->date().toString("yyyy-MM-dd")+"'";
//    qDebug() << queryComandas;
    infoComandas.prepare(queryComandas);
    infoComandas.exec();
    infoComandas.next();

    ui->lb_totalComandas_2->setText(infoComandas.value("numeroComandas").toString());

    //llenar tarejta personas
    QSqlQuery numPersonas(mDatabase);
    QString queryNumPersonas = "select sum(numero_personas) as 'numeroPersonas' from comanda where hora_apertura "
                            "between '"+ui->de_incio->date().toString("yyyy-MM-dd")+"' "
                            "and '"+ui->de_fin->date().toString("yyyy-MM-dd")+"'";
//    qDebug() << queryNumPersonas;
    numPersonas.prepare(queryNumPersonas);
    numPersonas.exec();
    numPersonas.next();

    ui->lb_totalPeronas->setText(numPersonas.value("numeroPersonas").toString());

    //llena tarjeta platillos
    QSqlQuery numPlatillos(mDatabase);
    QString queryNumPlatillos = "select count(id_Pedido) as 'numeroPedidos' from comanda "
                                "inner join pedido on comanda.id_comanda = pedido.Comanda_id_comanda "
                                "where hora_apertura "
                                "between '"+ui->de_incio->date().toString("yyyy-MM-dd")+"' "
                                "and '"+ui->de_fin->date().toString("yyyy-MM-dd")+"'";
//    qDebug() << queryNumPlatillos;
    numPlatillos.prepare(queryNumPlatillos);
    numPlatillos.exec();
    numPlatillos.next();

    ui->lb_totalPlatillos->setText(numPlatillos.value("numeroPedidos").toString());

    //tarjetas meseros
    QSqlQuery meseros(mDatabase);
    QSqlQuery pedidos(mDatabase);

    QString query_mesero = " select "
                           "concat(nombre, ' ', apellido_paterno, ' ', apellido_materno ) as nombre ,"
                           "nombre_tipo,"
                           "count(id_comanda) as comandas,"
                           "sum(numero_personas) as personas "
                           "from comanda "
                           "inner join usuario on usuario.clave = comanda.usuario_clave "
                           "inner join tipo on usuario.Tipo_id_tipo = tipo.id_tipo "
                           "where hora_apertura "
                           "between '"+ui->de_incio->date().toString("yyyy-MM-dd")+"' "
                           "and '"+ui->de_fin->date().toString("yyyy-MM-dd")+"'"
                           "group by Usuario_clave "
                           "order by nombre;";
    QString query_pedidos = " select "
                      "count(id_pedido) as pedidos, "
                      "concat(nombre, ' ', apellido_paterno, ' ', apellido_materno ) as nombre "
                      "from pedido "
                      "inner join comanda on comanda.id_comanda = pedido.Comanda_id_comanda "
                      "inner join usuario on usuario.clave = comanda.usuario_clave "
                      "where hora_apertura "
                      "between '"+ui->de_incio->date().toString("yyyy-MM-dd")+"' "
                      "and '"+ui->de_fin->date().toString("yyyy-MM-dd")+"'"
                      "group by Usuario_clave "
                      "order by nombre;";

    qDebug() << query_mesero;
    qDebug() << query_pedidos;

    meseros.prepare(query_mesero);
    meseros.exec();

    pedidos.prepare(query_pedidos);
    pedidos.exec();
    pedidos.next();

    int row = 0, col = 0;
    while (meseros.next()) {
        QString nombre = meseros.value("nombre").toString();
        QString tipo = meseros.value("nombre_tipo").toString();
        QString comandas = meseros.value("comandas").toString();
        QString platillos = pedidos.value("pedidos").toString();
        QString personas = meseros.value("personas").toString();

        qDebug() << nombre << tipo << comandas << platillos << personas;

        admin_tarjeta_emeplado_reporte *aux = new admin_tarjeta_emeplado_reporte(nombre, tipo, comandas, platillos, personas, this);

        ui->gridLayout_3->addWidget(aux, row, col);
        row++;
        pedidos.next();
    }

//    //Crear la grafica :)
//    QChart *chart = new QChart();
//    chart ->setTitle("Spline chart");
//    QChartView *chartView;
//    chartView = new QChartView(chart);
//    ui->grid_grafica->addWidget(chartView, 0, 0);
}



void admin_reportes::clicked_button(QPushButton *boton)
{
    QString styleOld = "*{ border: none; color: #A6A9A5; margin-left: 10px; margin-right: 10px; } "
                       ":hover{ color: #585858;  margin-left: 10px; margin-right: 10px;  }";
    QString styleNew = "*{ border: none; color: #585858; border-bottom: 3px solid #46B04A; margin-left: 10px; margin-right: 10px; }";
    ui->btn_comandas->setStyleSheet(styleOld);
    ui->btn_transacciones->setStyleSheet(styleOld);
    ui->btn_ventas->setStyleSheet(styleOld);

    boton->setStyleSheet(styleNew);
}

void admin_reportes::limpiarGridMeseros()
{
    while (QLayoutItem *item = ui->gridLayout_3->takeAt(0))
    {
        Q_ASSERT(!item->layout());
        delete item->widget();
        delete item;
    }
}

admin_reportes::~admin_reportes()
{
    delete ui;
}

void admin_reportes::on_btn_ventas_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    clicked_button(ui->btn_ventas);
}

void admin_reportes::on_btn_transacciones_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    clicked_button(ui->btn_transacciones);
}

void admin_reportes::on_btn_comandas_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    clicked_button(ui->btn_comandas);
}

void admin_reportes::on_btn_buscarReporte_clicked()
{
    actualizarDatos();
}
