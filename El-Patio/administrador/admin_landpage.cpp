#include "admin_landpage.h"
#include "ui_admin_landpage.h"

admin_landpage::admin_landpage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admin_landpage)
{
    ui->setupUi(this);
}

admin_landpage::~admin_landpage()
{
    delete ui;
}
