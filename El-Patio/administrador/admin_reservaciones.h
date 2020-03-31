#ifndef ADMIN_RESERVACIONES_H
#define ADMIN_RESERVACIONES_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class admin_reservaciones;
}

class admin_reservaciones : public QDialog
{
    Q_OBJECT

public:
    explicit admin_reservaciones(QWidget *parent = nullptr);
    void setHours(const QDate &date);
    ~admin_reservaciones();
    void llenaMesas();
    void setDate(const QDate &date);
private slots:
    void on_btnMasExtra_clicked();

    void on_btnMenosExtra_clicked();

    void on_btnCrearReserva_clicked();

private:
    Ui::admin_reservaciones *ui;
    QSqlDatabase mDatabase;
};

#endif // ADMIN_RESERVACIONES_H
