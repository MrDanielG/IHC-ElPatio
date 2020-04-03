#include "admin_reportes.h"
#include "ui_admin_reportes.h"

#include "administrador/admin_tarjeta_emeplado_reporte.h"

#include <QDebug>
#include <QSqlQuery>

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
QT_CHARTS_USE_NAMESPACE

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
    actualizarDatosTransaccion();
    actualizarDatosVentas();
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

void admin_reportes::actualizarDatosTransaccion()
{
    QSqlQuery transacciones(mDatabase);
    QString qTransa = "select count(id_transaccion) as transacciones from transaccion where fecha_hora "
                      "between '"+ui->de_incio->date().toString("yyyy-MM-dd")+"' "
                      "and '"+ui->de_fin->date().toString("yyyy-MM-dd")+"'";
    transacciones.exec(qTransa);
    transacciones.next();
    ui->lb_totalTran->setText(transacciones.value("transacciones").toString());

    //no perecederos
    QSqlQuery outNPerece(mDatabase);
    QString qNPerecedero = "select count(id_transaccion) as transacciones from insumo "
                          "inner join transaccion on transaccion.id_insumo = insumo.id_insumo "
                          "WHERE insumo.id_insumo not in (SELECT id_insumo from perecedero) and "
                          "fecha_hora "
                          "between '"+ui->de_incio->date().toString("yyyy-MM-dd")+"' "
                          "and '"+ui->de_fin->date().toString("yyyy-MM-dd")+"' "
                          "and tipo = 'salida';";
    outNPerece.exec(qNPerecedero);
    outNPerece.next();
    ui->lb_nPereSalida->setText(outNPerece.value("transacciones").toString());

    QSqlQuery inNPerece(mDatabase);
    qNPerecedero = "select count(id_transaccion) as transacciones from insumo "
                              "inner join transaccion on transaccion.id_insumo = insumo.id_insumo "
                              "WHERE insumo.id_insumo not in (SELECT id_insumo from perecedero) and "
                              "fecha_hora "
                              "between '"+ui->de_incio->date().toString("yyyy-MM-dd")+"' "
                              "and '"+ui->de_fin->date().toString("yyyy-MM-dd")+"' "
                              "and tipo = 'entrada';";
    inNPerece.exec(qNPerecedero);
    inNPerece.next();
    ui->lb_nPereEntrada_2->setText(inNPerece.value("transacciones").toString());

    //perecederos
    QSqlQuery outPerece(mDatabase);
    QString qPerece = "select count(id_transaccion) as transacciones from insumo "
                      "inner join transaccion on transaccion.id_insumo = insumo.id_insumo "
                      "where insumo.id_insumo not in (SELECT id_insumo FROM insumo WHERE id_insumo not in (SELECT id_insumo from perecedero)) and "
                      "fecha_hora "
                      "between '"+ui->de_incio->date().toString("yyyy-MM-dd")+"' "
                      "and '"+ui->de_fin->date().toString("yyyy-MM-dd")+"' "
                      "and tipo = 'salida';";
    outPerece.exec(qPerece);
    outPerece.next();
    ui->lb_pereEntrada_2->setText(outPerece.value("transacciones").toString());

    QSqlQuery inPerece(mDatabase);
    qPerece = "select count(id_transaccion) as transacciones from insumo "
                          "inner join transaccion on transaccion.id_insumo = insumo.id_insumo "
                          "where insumo.id_insumo not in (SELECT id_insumo FROM insumo WHERE id_insumo not in (SELECT id_insumo from perecedero)) and "
                          "fecha_hora "
                          "between '"+ui->de_incio->date().toString("yyyy-MM-dd")+"' "
                          "and '"+ui->de_fin->date().toString("yyyy-MM-dd")+"' "
                          "and tipo = 'entrada';";
    inPerece.exec(qPerece);
    inPerece.next();
    ui->lb_pereSalida_2->setText(inPerece.value("transacciones").toString());

    QSqlQuery countTran(mDatabase);
    QString numTran = "select comentario, count(comentario) as numComentario from transaccion where "
                      "fecha_hora between '"+ui->de_incio->date().toString("yyyy-MM-dd")+"' "
                      "and '"+ui->de_fin->date().toString("yyyy-MM-dd")+"' "
                      "group by comentario order by comentario;";
    countTran.exec(numTran);

    //grafica pie chart
    DataTable dataTable;
    DataList dataList;

    int it=0;
    while (countTran.next()) {
        dataList << Data(QPointF((qreal) it,
                                 (qreal) countTran.value("numComentario").toFloat()),
                                  countTran.value("comentario").toString() + " " + countTran.value("numComentario").toString());
        it++;
    }
    dataTable << dataList;

    QChart *chart = new QChart();
//    chart->setTitle("Porcentaje de Tranferencias");

    QPieSeries *series = new QPieSeries(chart);
    for (const Data &data : dataTable[0]) {
        QPieSlice *slice = series->append(data.second, data.first.y());
        slice->setLabelVisible();
        slice->setExploded();
        slice->setExplodeDistanceFactor(0.05);
    }
    series->setPieSize(0.6);
    chart->addSeries(series);

    QChartView *chartView = new QChartView(chart);
    chartView->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->gridGrafica->addWidget(chartView, 0, 0);
    chartView->chart()->legend()->setAlignment(Qt::AlignLeft);

}

void admin_reportes::actualizarDatosVentas()
{

    QSqlQuery topVentas(mDatabase);
    QString query_topVentas = "select foto, nombre, COUNT(nombre) as num from ticket "
                              "inner join comanda on ticket.Comanda_id_comanda = comanda.id_comanda "
                              "inner join pedido on pedido.Comanda_id_comanda = comanda.id_comanda "
                              "inner join platillo on platillo.id_platillo = pedido.Platillo_id_platillo "
                              "where fecha between '"+ui->de_incio->date().toString("yyyy-MM-dd")+"' "
                              "and '"+ui->de_fin->date().toString("yyyy-MM-dd")+"'"
                              "group by nombre order by num "
                              "limit 3; ";
    topVentas.exec(query_topVentas);

    //top 1 de ventas de platillos
    topVentas.next();
    QPixmap img1(topVentas.value("foto").toString());
    ui->lb_fotoPlatillo1->setPixmap(img1);
    ui->lb_nombrePlatillo1->setText(topVentas.value("nombre").toString());
    ui->lb_totalPlatillo1->setText(topVentas.value("num").toString());

    //top 2 de ventas de platillos
    topVentas.next();
    QPixmap img2(topVentas.value("foto").toString());
    ui->lb_fotoPlatillo2->setPixmap(img2);
    ui->lb_nombrePlatillo2->setText(topVentas.value("nombre").toString());
    ui->lb_totalPlatillo2->setText(topVentas.value("num").toString());

    //top 3 de ventas de platillos
    topVentas.next();
    QPixmap img3(topVentas.value("foto").toString());
    ui->lb_fotoPlatillo3->setPixmap(img3);
    ui->lb_nombrePlatillo3->setText(topVentas.value("nombre").toString());
    ui->lb_totalPlatillo3->setText(topVentas.value("num").toString());
    qDebug() << "11111111";

    //obtener el total de los dineros
    QSqlQuery totalDineros(mDatabase);
    QString query_totalDineros = "select sum(total) as total from ticket "
                           "where fecha between '"+ui->de_incio->date().toString("yyyy-MM-dd")+"' "
                           "and '"+ui->de_fin->date().toString("yyyy-MM-dd")+"'";
    totalDineros.exec(query_totalDineros);
    totalDineros.next();
    ui->lb_totalDinero->setText(totalDineros.value("total").toString());
    qDebug() << "222222222";

    //total de tickets
    QSqlQuery totalTickets(mDatabase);
    QString query_totalTickets = " select count(id_ticket) as numTickets from ticket "
                           "where fecha "
                           "between '"+ui->de_incio->date().toString("yyyy-MM-dd")+"' "
                           "and '"+ui->de_fin->date().toString("yyyy-MM-dd")+"'";

    totalTickets.exec(query_totalTickets);
    totalTickets.next();
    ui->lb_totalTickets->setText(totalTickets.value("numTickets").toString());
    qDebug() << "33333333333";

    //total de pagos por tarjeta y efectivo
    QSqlQuery totalMetodos(mDatabase);
    QString query_totoalMetodos = "select metodo, COUNT(metodo) as totalMetodo from ticket "
                                  "where fecha between '"+ui->de_incio->date().toString("yyyy-MM-dd")+"' "
                                  "and '"+ui->de_fin->date().toString("yyyy-MM-dd")+"'"
                                  "group by metodo order by metodo;";
    totalMetodos.exec(query_totoalMetodos);
    //efectivo
    totalMetodos.next();
    ui->lb_totalEfectivo->setText(totalMetodos.value("totalMetodo").toString());
    //tarjeta
    totalMetodos.next();
    ui->lb_totalTarjeta->setText(totalMetodos.value("totalMetodo").toString());
    qDebug() << "44444444444";
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
    actualizarDatosTransaccion();
    actualizarDatosVentas();
}
