#ifndef MESERO_TARJETA_EXTRA_H
#define MESERO_TARJETA_EXTRA_H

#include <QWidget>
#include <models/extra.h>

class mesero_editar_platillo;

namespace Ui {
class mesero_tarjeta_extra;
}

class mesero_tarjeta_extra : public QWidget
{
    Q_OBJECT

public:
    explicit mesero_tarjeta_extra(extra, mesero_editar_platillo *parent = nullptr);
    ~mesero_tarjeta_extra();
    void llenarTarjeta();

private slots:
    void on_btnMasExtra_clicked();

private:
    Ui::mesero_tarjeta_extra *ui;
    extra extraPlatillo;
    mesero_editar_platillo *padre;
};

#endif // MESERO_TARJETA_EXTRA_H
