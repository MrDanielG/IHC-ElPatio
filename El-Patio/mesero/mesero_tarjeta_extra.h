#ifndef MESERO_TARJETA_EXTRA_H
#define MESERO_TARJETA_EXTRA_H

#include <QWidget>

namespace Ui {
class mesero_tarjeta_extra;
}

class mesero_tarjeta_extra : public QWidget
{
    Q_OBJECT

public:
    explicit mesero_tarjeta_extra(QWidget *parent = nullptr);
    ~mesero_tarjeta_extra();

private:
    Ui::mesero_tarjeta_extra *ui;
};

#endif // MESERO_TARJETA_EXTRA_H
