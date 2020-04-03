#ifndef COCINERO_PEDIDOS_H
#define COCINERO_PEDIDOS_H

#include <QWidget>
#include <QSqlDatabase>

namespace Ui {
class cocinero_pedidos;
}

class cocinero_pedidos : public QWidget
{
    Q_OBJECT

public:
    explicit cocinero_pedidos(QWidget *parent = nullptr);
    void conexionBD();
    void actualizarCatalogo();
    void limiparCatalogo();
    ~cocinero_pedidos();

private:
    Ui::cocinero_pedidos *ui;
    QSqlDatabase mDatabase;
};

#endif // COCINERO_PEDIDOS_H
