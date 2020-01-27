#ifndef CATALOGOMESAS_H
#define CATALOGOMESAS_H

#include <QWidget>

namespace Ui {
class CatalogoMesas;
}

class CatalogoMesas : public QWidget
{
    Q_OBJECT

public:
    explicit CatalogoMesas(QWidget *parent = nullptr);
    ~CatalogoMesas();
    void AgregarMesas(int n);

public slots:
    void seleccionarMesa();

private slots:

    void on_btnTodos_clicked();

    void on_btnLibre_clicked();

    void on_btnOcupado_clicked();

    void on_btn1_clicked();

    void on_btn2_clicked();

    void on_btn3_clicked();

    void on_btn4_clicked();

    void on_btn5_clicked();

    void on_btn6_clicked();

    void on_btn7_clicked();

    void on_btn8_clicked();

    void on_btn9_clicked();

    void on_btn0_clicked();

    void on_btnDel_clicked();

    void on_btnAbrirMesa_clicked();

private:
    Ui::CatalogoMesas *ui;
};

#endif // CATALOGOMESAS_H
