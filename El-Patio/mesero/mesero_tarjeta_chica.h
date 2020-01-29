#ifndef MESERO_TARJETA_CHICA_H
#define MESERO_TARJETA_CHICA_H

#include <QWidget>
#include <QSqlDatabase>

namespace Ui {
class mesero_tarjeta_chica;
}

class mesero_tarjeta_chica : public QWidget
{
    Q_OBJECT

public:
    explicit mesero_tarjeta_chica(int, QWidget *parent = nullptr);
    float get_precio();
    ~mesero_tarjeta_chica();

private:
    Ui::mesero_tarjeta_chica *ui;
    //conexion BD
    QSqlDatabase mDatabase;

    //datos platillo
    int id_platillo;
    float precio;
    QString nombre;
};

#endif // MESERO_TARJETA_CHICA_H
