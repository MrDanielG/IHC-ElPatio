#ifndef ADMIN_EDITA_PLATILLO_H
#define ADMIN_EDITA_PLATILLO_H

#include <QDialog>

namespace Ui {
class admin_edita_platillo;
}

class admin_edita_platillo : public QDialog
{
    Q_OBJECT

public:
    explicit admin_edita_platillo(QWidget *parent = nullptr);
    ~admin_edita_platillo();

private:
    Ui::admin_edita_platillo *ui;
};

#endif // ADMIN_EDITA_PLATILLO_H
