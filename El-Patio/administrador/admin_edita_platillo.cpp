#include "admin_edita_platillo.h"
#include "ui_admin_edita_platillo.h"

admin_edita_platillo::admin_edita_platillo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin_edita_platillo)
{
    ui->setupUi(this);
}

admin_edita_platillo::~admin_edita_platillo()
{
    delete ui;
}
