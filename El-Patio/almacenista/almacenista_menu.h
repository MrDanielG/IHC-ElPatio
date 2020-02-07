#ifndef ALMACENISTA_MENU_H
#define ALMACENISTA_MENU_H

#include <QWidget>
#include <QSqlDatabase>

class MainWindow;

namespace Ui {
class almacenista_menu;
}

class QSqlQueryModel;
class QSortFilterProxyModel;
class almacenista_menu : public QWidget
{
    Q_OBJECT

public:
    explicit almacenista_menu(QWidget *parent = nullptr);
    ~almacenista_menu();
    void llenarTabla(QString query);
    void setMainWindow(MainWindow *);

private slots:
    void on_btn_editar_insumo_clicked();

    void on_btn_cancelar_clicked();

    void on_ln_nombre_insumo_textChanged(const QString &arg1);

    void on_tablaInsumos_clicked(const QModelIndex &index);

    void on_btnTodo_clicked();

    void on_btnPlatillos_clicked();

    void on_btnBebidas_clicked();

    void on_btn_guardar_clicked();

private:
    Ui::almacenista_menu *ui;

    //referencia al padre
    MainWindow *mainwindow;

    QSqlQueryModel *almacenModel;
    QSortFilterProxyModel *almacenProxyModel;
    QString script;
    QSqlDatabase mDatabase;

};

#endif // ALMACENISTA_MENU_H
