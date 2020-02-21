#include "dividircuenta.h"
#include "ui_dividircuenta.h"
#include <QInputDialog>
#include <QDebug>
#include <QAbstractItemView>
#include <QSqlDatabase>
#include <QSqlQuery>

DividirCuenta::DividirCuenta(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DividirCuenta)
{
    ui->setupUi(this);
    mDatabase = QSqlDatabase::database("Connection");
    if(!mDatabase.isOpen()){
        qDebug()<<"ERROR, Dividir Cuenta no conectado";
    }
    ui->btnAceptar->hide();
    ui->tablaCuenta->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tablaCuenta->verticalHeader()->setVisible(false);
    ui->tablaCuenta->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    //Cambiar el 20 por el atributo idComanda
    QString script;
    script = "select plat.nombre, plat.precio from comanda as"
             " com inner join pedido as p on"
             " p.Comanda_id_comanda = com.id_comanda"
             " inner join platillo as plat on"
             " plat.id_platillo = p.Platillo_id_platillo where com.id_comanda = 1";
    QString total;
    total = "select sum(plat.precio) as Total from comanda as"
            " com inner join pedido as p on"
            " p.Comanda_id_comanda = com.id_comanda"
            " inner join platillo as plat on"
            " plat.id_platillo = p.Platillo_id_platillo where com.id_comanda = 1";
    llenaCuentaPrincipal(script,total);
    connect(ui->btnDividir,SIGNAL(clicked()), this, SLOT(Dividir()));
}

DividirCuenta::~DividirCuenta()
{
    delete ui;
}

void DividirCuenta::setIdComanda(QString idC)
{
    idComanda = idC;
}

void DividirCuenta::setIdMesero()
{
    QString val;
    QSqlQuery query(mDatabase);
    query.prepare("SELECT Usuario_clave FROM comanda WHERE id_comanda = "+idComanda+"");
    query.exec();
    if(query.next())
        val = query.value(0).toString();
    ui->nombreMesero->setText(val);
}

void DividirCuenta::Dividir()
{
    ui->btnAceptar->show();
    ui->btnPagar->hide();
    ui->btnDividir->hide();
    bool ok;
    QInputDialog InpDia;
    int n = InpDia.getInt(this,tr("Número de cuentas a dividir "),tr("Dividir"),2,2,4,1,&ok);
    int width, height = 520, x = 30, y = 230;
    int espacio = n + 1;
    width = (1024 - (espacio*30)) / n;
    ui->tablaCuenta->setGeometry(x,y,width,height);
    for(int i = 2; i <= n; i++)
    {
        QStringList encabezado;
        encabezado << "Nombre" << "Precio";
        QTableWidget * auxCuenta = new QTableWidget(this);
        auxCuenta->setDragDropMode(QAbstractItemView::DragDrop);
        auxCuenta->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        auxCuenta->verticalHeader()->setVisible(false);
        auxCuenta->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        auxCuenta->setHorizontalHeaderItem(0, new QTableWidgetItem("Nombre"));
        auxCuenta->setHorizontalHeaderItem(1, new QTableWidgetItem("Precio"));
        x += 30 + width;
        auxCuenta->setGeometry(x,y,width,height);
        auxCuenta->show();
    }
}

void DividirCuenta::llenaCuentaPrincipal(QString script, QString script2)
{
    QSqlQuery query(mDatabase);
    query.prepare(script);
    query.exec();
    while(query.next())
    {
        QString nombre = query.value(0).toString();
        QString precio = query.value(1).toString();

        ui->tablaCuenta->insertRow(ui->tablaCuenta->rowCount());

        int filaEmp = ui->tablaCuenta->rowCount()-1;

        ui->tablaCuenta->setItem(filaEmp,0,new QTableWidgetItem(nombre));
        ui->tablaCuenta->setItem(filaEmp,1,new QTableWidgetItem(precio));

    }
    QSqlQuery query2(mDatabase);
    query2.prepare(script2);
    query2.exec();
    while(query2.next())
    {
        QString total = query2.value(0).toString();

        ui->tablaCuenta->insertRow(ui->tablaCuenta->rowCount());

        int filaEmp = ui->tablaCuenta->rowCount()-1;
        ui->tablaCuenta->setItem(filaEmp,0,new QTableWidgetItem("Total:"));
        ui->tablaCuenta->setItem(filaEmp,1,new QTableWidgetItem(total));
    }

}
