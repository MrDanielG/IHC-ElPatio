#ifndef COCINERO_LANDPAGE_H
#define COCINERO_LANDPAGE_H

#include <QWidget>

class MainWindow;
class cocinero_pedidos;
namespace Ui {
class cocinero_landpage;
}

class cocinero_landpage : public QWidget
{
    Q_OBJECT

public:
    explicit cocinero_landpage(QWidget *parent = nullptr);
    void setCocineroId(QString);
    ~cocinero_landpage();

private:
    Ui::cocinero_landpage *ui;
    MainWindow *padre;
    cocinero_pedidos *pedidosCocina;
    QString idCocinero;
};

#endif // COCINERO_LANDPAGE_H
