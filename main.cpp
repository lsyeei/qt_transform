#include "form.h"

#include <QApplication>
#include <QCoreApplication>

#include <QtGui/QTransform>
void showTrans(const QTransform &trans){
    qDebug() << trans.m11() << "\t" << trans.m12() << "\t" << trans.m13();
    qDebug() << trans.m21() << "\t" << trans.m22() << "\t" << trans.m23();
    qDebug() << trans.m31() << "\t" << trans.m32() << "\t" << trans.m33();
}
void noRotate()
{
    QTransform trans;
    trans.translate(100, 100);
    qDebug() << "just only translate:";
    showTrans(trans);
    trans.scale(0.5, 1);
    qDebug() << "after translate scale:";
    showTrans(trans);

    QTransform trans1;
    trans1.scale(0.5, 1);
    qDebug() << "just only scale:";
    showTrans(trans1);
    trans1.translate(100, 100);
    qDebug() << "after scale translate:";
    showTrans(trans1);
}
void noscale(){
    QTransform trans;
    trans.translate(100, 100);
    qDebug() << "just only translate:";
    showTrans(trans);
    trans.rotate(30);
    qDebug() << "after translate rotate:";
    showTrans(trans);

    QTransform trans1;
    trans1.rotate(30);
    qDebug() << "just only rotate:";
    showTrans(trans1);
    trans1.translate(100, 100);
    qDebug() << "after rotate translate:";
    showTrans(trans1);
}
void scaleRotate(){
    QTransform trans;
    trans.scale(0.5, 1);
    qDebug() << "just only scale:";
    showTrans(trans);
    trans.rotate(30);
    qDebug() << "after scale rotate:";
    showTrans(trans);
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Form form;
    form.show();
    return a.exec();
}
