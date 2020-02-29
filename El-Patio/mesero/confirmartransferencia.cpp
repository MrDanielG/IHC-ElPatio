#include "confirmartransferencia.h"
#include "ui_confirmartransferencia.h"

#include <QDebug>

ConfirmarTransferencia::ConfirmarTransferencia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfirmarTransferencia)
{
    ui->setupUi(this);
}

ConfirmarTransferencia::~ConfirmarTransferencia()
{
    delete ui;
}

QString ConfirmarTransferencia::get_claveAdmin()
{
    return claveAdmin;
}

void ConfirmarTransferencia::on_buttonBox_accepted()
{
    this->claveAdmin = ui->le_claveAdmin->text();
}
