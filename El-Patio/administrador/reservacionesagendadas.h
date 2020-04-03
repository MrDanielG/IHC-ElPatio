#ifndef RESERVACIONESAGENDADAS_H
#define RESERVACIONESAGENDADAS_H

#include <QDialog>

namespace Ui {
class reservacionesAgendadas;
}

class QSqlQueryModel;
class QSortFilterProxyModel;

class reservacionesAgendadas : public QDialog
{
    Q_OBJECT

public:
    explicit reservacionesAgendadas(QString date,QWidget *parent = nullptr);
    ~reservacionesAgendadas();
    void recargar();
private:
    Ui::reservacionesAgendadas *ui;
    QSqlQueryModel *reservasModel;
    QSortFilterProxyModel *reservasProxyModel;
    QString currentDate;
};

#endif // RESERVACIONESAGENDADAS_H
