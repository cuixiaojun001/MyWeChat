#include "receivewidget.h"
#include "ui_receivewidget.h"

ReceiveWidget::ReceiveWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReceiveWidget)
{
    ui->setupUi(this);
    init();
}

ReceiveWidget::~ReceiveWidget()
{
    delete ui;
}

void ReceiveWidget::setMessage(QString message)
{
    ui->msgLbl->setText(message);
}

void ReceiveWidget::init()
{
    ui->checkBtn->setVisible(false);
    connect(ui->msgLbl, &Label::sizeChanged, this, &ReceiveWidget::sizeChange);
}

void ReceiveWidget::sizeChange(QRect rect)
{
    auto g_rect = geometry();
    g_rect.setHeight(rect.height() + 20);
    setGeometry(g_rect);
    emit sizeChanged(rect);
}

void ReceiveWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    ui->msgLbl->setMaximumWidth(width() - 140);
    ui->msgLbl->setText(ui->msgLbl->text());
}
