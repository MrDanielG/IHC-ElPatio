#include "dividircuenta.h"
#include "ui_dividircuenta.h"
#include <QInputDialog>


DividirCuenta::DividirCuenta(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DividirCuenta)
{
    ui->setupUi(this);

    connect(ui->btnDividir,SIGNAL(clicked()), this, SLOT(Dividir()));

}

DividirCuenta::~DividirCuenta()
{
    delete ui;
}

void DividirCuenta::setIdComanda(QString idC)
{

}

void DividirCuenta::setIdMesero(int idM)
{
    ui->nombreMesero->setText(QString::number(idM));
}

void DividirCuenta::Dividir()
{
    bool ok;
    QInputDialog InpDia;
    int n = InpDia.getInt(this,tr("Número de cuentas a dividir "),tr("Dividir"),2,2,4,1,&ok);
    int width = 1024, height = 520, x = 30, y = 230;
    QTableView * auxCuenta = new QTableView(this);
    ui->tablaCuenta->setGeometry(30,230,422,520);
    auxCuenta->show();
    auxCuenta->setGeometry(30+422,230,422,520);
}
