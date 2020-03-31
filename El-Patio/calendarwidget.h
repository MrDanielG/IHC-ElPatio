#ifndef CALENDARWIDGET_H
#define CALENDARWIDGET_H

#include <QCalendarWidget>
#include <QSet>
#include <QDate>


class CalendarWidget : public QCalendarWidget
{
public:
    CalendarWidget(QWidget *parent = nullptr);
    CalendarWidget(const QSet<QDate> &dates, QWidget *parent = nullptr);
    // Interfaz añadida a QCalendarWidget
    // para soportar varias fechas marcadas.
    void markDate(const QDate &date);
    void markDates(const QSet<QDate> &dates);
    void unmarkDates(const QSet<QDate> &dates);
    void unmarkDate(const QDate &date);
    void setMarkLabel(const QString &label);
    void setMarkColor(const QColor& color);
    bool isMarked(const QDate &date) const;

protected:
    // reimplementación del método QCalendarWidget::painterCell
    // para marcar vairas fechas
    void paintCell(QPainter *painter, const QRect &rect, const QDate &date) const override;

protected:
    // conjuto de fechas marcadas
    QSet<QDate> marked_dates;
    // la etiqueta para las fechas marcadas
    QString mark_label;
    // el color de la etiqueta para las fechas marcadas
    QColor mark_color;
};

#endif // CALENDARWIDGET_H
