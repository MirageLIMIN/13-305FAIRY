#include <QDebug>

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    score = 0;
    connect(this,SIGNAL(changed(int)),ui->lcdNumber,
            SLOT(display(int)));

    fillTable();
    initGame();
}


Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
        case Qt::Key_Up:{
            if(canMoved())
                 moveUp();
            else endGame();
            break;
        }
        case Qt::Key_Down:{
            if(canMoved())
                moveDown();
            else endGame();
            break;
        }
        case Qt::Key_Left:{
            if(canMoved())
                moveLeft();
            else endGame();
            break;
        }
        case Qt::Key_Right:{
            if(canMoved())
                moveRight();
            else endGame();
            break;
        }
        default: QWidget::keyPressEvent(event);
    }
}


//向上移动，首先把其中的空Box置下，在进行计算
void Widget::moveUp()
{
    emptyBoxMoveDown();
    for(int j = 0;j < 4;j++){
        for(int i = 3;i > 0;i--){
            if(!oneboxTable[i][j]->isEmpty()){
                if(oneboxTable[i][j]->Number()
                        == oneboxTable[i-1][j]->Number()){
                    oneboxTable[i][j]->setNumber(0);
                    oneboxTable[i-1][j]->setNumber(oneboxTable[i-1][j]->Number()*2);
                    score += oneboxTable[i-1][j]->Number();
                    emit changed(score);
                    if(oneboxTable[i-1][j]->Number() == 2048){
                        endGame();
                    }
                }
            }
        }
    }
    emptyBoxMoveDown();
    randomBox();
}



//向右移动，首先把其中的空Box置左，在进行计算
void Widget::moveRight()
{
    emptyBoxMoveLft();
    for(int i = 0;i < 4; i++){
        for(int j = 0;j < 3;j++){
            if(!oneboxTable[i][j]->isEmpty()){
                if(oneboxTable[i][j]->Number()
                        == oneboxTable[i][j+1]->Number()){
                    oneboxTable[i][j]->setNumber(0);
                    oneboxTable[i][j+1]->setNumber(oneboxTable[i][j+1]->Number()*2);
                    score += oneboxTable[i][j+1]->Number();
                    emit changed(score);
                    if(oneboxTable[i][j+1]->Number() == 2048){
                        endGame();
                    }
                }
            }
        }
    }
    emptyBoxMoveLft();
    randomBox();
}

void Widget::moveLeft()
{
    emptyBoxMoveRight();
    for(int i = 0;i < 4;i++){
        for(int j = 3;j > 0;j--){
            if(!oneboxTable[i][j]->isEmpty()){
                if(oneboxTable[i][j]->Number()
                        == oneboxTable[i][j-1]->Number()){
                    oneboxTable[i][j]->setNumber(0);
                    oneboxTable[i][j-1]->setNumber(oneboxTable[i][j-1]->Number()*2);
                    score += oneboxTable[i][j-1]->Number();
                    emit changed(score);
                    if(oneboxTable[i][j-1]->Number() == 2048){
                        endGame();
                    }
                }
            }
        }
    }
    emptyBoxMoveRight();
    randomBox();
}

void Widget::moveDown()
{
    emptyBoxMoveUp();
    for(int j = 0;j < 4;j++){
        for(int i = 0;i < 3;i++){
            if(!oneboxTable[i][j]->isEmpty()){
                if(oneboxTable[i][j]->Number()
                        == oneboxTable[i+1][j]->Number()){
                    oneboxTable[i][j]->setNumber(0);
                    oneboxTable[i+1][j]->setNumber(oneboxTable[i+1][j]->Number()*2);
                    score += oneboxTable[i+1][j]->Number();
                    emit changed(score);
                    if(oneboxTable[i+1][j]->Number() == 2048){
                        endGame();
                    }
                }
            }
        }
    }
    emptyBoxMoveUp();
    randomBox();
}

bool Widget::canMoved()
{
    if(isFull()){
        for(int i = 0;i < 4; i++){
            for(int j = 0;j < 3;j++){
                if(oneboxTable[i][j]->Number() ==
                        oneboxTable[i][j+1]->Number())
                    return true;
            }
        }
        for(int j = 0;j < 4; j++){
            for(int i = 0;i < 3;i++){
                if(oneboxTable[i][j]->Number() ==
                        oneboxTable[i+1][j]->Number())
                   return true;
            }
        }
        return false;
    } else {
        return true;
    }
}

//游戏结束处理函数
void Widget::endGame()
{
//    this->setBackgroundRole();
    qDebug() << "End Game";

    QMessageBox::about(this,tr("End Game"),tr("Game Over!!!<br/>You Score is %1").arg(score));
    qApp->exit();
}

//初始化游戏,随机生成两个OneBox
void Widget::initGame()
{
    for(int i = 0;i < 2;i++){
        int x = qrand()%4;
        int y = qrand()%4;
        if(oneboxTable[x][y]->isEmpty()){
            int n = (qrand()%2+1)*2;
            oneboxTable[x][y]->setNumber(n);
        }
    }
}

//将16个OneBox填入oneboxTable,方便访问
void Widget::fillTable()
{
    oneboxTable[0][0] = ui->frame_0_0;
    oneboxTable[0][1] = ui->frame_0_1;
    oneboxTable[0][2] = ui->frame_0_2;
    oneboxTable[0][3] = ui->frame_0_3;

    oneboxTable[1][0] = ui->frame_1_0;
    oneboxTable[1][1] = ui->frame_1_1;
    oneboxTable[1][2] = ui->frame_1_2;
    oneboxTable[1][3] = ui->frame_1_3;

    oneboxTable[2][0] = ui->frame_2_0;
    oneboxTable[2][1] = ui->frame_2_1;
    oneboxTable[2][2] = ui->frame_2_2;
    oneboxTable[2][3] = ui->frame_2_3;

    oneboxTable[3][0] = ui->frame_3_0;
    oneboxTable[3][1] = ui->frame_3_1;
    oneboxTable[3][2] = ui->frame_3_2;
    oneboxTable[3][3] = ui->frame_3_3;

}

// 随机生成一个OneBox
void Widget::randomBox()
{
//    while(true){
//        int x = qrand()%4;
//        int y = qrand()%4;
//        qDebug() << x <<y;
//        if(oneboxTable[x][y]->isEmpty()){
//            int n = (qrand()%2+1)*2;
//            oneboxTable[x][y]->setNumber(n);
//            break;
//        }
//    }
/*修改程序*/
    QList<OneBox *> list;
    for(int i = 0;i < 4;i++){
        for(int j = 0;j < 4;j++){
            if(oneboxTable[i][j]->isEmpty())
                list.append(oneboxTable[i][j]);
        }
    }
    int n = (qrand()%2+1)*2;
    int emptyBoxCount = list.count();
    if(emptyBoxCount)
        list.at(qrand()%emptyBoxCount)->setNumber(n);

}


bool Widget::isFull()
{
    for(int i = 0;i < 4;i++){
        for(int j = 0;j < 4;j++){
            if(oneboxTable[i][j]->isEmpty())
                return false;
        }
    }
    return true;
}

void Widget::swapBox(OneBox *firstBox, OneBox *lastBox)
{
     int Num = firstBox->Number();
     firstBox->setNumber(lastBox->Number());
     lastBox->setNumber(Num);
}


void Widget::emptyBoxMoveLft()
{
    for(int i = 0;i < 4;i++){
        for(int j = 3;j > 0;j--){
            if(oneboxTable[i][j]->isEmpty()){
                for(int m = j;m > 0;m--){
                    swapBox(oneboxTable[i][m],oneboxTable[i][m-1]);
                }
            }
        }
    }
}

void Widget::emptyBoxMoveDown()
{
    for(int j = 0;j < 4;j++){
        for(int i = 0;i < 3;i++){
            if(oneboxTable[i][j]->isEmpty()){
                for(int m = i;m < 3;m++){
                    swapBox(oneboxTable[m][j],oneboxTable[m+1][j]);
                }
            }
        }
    }
}

void Widget::emptyBoxMoveRight()
{
    for(int i = 0;i < 4;i++){
        for(int j = 0;j < 3;j++){
            if(oneboxTable[i][j]->isEmpty()){
                for(int m = j;m < 3;m++){
                    swapBox(oneboxTable[i][m],oneboxTable[i][m+1]);
                }
            }
        }
    }
}

void Widget::emptyBoxMoveUp()
{
    for(int j = 0;j < 4;j++){
        for(int i = 3;i > 0;i--){
            if(oneboxTable[i][j]->isEmpty()){
                for(int m = i;m > 0;m--){
                    swapBox(oneboxTable[m][j],oneboxTable[m-1][j]);
                }
            }
        }
    }
}
