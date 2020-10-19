#include "chesspiece.h"

//Clase para las piezas
ChessPiece::ChessPiece(bool team, QGraphicsItem *parent) : QGraphicsPixmapItem(parent) {
    this->_team = team;
    this->isPlaced = true;
}

void ChessPiece::setCurrentBlock(BoardBlock *block){
    this->currentBlock = block;
}

BoardBlock* ChessPiece::getCurrentBlock(){
    return this->currentBlock;
}

void ChessPiece::setTeam(bool team){
    this->_team = team;
}

bool ChessPiece::getTeam(){
    return this->_team;
}

QString ChessPiece::getSide(){
    if(_team == 0){
        return "Black";
    }
    else{
        return "White";
    }
}

void ChessPiece::colorPossibleLocations(BoardBlock *box){

    box->setColor(QColor(148, 173, 214));
}

