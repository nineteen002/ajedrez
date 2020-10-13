#include "boardblock.h"
#include "chesspiece.h"
#include <QDebug>

BoardBlock::BoardBlock(QGraphicsItem *parent): QGraphicsRectItem(parent) {
    //make square block
    setRect(0,0,100,100);
    brush.setStyle(Qt::SolidPattern);//bushstyle
    setZValue(-1);

    this->rowNum = 0;
    this->columnNum = 0;
    this->piece = nullptr;
}

void BoardBlock::setColor(QColor color){ //Sets color of block
    brush.setColor(color);
    setBrush(color);
}

QColor BoardBlock::getColor(){
    return this->color;
}

void BoardBlock::setLocation(int x, int y){
    this->rowNum = x;
    this->columnNum = y;
}


void BoardBlock::setChessPiece(ChessPiece* piece){
    //qDebug() << x()+50- piece->pixmap().width()/2 <<  y()+50-piece->pixmap().width()/2;
    piece->setPos(x()+50- piece->pixmap().width()/2  , y()+50-piece->pixmap().width()/2);
    this->piece = piece;
}

ChessPiece* BoardBlock::getChessPiece(){
    return this->piece;
}

BoardBlock::~BoardBlock(){
    delete this;
}
