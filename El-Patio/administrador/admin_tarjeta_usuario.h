#ifndef ADMIN_TARJETA_USUARIO_H
#define ADMIN_TARJETA_USUARIO_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
namespace Ui {
class admin_tarjeta_usuario;
}

class admin_tarjeta_usuario : public QWidget
{
    Q_OBJECT

public:
    explicit admin_tarjeta_usuario(QString, QString, QString, QString, QString, QWidget *parent = nullptr);
    ~admin_tarjeta_usuario();

private slots:
    void on_label_linkActivated(const QString &link);

private:
    Ui::admin_tarjeta_usuario *ui;
    QSqlDatabase mDatabase;
};

#endif // ADMIN_TARJETA_USUARIO_H
