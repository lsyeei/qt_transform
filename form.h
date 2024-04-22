#ifndef FORM_H
#define FORM_H

#include "demowidget.h"

#include <QWidget>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

private:
    Ui::Form *ui;
    QScopedPointer<QTransform> trans;

    // QWidget interface
    void showTranForm(const QString &title);
    void updateDemo();

    void transIsInvertible();

protected:

private slots:
    void on_setTranslate_clicked();
    void on_setScale_clicked();
    void on_setRotate_clicked();
    void on_reset_clicked();
    void on_clear_clicked();
    void on_parse_clicked();
};

#endif // FORM_H
