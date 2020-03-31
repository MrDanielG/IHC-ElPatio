#include "calendarwidget.h"
#include <QPainter>


CalendarWidget::CalendarWidget(QWidget *parent) :
    QCalendarWidget(parent),
    mark_label(""),
    mark_color(Qt::red)
{
}

CalendarWidget::CalendarWidget(const QSet<QDate> &dates, QWidget *parent) :
    QCalendarWidget(parent),
    marked_dates(dates),
    mark_label(""),
    mark_color(Qt::red)
{

}

void CalendarWidget::markDate(const QDate &date)
{
    marked_dates.insert(date);
}

void CalendarWidget::unmarkDate(const QDate &date)
{
    marked_dates.remove(date);
}

void CalendarWidget::markDates(const QSet<QDate> &dates)
{
    marked_dates += dates;
}

void CalendarWidget::unmarkDates(const QSet<QDate> &dates)
{
    marked_dates -= dates;
}

bool CalendarWidget::isMarked(const QDate &date) const
{
    return marked_dates.contains(date);
}
void CalendarWidget::paintCell(QPainter *painter, const QRect &rect, const QDate &date) const
{
    if(marked_dates.contains(date))
    {
        painter->save();
        painter->fillRect(rect, mark_color);
        painter->setPen(mark_color.lighter());

        QString str;

        if(mark_label.isEmpty())
        {
            str = QString::number(date.day());
        }
        else
        {
            str =  mark_label + "\n" + QString::number(date.day());
        }
        painter->drawText(rect, Qt::AlignCenter, str);
        painter->restore();
    }
    else if(date > maximumDate()
            || date < minimumDate())
    {
        painter->save();
        painter->fillRect(rect, mark_color.lighter(110));

        painter->setPen(mark_color.lighter());
        QString str = "No disp.\n" + QString::number(date.day());
        painter->drawText(rect, Qt::AlignCenter, str);
        painter->restore();
    }
    else
        QCalendarWidget::paintCell(painter, rect, date);

}

void CalendarWidget::setMarkLabel(const QString &label)
{
    mark_label = label;
}

void CalendarWidget::setMarkColor(const QColor &color)
{
    mark_color = color;
}
