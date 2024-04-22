#include "demowidget.h"

#include <QPaintEvent>
#include <QPainter>
#include <QPen>

DemoWidget::DemoWidget(QWidget *parent)
    : QWidget{parent}
{
    trans = nullptr;
}

DemoWidget::~DemoWidget()
{
    trans = nullptr;
}


void DemoWidget::drawDemo(QPainter *painter, QPen pen, QRect viewRect)
{
    painter->drawLine(QPoint(0,0), QPoint(viewRect.width()/2 - 20,0));
    painter->drawText(QPoint(viewRect.width()/2 - 25,-5), "x");
    painter->drawLine(QPoint(0,0), QPoint(0,viewRect.height()/2 - 20));
    painter->drawText(QPoint(-10, viewRect.height()/2 - 20), "y");

    pen.setColor(Qt::red);
    painter->setPen(pen);
    painter->drawRect(QRect(0,0,50,50));
}

void DemoWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter *painter = new QPainter(this);
    QPen pen(Qt::SolidLine);
    pen.setColor(Qt::black);
    pen.setWidth(1);
    painter->setPen(pen);

    QRect viewRect= rect();
    painter->setViewport(viewRect);
    painter->setWindow({-viewRect.width() / 2, -viewRect.height() / 2,
                        viewRect.width(), viewRect.height()});
    drawDemo(painter, pen, viewRect);

    if (trans != nullptr && !trans->isIdentity()) {
        // painter->setTransform(*trans);
        painter->setWorldTransform(*trans);

        pen.setColor(Qt::blue);
        pen.setStyle(Qt::DashLine);
        painter->setPen(pen);

        drawDemo(painter, pen, viewRect);
    }

    painter->end();
    delete painter;
}

void DemoWidget::setTrans(QTransform *newTrans)
{
    trans = newTrans;
}
