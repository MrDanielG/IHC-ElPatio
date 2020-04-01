#ifndef ADMIN_LANDPAGE_H
#define ADMIN_LANDPAGE_H

#include <QWidget>

namespace Ui {
class admin_landpage;
}

class admin_landpage : public QWidget
{
    Q_OBJECT

public:
    explicit admin_landpage(QWidget *parent = nullptr);
    ~admin_landpage();

private:
    Ui::admin_landpage *ui;
};

#endif // ADMIN_LANDPAGE_H
