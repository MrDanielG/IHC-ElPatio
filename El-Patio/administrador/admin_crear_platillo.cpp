#include "admin_crear_platillo.h"
#include "ui_admin_crear_platillo.h"

#include <QDebug>
#include <QMessageBox>
#include <QListWidgetItem>

admin_crear_platillo::admin_crear_platillo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin_crear_platillo)
{
    ui->setupUi(this);
    conexionBD();
    actualizarDatos();
    ui->le_categoria->setHidden(true);
    ui->btn_canNueCategoria->setHidden(true);
}

void admin_crear_platillo::conexionBD()
{
    mDatabase = QSqlDatabase::database("Connection");
    if (!mDatabase.isOpen()){
        qDebug() << "ERROR con Base de Datos, esto es: CREAR PLATILLO";
        return;
    }
    else{
        qDebug() << "Base de datos continua abierta, esto es: CREAR PLATILLO";
    }
}

void admin_crear_platillo::actualizarDatos()
{
    QSqlQuery listaIngredientes(mDatabase);
    QString query = "select * from ingrediente order by nombre;";
    listaIngredientes.prepare(query);

    if(listaIngredientes.exec())
        qDebug() << "listaIngredientes [ejecutado] "    + query;
    else
        qDebug() << "listaIngredientes [no_ejecutado]"  + query;

    while (listaIngredientes.next())
        ui->list_ingreExistente->addItem(listaIngredientes.value("nombre").toString());
}

admin_crear_platillo::~admin_crear_platillo()
{
    delete ui;
}

void admin_crear_platillo::on_list_ingreExistente_itemDoubleClicked(QListWidgetItem *item)
{
    ui->list_ingrePlatillo->addItem(item->text());
    ui->list_ingreExistente->removeItemWidget(item);
    item->~QListWidgetItem();
}

void admin_crear_platillo::on_list_ingrePlatillo_itemDoubleClicked(QListWidgetItem *item)
{
    ui->list_ingreExistente->addItem(item->text());
    ui->list_ingrePlatillo->removeItemWidget(item);
    item->~QListWidgetItem();
}

void admin_crear_platillo::on_btnCrearPlatillo_clicked()
{
    int iterador = 0;
    while (ui->list_ingrePlatillo->item(iterador)) {
        //este regresa constante y takeItem() no lo retorna constante
        qDebug() << ui->list_ingrePlatillo->item(iterador)->text();
        iterador++;
    }

}

void admin_crear_platillo::on_btn_siguiente_clicked()
{
    ui->sW_datosPlatillo->setCurrentIndex(1);
}

void admin_crear_platillo::on_btn_atras_clicked()
{
    ui->sW_datosPlatillo->setCurrentIndex(0);
}

void admin_crear_platillo::on_btn_nuevaCategoria_clicked()
{
    ui->cb_categoria->setHidden(true);
    ui->le_categoria->setHidden(false);
    ui->btn_nuevaCategoria->setHidden(true);
    ui->btn_canNueCategoria->setHidden(false);
}

void admin_crear_platillo::on_btn_canNueCategoria_clicked()
{
    ui->cb_categoria->setHidden(false);
    ui->le_categoria->setHidden(true);
    ui->btn_nuevaCategoria->setHidden(false);
    ui->btn_canNueCategoria->setHidden(true);
}
