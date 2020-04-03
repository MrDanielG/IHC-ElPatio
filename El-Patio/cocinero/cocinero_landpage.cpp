#include "cocinero_landpage.h"
#include "ui_cocinero_landpage.h"

cocinero_landpage::cocinero_landpage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cocinero_landpage)
{
    ui->setupUi(this);
}

cocinero_landpage::~cocinero_landpage()
{
    delete ui;
}
