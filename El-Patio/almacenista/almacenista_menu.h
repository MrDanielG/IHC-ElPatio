#ifndef ALMACENISTA_MENU_H
#define ALMACENISTA_MENU_H

#include <QWidget>

class MainWindow;

namespace Ui {
class almacenista_menu;
}

class almacenista_menu : public QWidget
{
    Q_OBJECT

public:
    explicit almacenista_menu(QWidget *parent = nullptr);
    ~almacenista_menu();

    void setMainWindow(MainWindow *);

private slots:
    void on_btn_editar_insumo_clicked();

    void on_btn_cancelar_clicked();

    void on_btn_agregar_insumo_clicked();

private:
    Ui::almacenista_menu *ui;

    //referencia al padre
    MainWindow *mainwindow;
};

#endif // ALMACENISTA_MENU_H
