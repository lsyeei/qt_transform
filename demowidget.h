#ifndef DEMOWIDGET_H
#define DEMOWIDGET_H

#include <QObject>
#include <QWidget>

class DemoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DemoWidget(QWidget *parent = nullptr);
    ~DemoWidget();

    void setTrans(QTransform *newTrans);

signals:

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QTransform *trans;
    void drawDemo(QPainter *painter, QPen pen, QRect viewRect);
};

#endif // DEMOWIDGET_H
