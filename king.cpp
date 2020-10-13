#include "king.h"

King::King(bool team, QGraphicsItem *parent) : ChessPiece(team,parent){
    setImage();
}

void King::setImage(){
    if(_team == 0)
        setPixmap(QPixmap(":/images/king_blk.png"));
    else
        setPixmap(QPixmap(":/images/king_white.png"));
}

void King::move(){

}
