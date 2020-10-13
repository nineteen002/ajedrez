#include "queen.h"

Queen::Queen(bool team, QGraphicsItem *parent) : ChessPiece(team,parent){
    setImage();
}

void Queen::setImage(){
    if(_team == 0)
        setPixmap(QPixmap(":/images/queen_blk.png"));
    else
        setPixmap(QPixmap(":/images/queen_white.png"));
}

void Queen::move(){

}
