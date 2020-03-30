#ifndef ADMIN_RESERVACIONES_H
#define ADMIN_RESERVACIONES_H

#include <QDialog>

namespace Ui {
class admin_reservaciones;
}

class admin_reservaciones : public QDialog
{
    Q_OBJECT

public:
    explicit admin_reservaciones(QWidget *parent = nullptr);
    ~admin_reservaciones();

private:
    Ui::admin_reservaciones *ui;
};

#endif // ADMIN_RESERVACIONES_H
