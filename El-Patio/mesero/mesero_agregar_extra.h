#ifndef MESERO_AGREGAR_EXTRA_H
#define MESERO_AGREGAR_EXTRA_H

#include <QWidget>
#include <QSqlDatabase>

namespace Ui {
class mesero_agregar_extra;
}

class mesero_agregar_extra : public QWidget
{
    Q_OBJECT

public:
    explicit mesero_agregar_extra(QWidget *parent = nullptr);
    ~mesero_agregar_extra();

private slots:
    void on_btnMasExtra_clicked();

    void on_btnMasExtra_2_clicked();

    void on_btnMandarCocina_2_clicked();

private:
    Ui::mesero_agregar_extra *ui;
    QSqlDatabase mDatabase;
};

#endif // MESERO_AGREGAR_EXTRA_H
