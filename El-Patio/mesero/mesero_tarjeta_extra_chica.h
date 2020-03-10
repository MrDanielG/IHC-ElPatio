#ifndef MESERO_TARJETA_EXTRA_CHICA_H
#define MESERO_TARJETA_EXTRA_CHICA_H

#include <QWidget>
#include <models/extra.h>

class mesero_editar_platillo;
namespace Ui {
class mesero_tarjeta_extra_chica;
}

class mesero_tarjeta_extra_chica : public QWidget
{
    Q_OBJECT

public:
    explicit mesero_tarjeta_extra_chica(extra, mesero_editar_platillo *parent = nullptr);
    ~mesero_tarjeta_extra_chica();
    void llenarTarjeta();

private slots:
    void on_btnMasExtra_clicked();

    void on_btnMenosExtra_clicked();

private:
    Ui::mesero_tarjeta_extra_chica *ui;
    mesero_editar_platillo *padre;
    extra extraPlatillo;
};

#endif // MESERO_TARJETA_EXTRA_CHICA_H
