#ifndef AGREGAR_PROPINA_CUENTA_H
#define AGREGAR_PROPINA_CUENTA_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class agregar_propina_cuenta;
}

class agregar_propina_cuenta : public QDialog
{
    Q_OBJECT

public:
    explicit agregar_propina_cuenta(QStringList totales, QString idC, QWidget *parent = nullptr);
    ~agregar_propina_cuenta();

private slots:
    void on_otroMonto_clicked();

    void on_diezPorciento_clicked();

    void on_quincePorciento_clicked();

    void on_veintePorciento_clicked();

    void on_btnSecundaio_2_clicked();

    void on_btnPrimario_2_clicked();

    void on_montoPropina_textChanged(const QString &arg1);

    QString calculaPropina();


private:
    Ui::agregar_propina_cuenta *ui;
    double propina;
    QString idComanda;
    QSqlDatabase mDatabase;
    QStringList totalesDiv;
    int cuentas;
};

#endif // AGREGAR_PROPINA_CUENTA_H
