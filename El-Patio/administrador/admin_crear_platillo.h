#ifndef ADMIN_CREAR_PLATILLO_H
#define ADMIN_CREAR_PLATILLO_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QListWidgetItem>

namespace Ui {
class admin_crear_platillo;
}

class admin_crear_platillo : public QDialog
{
    Q_OBJECT

public:
    explicit admin_crear_platillo(QWidget *parent = nullptr);
    void conexionBD();
    void actualizarDatos();
    ~admin_crear_platillo();

private slots:
    void on_list_ingreExistente_itemDoubleClicked(QListWidgetItem *item);

    void on_list_ingrePlatillo_itemDoubleClicked(QListWidgetItem *item);

    void on_btnCrearPlatillo_clicked();

    void on_btn_siguiente_clicked();

    void on_btn_atras_clicked();

    void on_btn_nuevaCategoria_clicked();

    void on_btn_canNueCategoria_clicked();

private:
    Ui::admin_crear_platillo *ui;
    QSqlDatabase mDatabase;
};

#endif // ADMIN_CREAR_PLATILLO_H
