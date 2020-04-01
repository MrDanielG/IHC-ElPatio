#ifndef RESERVACIONDELEGATE_H
#define RESERVACIONDELEGATE_H

#include <QStyledItemDelegate>

class reservacionDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    reservacionDelegate();
    void paint(QPainter* painter, const QStyleOptionViewItem&
                   option, const QModelIndex& index) const override;
    QSize sizeHint(const QStyleOptionViewItem& option,
            const QModelIndex& index) const override;
};

#endif // RESERVACIONDELEGATE_H
