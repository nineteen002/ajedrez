#include "bishop.h"

Bishop::Bishop(bool team, QGraphicsItem *parent) : ChessPiece(team,parent){
    setImage();
}

void Bishop::setImage(){
    if(_team == 0)
        setPixmap(QPixmap(":/images/bishop_blk.png"));
    else
        setPixmap(QPixmap(":/images/bishop_white.png"));
}

void Bishop::move(){

}
