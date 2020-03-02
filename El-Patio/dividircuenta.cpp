#include "dividircuenta.h"
#include "ui_dividircuenta.h"
#include <QInputDialog>
#include <QDebug>
#include <QAbstractItemView>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QLabel>
#include "administrador/agregar_propina_cuenta.h"

DividirCuenta::DividirCuenta(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DividirCuenta)
{
    ui->setupUi(this);
    mDatabase = QSqlDatabase::database("Connection");
    if(!mDatabase.isOpen()){
        qDebug()<<"ERROR, Dividir Cuenta no conectado";
    }
    ui->btnCancelar->hide();
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
    cuentas[0] = ui->tablaCuenta;
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
    ui->tablaCuenta->setDragDropMode(QAbstractItemView::DragDrop);
    ui->btnAceptar->show();
    ui->btnDividir->hide();
    ui->btnPagar->hide();
    ui->total->hide();
    ui->btnCancelar->show();
    total[0] = ui->total;
    bool ok;
    QInputDialog InpDia;
    int n = InpDia.getInt(this,tr("Número de cuentas a dividir "),tr("Dividir"),2,2,4,1,&ok);
    numeroCuenta = n;
    int width, height = 380, x = 30, y = 230;
    int espacio = n + 1;
    width = (1024 - (espacio*30)) / n;
    ui->tablaCuenta->setGeometry(x,y,width,height);
    for(int i = 2; i <= n; i++)
    {
        QStringList encabezado;
        encabezado << "Nombre" << "Precio";
        QTableWidget * auxCuenta = new QTableWidget(this);
        cuentas[i-1] = auxCuenta;
        auxCuenta->setDragDropMode(QAbstractItemView::DragDrop);
        auxCuenta->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        auxCuenta->verticalHeader()->setVisible(false);
        auxCuenta->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        auxCuenta->setHorizontalHeaderItem(0, new QTableWidgetItem("Nombre"));
        auxCuenta->setHorizontalHeaderItem(1, new QTableWidgetItem("Precio"));
        auxCuenta->setSelectionMode(QAbstractItemView::SingleSelection);
        auxCuenta->setSelectionBehavior(QAbstractItemView::SelectRows);
        auxCuenta->setDefaultDropAction(Qt::DropAction::MoveAction);
        x += 30 + width;
        auxCuenta->setGeometry(x,y,width,height);
        auxCuenta->show();
        QLabel * totalLabel = new QLabel(this);
        total[i-1] = totalLabel;
        totalLabel->setText("Total: $");
        totalLabel->setGeometry(x+150,height+y+20,120,20);
        QFont f("Roboto",12,QFont::Normal);
        totalLabel->setFont(f);
        totalLabel->hide();
    }
}

void DividirCuenta::llenaCuentaPrincipal(QString script, QString script2)
{
    while(ui->tablaCuenta->rowCount()){
        ui->tablaCuenta->removeRow(ui->tablaCuenta->rowCount()-1);
    }
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
        Totales.append(total);

        //ui->tablaCuenta->insertRow(ui->tablaCuenta->rowCount());

        //int filaEmp = ui->tablaCuenta->rowCount()-1;
        //ui->tablaCuenta->setItem(filaEmp,0,new QTableWidgetItem("Total:"));
        //ui->tablaCuenta->setItem(filaEmp,1,new QTableWidgetItem(total));
        ui->total->setText("Total: $"+total);
    }

}

void DividirCuenta::on_btnAceptar_clicked()
{
    ui->btnPagar->show();
    Totales.pop_front();
    for(int i = 0; i < numeroCuenta; i++)
    {
        cuentas[i]->setDragDropMode(QAbstractItemView::NoDragDrop);
        total[i]->show();
        int auxFilas = cuentas[i]->rowCount();
        int auxCuenta = 0;
        for(int j = 0; j < auxFilas; j++)
        {
            auxCuenta = auxCuenta + cuentas[i]->item(j,1)->text().toInt();
        }
        total[i]->setText("Total: $"+QString::number(auxCuenta));
        Totales.append(QString::number(auxCuenta));
    }
}

void DividirCuenta::on_btnCancelar_clicked()
{
    ui->btnCancelar->hide();
    ui->btnAceptar->hide();
    ui->btnDividir->show();
    for(int i = 1; i < numeroCuenta; i++)
    {
        delete(cuentas[i]);
        delete(total[i]);
    }
    ui->tablaCuenta->setGeometry(30,230,660,380);
    ui->total->show();
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

}

void DividirCuenta::on_btnPagar_clicked()
{
    //TODO: Mandar idComanda
    //Propina = new agregar_propina_cuenta(Totales, idComanda, this);
    Propina = new agregar_propina_cuenta(Totales, "20", this);
    Propina->exec();
    //TODO Ver a dónde devuelve esto, en términos de navegación
}
