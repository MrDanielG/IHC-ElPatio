#ifndef ADMIN_EDITA_PLATILLO_H
#define ADMIN_EDITA_PLATILLO_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QListWidgetItem>
#include <models/platillo.h>

namespace Ui {
class admin_edita_platillo;
}

class admin_edita_platillo : public QDialog
{
    Q_OBJECT

public:
    explicit admin_edita_platillo(Platillo, QWidget *parent = nullptr);
    ~admin_edita_platillo();
    void conexionBD();
    void llenarInfo();
    void infoPlatilloDB();
    void llenarCategorias();
    void llenarIngredientes();

private slots:
    void on_btn_siguiente_clicked();

    void on_btn_atras_clicked();

    void on_btnCancelar_2_clicked();

    void on_btnCancelar2_clicked();

    void on_btn_editarFoto_clicked();

private:
    Ui::admin_edita_platillo *ui;
    QSqlDatabase mDatabase;
    Platillo platillo;
};

#endif // ADMIN_EDITA_PLATILLO_H
