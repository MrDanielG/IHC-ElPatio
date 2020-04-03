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

void reservaItemWidget::setDatos(const QMap<QString, QString> &datos)
{
   ui->Reservacion->setText(datos["reservacion"]);
   ui->Mesa->setText(datos["mesa"]);
   ui->Fecha->setText(datos["fecha"]);
   ui->Hora->setText(datos["hora"]);
   ui->Cliente->setText(datos["cliente"]);
   ui->Personas->setText(datos["personas"]);
}
