
#include "textticker.h"
#include <QPainter>
#include <QTimer>
#include <QDebug>

TextTicker::TextTicker(QWidget *parent)
    : QLabel(parent)
{

    stepTime = 50;
    stepWidth = 1;
    curIndex = 0;

    scrollTimer = new QTimer();
    connect(scrollTimer, SIGNAL(timeout()), this, SLOT(updateIndex()));

}


void TextTicker::showScrollText(QString text)
{
    if(scrollTimer->isActive())
        scrollTimer->stop();

    showText = text;
    scrollTimer->start(stepTime);
}

void TextTicker::changeLabelState()
{
    if(scrollTimer->isActive()){
        scrollTimer->stop();
    }
    else {
        scrollTimer->start();
    }
}

void TextTicker::updateIndex()
{
    update();
    curIndex++;
    if (curIndex*stepWidth > width()){
        curIndex = 0;qDebug() << "aaa";
        }
}

void TextTicker::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.drawText(0-stepWidth*curIndex, 30, showText);
    painter.drawText(width() - stepWidth*curIndex, 30, showText.left(curIndex));
}
