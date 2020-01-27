#ifndef MESERO_MENU_COMANDAS_H
#define MESERO_MENU_COMANDAS_H

#include <QWidget>

namespace Ui {
class mesero_menu_comandas;
}

class mesero_menu_comandas : public QWidget
{
    Q_OBJECT

public:
    explicit mesero_menu_comandas(QWidget *parent = nullptr);
    ~mesero_menu_comandas();

private:
    Ui::mesero_menu_comandas *ui;
};

#endif // MESERO_MENU_COMANDAS_H
