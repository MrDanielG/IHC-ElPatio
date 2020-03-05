#ifndef MESERO_TARJETA_EXTRA_CHICA_H
#define MESERO_TARJETA_EXTRA_CHICA_H

#include <QWidget>

namespace Ui {
class mesero_tarjeta_extra_chica;
}

class mesero_tarjeta_extra_chica : public QWidget
{
    Q_OBJECT

public:
    explicit mesero_tarjeta_extra_chica(QWidget *parent = nullptr);
    ~mesero_tarjeta_extra_chica();

private:
    Ui::mesero_tarjeta_extra_chica *ui;
};

#endif // MESERO_TARJETA_EXTRA_CHICA_H
