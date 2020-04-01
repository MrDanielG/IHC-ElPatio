#include "reservaciondelegate.h"
#include "reservaitemwidget.h"

#include <QDate>
#include <QTime>

#include <QPainter>
#include <QMap>
#include <QEvent>

reservacionDelegate::reservacionDelegate(){}

void reservacionDelegate::paint(QPainter* painter, const QStyleOptionViewItem&
                         option, const QModelIndex& index) const
{
    painter->save();
    QMap<QString, QString> datos;

    datos["reservacion"]    = index.siblingAtColumn(0).data().toString();
    datos["mesa"]           = index.siblingAtColumn(1).data().toString();
    datos["fecha"]          = index.siblingAtColumn(2).data().toDate().toString("ddd, dd MMMM yyyy");
    datos["hora"]           = index.siblingAtColumn(3).data().toTime().toString("hh:mm AP");
    datos["cliente"]        = index.siblingAtColumn(4).data().toString();
    datos["personas"]       = index.siblingAtColumn(5).data().toString();

    reservaItemWidget date;
    date.setDatos(datos);

    //Region de Dibujo
    int x = option.rect.x();
    int y = option.rect.y();
    int w = option.rect.width();
    int z = option.rect.height();

    date.setFixedWidth(w);
    date.setFixedHeight(z);
    QPixmap pixmap(date.size());
    date.render(&pixmap);

    painter->drawPixmap(x,y, pixmap);

    if (option.state.testFlag(QStyle::State_Selected)) {
        QColor selectedColor = option.palette.highlight().color();
        painter->fillRect(option.rect, selectedColor);
    }

    painter->restore();
}

QSize reservacionDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    Q_UNUSED(index)
    Q_UNUSED(option)
    reservaItemWidget date;
    return date.size();
}
