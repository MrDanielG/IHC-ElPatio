#include "reservacionesagendadas.h"
#include "ui_reservacionesagendadas.h"
#include "reservaciondelegate.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSortFilterProxyModel>
#include <QSqlRelationalTableModel>
#include <QDebug>

reservacionesAgendadas::reservacionesAgendadas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reservacionesAgendadas),
    reservasModel(new QSqlQueryModel(this)),
    reservasProxyModel(new QSortFilterProxyModel(this))
{
    ui->setupUi(this);
}

reservacionesAgendadas::~reservacionesAgendadas()
{
    delete reservasModel;
    delete reservasProxyModel;
    delete ui;
}

void reservacionesAgendadas::recargar()
{
    QString script;

    reservasModel->setQuery(script, QSqlDatabase::database("Connection"));

    reservasProxyModel->setSourceModel(reservasModel);
    ui->reservasListView->setModel(reservasProxyModel);
    auto curDelegate = ui->reservasListView->itemDelegate();
    ui->reservasListView->setItemDelegate(new reservacionDelegate(this));
    if(curDelegate)
        delete curDelegate;

    ui->reservasListView->show();
}
