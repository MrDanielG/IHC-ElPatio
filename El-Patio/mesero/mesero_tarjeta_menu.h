#ifndef MESERO_TARJETA_MENU_H
#define MESERO_TARJETA_MENU_H

#include <QWidget>

namespace Ui {
class mesero_tarjeta_menu;
}

class mesero_tarjeta_menu : public QWidget
{
    Q_OBJECT

public:
    explicit mesero_tarjeta_menu(QWidget *parent = nullptr);
    ~mesero_tarjeta_menu();

private:
    Ui::mesero_tarjeta_menu *ui;
};

#endif // MESERO_TARJETA_MENU_H
