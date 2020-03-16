#ifndef ADMINISTRADOR_CRUD_PLATILLOS_H
#define ADMINISTRADOR_CRUD_PLATILLOS_H

#include <QWidget>
#include <QSqlDatabase>
#include "models/platillo.h"
#include "models/extra.h"

namespace Ui {
class administrador_crud_platillos;
}

class administrador_crud_platillos : public QWidget
{
    Q_OBJECT

public:
    explicit administrador_crud_platillos(QWidget *parent = nullptr);
    ~administrador_crud_platillos();
    void conexionBD();
    void actualizarCatalogo();
    void limiparCatalogo();
    void getPlatilloTarjeta(Platillo platillo);
    void infoPlatillo();

private slots:
    void on_btnCrearPlatillo_clicked();

private:
    Ui::administrador_crud_platillos *ui;
    QSqlDatabase mDatabase;
    Platillo platilloTemporal;
};

#endif // ADMINISTRADOR_CRUD_PLATILLOS_H
