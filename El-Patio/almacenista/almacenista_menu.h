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

    void on_btnEliminarInsumo_clicked();
    
    void on_btnTodo_clicked();

    void on_btnPlatillos_clicked();

    void on_btnBebidas_clicked();

    void on_spinBox_precio_valueChanged(const QString &arg1);

    void on_spinBox_existencias_valueChanged(const QString &arg1);

    void on_ln_presentacion_textChanged(const QString &arg1);
    void on_btn_agregar_insumo_clicked();

    void on_btn_guardar_clicked();

    void eliminaPerecedero();
    void eliminaInsumo();

private:
    Ui::almacenista_menu *ui;

    //referencia al padre
    MainWindow *mainwindow;

    QSqlQueryModel *almacenModel;
    QSortFilterProxyModel *almacenProxyModel;
    QString script;
    QSqlDatabase mDatabase;
    int existenciasOriginales;
    QString id;

    int headers = 1;
};

#endif // ALMACENISTA_MENU_H
