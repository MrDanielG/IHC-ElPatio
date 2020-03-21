#ifndef ADMIN_TARJETA_EMEPLADO_REPORTE_H
#define ADMIN_TARJETA_EMEPLADO_REPORTE_H

#include <QWidget>

namespace Ui {
class admin_tarjeta_emeplado_reporte;
}

class admin_tarjeta_emeplado_reporte : public QWidget
{
    Q_OBJECT

public:
    explicit admin_tarjeta_emeplado_reporte(QWidget *parent = nullptr);
    admin_tarjeta_emeplado_reporte(QString nombre, QString tipoEmpleado, QString numComandas, QString numPlatillos, QString numPersonas, QWidget *parent = nullptr);
    void asignarDatos();
    ~admin_tarjeta_emeplado_reporte();

private:
    Ui::admin_tarjeta_emeplado_reporte *ui;

    QString nombre;
    QString tipoEmpleado;
    QString numComandas;
    QString numPlatillos;
    QString numPersonas;
};

#endif // ADMIN_TARJETA_EMEPLADO_REPORTE_H
