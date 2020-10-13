#include "rook.h"

Rook::Rook(bool team, QGraphicsItem *parent) : ChessPiece(team,parent){
    setImage();
}

void Rook::setImage(){
    if(_team == 0)
        setPixmap(QPixmap(":/images/rook_blk.png"));
    else
        setPixmap(QPixmap(":/images/rook_white.png"));
}

void Rook::move(){

}
