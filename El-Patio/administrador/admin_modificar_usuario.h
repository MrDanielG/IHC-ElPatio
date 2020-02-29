#ifndef ADMIN_MODIFICAR_USUARIO_H
#define ADMIN_MODIFICAR_USUARIO_H

#include <QDialog>

namespace Ui {
class admin_modificar_usuario;
}

class admin_modificar_usuario : public QDialog
{
    Q_OBJECT

public:
    explicit admin_modificar_usuario(QWidget *parent = nullptr);
    ~admin_modificar_usuario();

private:
    Ui::admin_modificar_usuario *ui;
};

#endif // ADMIN_MODIFICAR_USUARIO_H
