#ifndef ADMIN_REPORTES_H
#define ADMIN_REPORTES_H

#include <QWidget>
#include <QSqlDatabase>

class QPushButton;

namespace Ui {
class admin_reportes;
}

class admin_reportes : public QWidget
{
    Q_OBJECT

public:
    explicit admin_reportes(QWidget *parent = nullptr);
    void conexionBD();
    void actualizarDatos();
    void clicked_button(QPushButton *boton);
    void limpiarGridMeseros();
    ~admin_reportes();

private slots:
    void on_btn_ventas_clicked();

    void on_btn_transacciones_clicked();

    void on_btn_comandas_clicked();

    void on_btn_buscarReporte_clicked();

private:
    Ui::admin_reportes *ui;
    QSqlDatabase mDatabase;
};

#endif // ADMIN_REPORTES_H
