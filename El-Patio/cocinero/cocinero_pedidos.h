#ifndef COCINERO_PEDIDOS_H
#define COCINERO_PEDIDOS_H

#include <QWidget>

namespace Ui {
class cocinero_pedidos;
}

class cocinero_pedidos : public QWidget
{
    Q_OBJECT

public:
    explicit cocinero_pedidos(QWidget *parent = nullptr);
    ~cocinero_pedidos();

private:
    Ui::cocinero_pedidos *ui;
};

#endif // COCINERO_PEDIDOS_H
