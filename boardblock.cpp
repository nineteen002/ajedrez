#include "boardblock.h"
#include "chessboard.h"
#include "chesspiece.h"
#include <QDebug>

extern ChessBoard* board;
BoardBlock::BoardBlock(QGraphicsItem *parent): QGraphicsRectItem(parent) {
    //make square block
    setRect(0,0,100,100);
    brush.setStyle(Qt::SolidPattern);//bushstyle
    setZValue(-1);

    this->rowNum = 0;
    this->columnNum = 0;
    this->piece = nullptr;
}

//Color Related
void BoardBlock::setColor(QColor color){ //Sets color of block
    brush.setColor(color);
    setBrush(color);
}

void BoardBlock::setOriginalColor(QColor color){
    this->originalColor = color;
}

QColor BoardBlock::getOriginalColor(){
    return this->originalColor;
}

/*
QColor BoardBlock::getColor(){
    return this->color;
}*/

void BoardBlock::setLocation(int x, int y){
    this->rowNum = x;
    this->columnNum = y;
}

int BoardBlock::getRowLocation(){
    return this->rowNum;
}

int BoardBlock::getColumnLocation(){
    return this->columnNum;
}

//Chesspiece related
void BoardBlock::setChessPiece(ChessPiece* piece){
    //qDebug() << x()+50- piece->pixmap().width()/2 <<  y()+50-piece->pixmap().width()/2;
    piece->setPos(x()+50- piece->pixmap().width()/2  , y()+50-piece->pixmap().width()/2);
    piece->setCurrentBlock(this);
    this->piece = piece;
}

ChessPiece* BoardBlock::getChessPiece(){
    return this->piece;
}

bool BoardBlock::hasPiece(){
    return hasChessPiece;
}

BoardBlock::~BoardBlock(){
    delete this;
}
