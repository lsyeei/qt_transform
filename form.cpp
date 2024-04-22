#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Form)
    , trans(new QTransform())
{
    ui->setupUi(this);
    trans->reset();
}

Form::~Form()
{
    delete ui;
}

void Form::showTranForm(const QString &title)
{
    QString content("%1\n\n%2\t%3\t%4\n%5\t%6\t%7\n%8\t%9\t%10\n");
    content = content.arg(title)
                  .arg(trans->m11()).arg(trans->m12()).arg(trans->m13())
                    .arg(trans->m21()).arg(trans->m22()).arg(trans->m23())
                  .arg(trans->m31()).arg(trans->m32()).arg(trans->m33());
    ui->result->append(content);
    ui->result->append("-----------------------------------");
}

void Form::updateDemo()
{
    DemoWidget *demo = static_cast<DemoWidget *>(ui->demo);
    demo->setTrans(trans.data());
    demo->update();
    ui->result->append(QString("TranForm is invertible:%1").arg(trans->isInvertible()));
    ui->result->append(QString("TranForm compute dx:%1; fy:%2").arg(trans->dx()).arg(trans->dy()));
}

void Form::on_setTranslate_clicked()
{
    qreal dx = ui->dx->value(), dy = ui->dy->value();
    if (dx == 0 && dy == 0) {
        return;
    }
    // ui->setTranslate->setDisabled(true);
    trans->translate(dx, dy);
    showTranForm(QString("set Translate: dx=%1; dy=%2").arg(dx).arg(dy));
    updateDemo();
}


void Form::on_setScale_clicked()
{
    qreal sx = ui->scaleX->value(), sy = ui->scaleY->value();
    if (sx == 0 && sy == 0) {
        return;
    }
    // ui->setScale->setDisabled(true);
    trans->scale(sx, sy);
    showTranForm(QString("set Scale: sx=%1; sy=%2").arg(sx).arg(sy));
    updateDemo();
}


void Form::on_setRotate_clicked()
{
    qreal a =ui->rotateValue->value();
    if (a == 0){
        return;
    }
    // ui->setRotate->setDisabled(true);
    trans->rotate(a);
    showTranForm(QString("set Rotate: rotate=%1").arg(a));
    updateDemo();
}


void Form::on_reset_clicked()
{
    trans->reset();
    updateDemo();
    ui->setTranslate->setDisabled(false);
    ui->setRotate->setDisabled(false);
    ui->setScale->setDisabled(false);
}


void Form::on_clear_clicked()
{
    ui->result->clear();
}


void Form::on_parse_clicked()
{
    qreal angle = 0.0;
    qreal sina = trans->m21();
    qreal cosa = trans->m22();
    if (cosa == 0){
        if (sina > 0) {
            angle = 270;
        }else{
            angle = 90;
        }
    }else{
        qreal tan1 = trans->m21() / trans->m11();
        qreal tan2 = trans->m12() / trans->m22();
        if (tan1 + tan1 != 0) {
            // x于y的缩放比不同，且先缩放再旋转
            ui->result->append("先旋转再缩放");
            tan1 = trans->m21() / trans->m22();
            tan2 = trans->m12() / trans->m11();
        }else{
            ui->result->append("先缩放再旋转");
        }
        angle = atan(tan2) * 180 / 3.1415;

        if (cosa < 0) {
            if (sina != 0) {
                angle += 180;
            }else{
                angle = 180;
            }
        } else if (cosa > 0) {
            if (sina == 0){
                angle = 0;
            }
        }
    }
    if (abs(angle) < 0.001){
        angle = 0;
    }
    ui->result->append(QString("计算旋转角度 = %1").arg(angle));

    // 计算缩放比例
    qreal scaleX = trans->m12();
    qreal scaleY = - trans->m21();
    if (trans->m11() != 0){
        scaleX = abs(trans->m11() / cos(qDegreesToRadians(angle)));
        scaleY = abs(trans->m22() / cos(qDegreesToRadians(angle)));
    }

    ui->result->append(QString("计算缩放比例 sx= %1;  sy = %2;").arg(scaleX).arg(scaleY));
}

