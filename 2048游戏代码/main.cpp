#include "widget.h"
#include <QApplication>
#include <QTime>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qsrand(QTime::currentTime().msec());

    Widget w;
    w.show();

    return a.exec();
}
