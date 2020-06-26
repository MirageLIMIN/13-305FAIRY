#ifndef ONEBOX_H
#define ONEBOX_H

#include <QFrame>
#include <QPainter>
#include <QPaintEvent>


class OneBox : public QFrame
{
    Q_OBJECT
public:
    explicit OneBox(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void setNumber(int num);
    int Number() { return number;}
    bool isEmpty() { return !number;}
private:
    int number;
    QPixmap *pixmap;

};

#endif // ONEBOX_H
