#include "almacenista_menu.h"
#include "ui_almacenista_menu.h"
#include "almacenista/almacenista_crear_insumo.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSortFilterProxyModel>
#include <QSqlRelationalTableModel>
#include <QMessageBox>
#include <QDate>

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
                     " from insumo as ins inner join perecedero as ing"
                     " where ins.id_insumo = ing.id_insumo";
    llenarTabla(script);
    QFont fuente("Roboto", 12, QFont::Bold);
    ui->btnTodo->setFont(fuente);

    QSqlQuery query(mDatabase);
    QString scrp = "select ins.id_insumo,ins.nombre, ins.precio_compra,"
                   " ins.existencias, ins.presentacion from insumo"
                   " as ins inner join perecedero as ing where ins.id_insumo = 1;";
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

    QString auxPrecio = ui->lb_precio_insumo->text();
    QString auxExist = ui->lb_existencias_insumo->text();
    QString auxPresent = ui->lb_presentacion_insumo->text();

    ui->spinBox_precio->setValue(auxPrecio.toFloat());
    ui->spinBox_existencias->setValue(auxExist.toInt());
    ui->ln_presentacion->setText(auxPresent);

    QString disableStyle = "*{color: #539E56; border-radius: 10px;"
                          " background-color: #E3EFB0; border: none;"
                          " padding: 5px; }"
                          " :hover{ background-color: white; "
                          "border: 1px solid #46B04A; color: #46B04A; }";
    ui->btn_guardar->setStyleSheet(disableStyle);
    ui->btn_guardar->setEnabled(false);
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
        QString filtro = script + " && ins.nombre like '%"+arg1+"%'";
        llenarTabla(filtro);
    }
}

void almacenista_menu::on_tablaInsumos_clicked(const QModelIndex &index)
{
    //Mostrar elementos ocultos
    ui->spinBox_existencias->setValue(0);
    ui->spinBox_precio->setValue(0);
    ui->ln_presentacion->setText("");
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

    int row = index.row();
    id = ui->tablaInsumos->model()->index(row,0).data().toString();

    QSqlQuery query(mDatabase);
    QString scrp = "select ins.id_insumo,ins.nombre, ins.precio_compra,"
                   " ins.existencias, ins.presentacion from insumo"
                   " as ins inner join perecedero as ing where ins.id_insumo = "+id+"";
    query.prepare(scrp);
    if(query.exec())
    {
        query.next();
        QString nombre = query.value(1).toString();
        QString clave = query.value(0).toString();
        QString precio = query.value(2).toString();

        QString existencias = query.value(3).toString();
        existenciasOriginales = query.value(3).toInt();

        QString presentacion = query.value(4).toString();
        ui->lb_id_insumo->setText(clave);
        ui->lb_nombre_insumo->setText(nombre);
        ui->lb_precio_insumo->setText(precio);
        ui->lb_existencias_insumo->setText(existencias);
        ui->lb_presentacion_insumo->setText(presentacion);
    }
    query.finish();
}

void almacenista_menu::on_btnEliminarInsumo_clicked()
{
    qDebug() << "Existencias originales " << existenciasOriginales;
    if(existenciasOriginales != 0){
        QMessageBox::warning(this, tr("Alerta"), tr("Aún hay registro de existencias de "
                                                   "este insumo, no puede ser eliminado"));
    }
    else{
        QSqlQuery query(mDatabase);
        QString scrp = "select id_transaccion from transaccion"
                       " where id_insumo = "+id+"";
        query.prepare(scrp);
        if(query.exec()){
            if(query.next()){
                if(QMessageBox::question(this, tr("Desactivar insumo"), tr("¿Está seguro que desea desactivar este insumo?"))==QMessageBox::Yes){
                    QString desactivar = "update insumo set estado = 'inactivo' where id_insumo = "+id+"";
                    query.finish();
                    query.prepare(desactivar);
                    if(query.exec())
                        QMessageBox::information(this, tr("Éxito"), tr("El insumo fue desactivado"));//Ocultar
                    else QMessageBox::warning(this, tr("Error"), tr("El insumo no pudo ser desactivado."));
                }
            }
            else{
                qDebug() << "sí la wa borrar eñe";//Eliminar
            }
        }

    }
}
void almacenista_menu::on_btnTodo_clicked()
{
    QFont fuente("Roboto", 12, QFont::Bold);
    QFont fuente2("Roboto", 12);
    if(ui->btnTodo->font() != fuente)
    {
        ui->btnTodo->setFont(fuente);
        ui->btnPlatillos->setFont(fuente2);
        ui->btnBebidas->setFont(fuente2);
        script = "select ins.id_insumo,ins.nombre, ins.precio_compra, ins.existencias,"
                         " ins.presentacion, ing.fecha_almacenamiento, ing.dias_caducidad"
                         " from insumo as ins inner join perecedero as ing"
                         " where ins.id_insumo = ing.id_insumo";
        llenarTabla(script);
    }
}

void almacenista_menu::on_btnPlatillos_clicked()
{
    QFont fuente("Roboto", 12, QFont::Bold);
    QFont fuente2("Roboto", 12);
    if(ui->btnPlatillos->font() != fuente)
    {
        ui->btnPlatillos->setFont(fuente);
        ui->btnBebidas->setFont(fuente2);
        ui->btnTodo->setFont(fuente2);
        script = "SELECT * FROM insumo WHERE id_insumo not in (SELECT id_insumo from perecedero);";
        llenarTabla(script);
    }
}

void almacenista_menu::on_btnBebidas_clicked()
{
    QFont fuente("Roboto", 12, QFont::Bold);
    QFont fuente2("Roboto", 12);
    if(ui->btnBebidas->font() != fuente)
    {
        ui->btnBebidas->setFont(fuente);
        ui->btnTodo->setFont(fuente2);
        ui->btnPlatillos->setFont(fuente2);
        script = "select * from insumo where existencias = 0;";
        llenarTabla(script);
    }
}

void almacenista_menu::on_btn_guardar_clicked()
{
    //TODO id del empleado

    QString fecha = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:z");
    QString cantidad = ui->spinBox_existencias->text();
    QString id_insumo = ui->lb_id_insumo->text();
    QString clave = "101";

    QString query_transaccion =
            "INSERT INTO `el_patio`.`transaccion` "
            "(`fecha_hora`, `cantidad`, `tipo`, `comentario`, `clave`, `id_insumo`)"
            "VALUES ('" +fecha+ "', '" +cantidad+ "', 'entrada', 'S/C', '" +clave+ "', ' " +id_insumo+ " ');";

    qDebug() << query_transaccion;
    QMessageBox::information(this, ui->lb_id_insumo->text(), query_transaccion);
}

void almacenista_menu::on_btn_agregar_insumo_clicked()
{
    almacenista_crear_insumo *crearInsumo = new almacenista_crear_insumo(this) ;
    crearInsumo->exec();
}

void almacenista_menu::on_spinBox_precio_valueChanged(const QString &arg1)
{
    QString enableStyle = "*{color: white; border-radius: 10px; "
                          "background-color: #46B04A; border: none; padding: 5px; }"
                          "  :hover{ background-color: white; "
                          "border: 1px solid #46B04A; color: #46B04A; }";
    ui->btn_guardar->setStyleSheet(enableStyle);
    ui->btn_guardar->setEnabled(true);
}

void almacenista_menu::on_spinBox_existencias_valueChanged(const QString &arg1)
{
    QString enableStyle = "*{color: white; border-radius: 10px; "
                          "background-color: #46B04A; border: none; padding: 5px; }"
                          "  :hover{ background-color: white; "
                          "border: 1px solid #46B04A; color: #46B04A; }";
    ui->btn_guardar->setStyleSheet(enableStyle);
    ui->btn_guardar->setEnabled(true);
}

void almacenista_menu::on_ln_presentacion_textChanged(const QString &arg1)
{
    QString enableStyle = "*{color: white; border-radius: 10px; "
                          "background-color: #46B04A; border: none; padding: 5px; }"
                          "  :hover{ background-color: white; "
                          "border: 1px solid #46B04A; color: #46B04A; }";
    ui->btn_guardar->setStyleSheet(enableStyle);
    ui->btn_guardar->setEnabled(true);
}

void almacenista_menu::on_btn_guardar_clicked()
{
    QString id,precio1, precio2, present1, present2,exist1, exist2;

    id = ui->lb_id_insumo->text();
    precio1 = ui->lb_precio_insumo->text();
    precio2 = ui->spinBox_precio->text();
    exist1 = ui->lb_existencias_insumo->text();
    exist2 = ui->spinBox_existencias->text();
    present1 = ui->lb_presentacion_insumo->text();
    present2 = ui->ln_presentacion->text();

    if((precio1 != precio2) || (exist1 != exist2) || (present1 != present2))
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirmacion: ", "¿Está seguro de actualizar los datos del insumo?",
                                        QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            QSqlQuery query(mDatabase);
            QString sql = "UPDATE insumo SET precio_compra = "+precio2+", existencias = "+exist2+" , presentacion = '"+present2+"' WHERE id_insumo = "+id+"";
            query.prepare(sql);
            query.exec();
        }
    }

    llenarTabla(script);
    ui->lb_id_insumo->setText("");
    ui->lb_precio_insumo->setText("");
    ui->lb_existencias_insumo->setText("");
    ui->lb_precio_insumo->setText("");
    ui->lb_presentacion_insumo->setText("");
    ui->lb_nombre_insumo->setText("");
    ui->spinBox_precio->setValue(0);
    ui->spinBox_existencias->setValue(0);
    ui->ln_presentacion->setText("");
    on_btn_cancelar_clicked();
}
