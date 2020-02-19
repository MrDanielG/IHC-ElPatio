#ifndef MESERO_TRANSFERIR_PLATILLO_H
#define MESERO_TRANSFERIR_PLATILLO_H

#include <QWidget>
#include <QSqlDatabase>

class MainWindow;

namespace Ui {
class mesero_transferir_platillo;
}

class mesero_transferir_platillo : public QWidget
{
    Q_OBJECT

public:
    explicit mesero_transferir_platillo(QWidget *parent = nullptr);
    ~mesero_transferir_platillo();
    void setMainWindow(MainWindow *);

private:
    Ui::mesero_transferir_platillo *ui;
    QSqlDatabase mDatabase;

    MainWindow *mainWindow;
};

#endif // MESERO_TRANSFERIR_PLATILLO_H
