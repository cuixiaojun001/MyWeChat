#ifndef RECEIVEWIDGET_H
#define RECEIVEWIDGET_H

#include <QWidget>

namespace Ui {
class ReceiveWidget;
}

class ReceiveWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ReceiveWidget(QWidget *parent = nullptr);
    ~ReceiveWidget();

    void setMessage(QString message);

signals:
    void sizeChanged(QRect rect);

private:
    Ui::ReceiveWidget *ui;

    void init();
    void sizeChange(QRect rect);

protected:
    void resizeEvent(QResizeEvent *event);
};

#endif // RECEIVEWIDGET_H
