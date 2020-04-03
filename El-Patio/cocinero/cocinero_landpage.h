#ifndef COCINERO_LANDPAGE_H
#define COCINERO_LANDPAGE_H

#include <QWidget>

namespace Ui {
class cocinero_landpage;
}

class cocinero_landpage : public QWidget
{
    Q_OBJECT

public:
    explicit cocinero_landpage(QWidget *parent = nullptr);
    ~cocinero_landpage();

private:
    Ui::cocinero_landpage *ui;
};

#endif // COCINERO_LANDPAGE_H
