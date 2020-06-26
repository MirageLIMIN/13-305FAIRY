#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QMessageBox>

#include "onebox.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

signals:
    void changed(int score);

protected:
    void keyPressEvent(QKeyEvent *event);
    void moveUp();
    void moveRight();
    void moveLeft();
    void moveDown();

    bool canMoved();
    void endGame();
private:
    void initGame();
    void fillTable();
    void randomBox();
    bool isFull();
    void swapBox(OneBox *firstBox,OneBox *lastBox);

    void emptyBoxMoveLft();
    void emptyBoxMoveDown();
    void emptyBoxMoveRight();
    void emptyBoxMoveUp();

    Ui::Widget *ui;
    OneBox* oneboxTable[4][4];
    int score;
};

#endif // WIDGET_H
