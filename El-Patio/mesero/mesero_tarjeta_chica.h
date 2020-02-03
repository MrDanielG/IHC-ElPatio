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
    explicit mesero_tarjeta_chica(QString, QString, QString, QString, int, QWidget *parent = nullptr);
    explicit mesero_tarjeta_chica(int, QWidget *parent = nullptr);
    ~mesero_tarjeta_chica();
    void llenarTarjeta();
    float get_precio();

private:
    Ui::mesero_tarjeta_chica *ui;
    QString id;
    QString nombrePlatillo;
    QString precioPlatillo;
    QString foto;
    int cantidad = 0;

    //conexion BD
    QSqlDatabase mDatabase;
};

#endif // MESERO_TARJETA_CHICA_H
