#ifndef ADMINISTRADOR_CRUD_PLATILLOS_H
#define ADMINISTRADOR_CRUD_PLATILLOS_H

#include <QWidget>

namespace Ui {
class administrador_crud_platillos;
}

class administrador_crud_platillos : public QWidget
{
    Q_OBJECT

public:
    explicit administrador_crud_platillos(QWidget *parent = nullptr);
    ~administrador_crud_platillos();

private:
    Ui::administrador_crud_platillos *ui;
};

#endif // ADMINISTRADOR_CRUD_PLATILLOS_H
