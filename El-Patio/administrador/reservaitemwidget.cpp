#include "reservaitemwidget.h"
#include "ui_reservaitemwidget.h"

reservaItemWidget::reservaItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::reservaItemWidget)
{
    ui->setupUi(this);
}

reservaItemWidget::~reservaItemWidget()
{
    delete ui;
}
