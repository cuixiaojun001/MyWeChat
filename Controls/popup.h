#ifndef POPUPWIDGET_H
#define POPUPWIDGET_H

#include <QWidget>

class Popup : public QWidget
{
    Q_OBJECT
public:
    explicit Popup(QWidget *parent = nullptr);

private:
    bool event(QEvent *event);
signals:

};

#endif // POPUPWIDGET_H
