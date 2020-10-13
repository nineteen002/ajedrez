#include "knight.h"

Knight::Knight(bool team, QGraphicsItem *parent) : ChessPiece(team,parent){
    setImage();
}

void Knight::setImage(){
    if(_team == 0)
        setPixmap(QPixmap(":/images/knight_blk.png"));
    else
        setPixmap(QPixmap(":/images/knight_white.png"));
}

void Knight::move(){

}
