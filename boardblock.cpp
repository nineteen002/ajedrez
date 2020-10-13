#include "boardblock.h"

#include <QDebug>

BoardBlock::BoardBlock(QGraphicsItem *parent): QGraphicsRectItem(parent) {
    qDebug() << "Started cheess block";
    //make square block
    setRect(0,0,100,100);
    brush.setStyle(Qt::SolidPattern);
    setZValue(-1);

    this->rowNum = 0;
    this->columnNum = 0;
    this->piece = nullptr;
}

void BoardBlock::setColor(QColor color){
    brush.setColor(color);
    setBrush(color);
}

QColor BoardBlock::getColor(){
    return this->color;
}

BoardBlock::~BoardBlock(){
    delete this;
}
