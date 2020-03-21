#include "admin_tarjeta_emeplado_reporte.h"
#include "ui_admin_tarjeta_emeplado_reporte.h"

admin_tarjeta_emeplado_reporte::admin_tarjeta_emeplado_reporte(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admin_tarjeta_emeplado_reporte)
{
    ui->setupUi(this);
}

admin_tarjeta_emeplado_reporte::admin_tarjeta_emeplado_reporte(QString nombre, QString tipoEmpleado, QString numComandas, QString numPlatillos, QString numPersonas, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admin_tarjeta_emeplado_reporte)
{
    ui->setupUi(this);

    this->nombre = nombre;
    this->tipoEmpleado = tipoEmpleado;
    this->numComandas = numComandas;
    this->numPlatillos = numPlatillos;
    this->numPersonas = numPersonas;

    asignarDatos();
}

void admin_tarjeta_emeplado_reporte::asignarDatos()
{
    ui->lb_nombre->setText(nombre);
    ui->lb_tipoEmpleado->setText(tipoEmpleado);
    ui->lb_numComandas->setText(numComandas + " realizadas");
    ui->lb_numPlatillos->setText(numPlatillos + " entregados");
    ui->lb_numPersonas->setText(numPersonas + " atendidas");
}

admin_tarjeta_emeplado_reporte::~admin_tarjeta_emeplado_reporte()
{
    delete ui;
}
