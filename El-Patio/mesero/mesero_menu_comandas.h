#ifndef MESERO_MENU_COMANDAS_H
#define MESERO_MENU_COMANDAS_H

#include <QWidget>
#include <QSqlDatabase>

namespace Ui {
class mesero_menu_comandas;
}

class mesero_menu_comandas : public QWidget
{
    Q_OBJECT

public:
    explicit mesero_menu_comandas(QWidget *parent = nullptr);
    ~mesero_menu_comandas();
    void limiparCatalogo();

private:
    Ui::mesero_menu_comandas *ui;
    QSqlDatabase mDatabase;
};

#endif // MESERO_MENU_COMANDAS_H
