#ifndef MESERO_CAMBIAR_CUENTA_MESA_H
#define MESERO_CAMBIAR_CUENTA_MESA_H

#include <QDialog>

namespace Ui {
class mesero_cambiar_cuenta_mesa;
}

class mesero_cambiar_cuenta_mesa : public QDialog
{
    Q_OBJECT

public:
    explicit mesero_cambiar_cuenta_mesa(QWidget *parent = nullptr);
    void setNumeroMesa(int);
    ~mesero_cambiar_cuenta_mesa();

private slots:
    void on_btnSecundaio_clicked();

    void on_btnPrimario_clicked();

    void transferir();

private:
    Ui::mesero_cambiar_cuenta_mesa *ui;
    int Mesa;
};

#endif // MESERO_CAMBIAR_CUENTA_MESA_H
