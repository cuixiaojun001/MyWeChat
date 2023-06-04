#include "popup.h"
#include <QEvent>

Popup::Popup(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::Popup);
}

bool Popup::event(QEvent *event)
{
    Q_UNUSED(event);
    if (QEvent::WindowDeactivate == event->type())
    {
        close();
    }
    return QWidget::event(event);
}
