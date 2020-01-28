#ifndef MESERO_TARJETA_CHICA_H
#define MESERO_TARJETA_CHICA_H

#include <QWidget>

namespace Ui {
class mesero_tarjeta_chica;
}

class mesero_tarjeta_chica : public QWidget
{
    Q_OBJECT

public:
    explicit mesero_tarjeta_chica(QString, QString, QString, QString, int, QWidget *parent = nullptr);
    ~mesero_tarjeta_chica();
    void llenarTarjeta();

private:
    Ui::mesero_tarjeta_chica *ui;
    QString id;
    QString nombrePlatillo;
    QString precioPlatillo;
    QString foto;
    int cantidad = 0;
};

#endif // MESERO_TARJETA_CHICA_H
