#ifndef DIVIDIRCUENTA_H
#define DIVIDIRCUENTA_H

#include <QWidget>

namespace Ui {
class DividirCuenta;
}

class DividirCuenta : public QWidget
{
    Q_OBJECT

public:
    explicit DividirCuenta(QWidget *parent = nullptr);
    ~DividirCuenta();
    void setIdComanda(QString idC);
    void llenaCuentaPrincipal();
    void setIdMesero(int idM);
    void Dividir();

private:
    Ui::DividirCuenta *ui;
    QString idComanda;
    int numCuentas = 1;
};

#endif // DIVIDIRCUENTA_H
