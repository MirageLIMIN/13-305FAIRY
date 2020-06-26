#include <QDebug>
#include "onebox.h"

OneBox::OneBox(QWidget *parent) :
    QFrame(parent)
{
    number = 0;
    pixmap = new QPixmap(":/image/image/0.png");

}

void OneBox::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,80,80,*pixmap);
}

void OneBox::setNumber(int num)
{
    number = num;
    QString name = QString::number(num);
    QString filename  = ":/image/image/" + name + ".png";
    pixmap->load(filename);
    *pixmap = pixmap->scaled(QSize(80,80));
    update();
}
