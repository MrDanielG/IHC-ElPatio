#ifndef ADMIN_TARJETA_USUARIO_H
#define ADMIN_TARJETA_USUARIO_H

#include <QWidget>

namespace Ui {
class admin_tarjeta_usuario;
}

class admin_tarjeta_usuario : public QWidget
{
    Q_OBJECT

public:
    explicit admin_tarjeta_usuario(QWidget *parent = nullptr);
    ~admin_tarjeta_usuario();

private:
    Ui::admin_tarjeta_usuario *ui;
};

#endif // ADMIN_TARJETA_USUARIO_H
