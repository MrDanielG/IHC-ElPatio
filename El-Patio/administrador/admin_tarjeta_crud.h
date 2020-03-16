#ifndef ADMIN_TARJETA_CRUD_H
#define ADMIN_TARJETA_CRUD_H

#include <QWidget>
#include <models/platillo.h>

class administrador_crud_platillos;
namespace Ui {
class admin_tarjeta_crud;
}

class admin_tarjeta_crud : public QWidget
{
    Q_OBJECT

public:
    explicit admin_tarjeta_crud(Platillo, administrador_crud_platillos *parent = nullptr);
    ~admin_tarjeta_crud();
    void llenarTarjeta();
    void actualizarTarjeta();

private slots:
    void on_btnMasPlatillo_clicked();

private:
    Ui::admin_tarjeta_crud *ui;
    Platillo platillo;
    administrador_crud_platillos *padre;
};

#endif // ADMIN_TARJETA_CRUD_H
