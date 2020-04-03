#ifndef RESERVAITEMWIDGET_H
#define RESERVAITEMWIDGET_H

#include <QWidget>

namespace Ui {
class reservaItemWidget;
}

class reservaItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit reservaItemWidget(QWidget *parent = nullptr);
    void setDatos( const QMap<QString, QString> &datos);
    ~reservaItemWidget();

private:
    Ui::reservaItemWidget *ui;
};

#endif // RESERVAITEMWIDGET_H
