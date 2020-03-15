#ifndef ADMIN_TARJETA_CRUD_H
#define ADMIN_TARJETA_CRUD_H

#include <QWidget>

namespace Ui {
class admin_tarjeta_crud;
}

class admin_tarjeta_crud : public QWidget
{
    Q_OBJECT

public:
    explicit admin_tarjeta_crud(QWidget *parent = nullptr);
    ~admin_tarjeta_crud();

private:
    Ui::admin_tarjeta_crud *ui;
};

#endif // ADMIN_TARJETA_CRUD_H
