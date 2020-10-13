#include "pawn.h"

Pawn::Pawn(bool team, QGraphicsItem *parent) : ChessPiece(team,parent){
    setImage();
}

void Pawn::setImage(){
    if(_team == 0)
        setPixmap(QPixmap(":/images/pawn_blk.png"));
    else
        setPixmap(QPixmap(":/images/pawn_white.png"));
}

void Pawn::move(){

}
