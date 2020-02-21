#ifndef CONFIRMARTRANSFERENCIA_H
#define CONFIRMARTRANSFERENCIA_H

#include <QDialog>

namespace Ui {
class ConfirmarTransferencia;
}

class ConfirmarTransferencia : public QDialog
{
    Q_OBJECT

public:
    explicit ConfirmarTransferencia(QWidget *parent = nullptr);
    ~ConfirmarTransferencia();
    QString get_claveAdmin();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ConfirmarTransferencia *ui;

    QString claveAdmin;
};

#endif // CONFIRMARTRANSFERENCIA_H
