#ifndef ADMIN_EDITA_PLATILLO_H
#define ADMIN_EDITA_PLATILLO_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QListWidgetItem>
#include <models/platillo.h>
#include <models/ingrediente.h>
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
    void updatePlatillo();
    void updateIngredientesPlatillo();
    Platillo platillo;

private slots:
    void on_btn_siguiente_clicked();

    void on_btn_atras_clicked();

    void on_btnCancelar_2_clicked();

    void on_btn_editarFoto_clicked();

    void on_list_ingreExistente_itemDoubleClicked(QListWidgetItem *item);

    void on_list_ingrePlatillo_itemDoubleClicked(QListWidgetItem *item);

    void on_btnActualizar_clicked();

    void on_le_nombrePlatillo_textChanged(const QString &arg1);

    void on_spinBoxPrecio_valueChanged(const QString &arg1);

    void on_cb_categoria_activated(const QString &arg1);

    void on_btn_nuevaCategoria_clicked();

    void on_btn_canNueCategoria_clicked();

    void on_le_categoria_textChanged(const QString &arg1);

private:
    Ui::admin_edita_platillo *ui;
    QSqlDatabase mDatabase;

    QList<Ingrediente> listaIngPlatillo;
    QList<Ingrediente> listaIngGeneral;
};

#endif // ADMIN_EDITA_PLATILLO_H
