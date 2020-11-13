#include "chesspiece.h"
#include "chessboard.h"

//Clase para las piezas
extern ChessBoard* board;
ChessPiece::ChessPiece(bool team, QGraphicsItem *parent) : QGraphicsPixmapItem(parent) {
    this->_team = team;
    this->isPlaced = true;
    isFirstMove = true;
    castling = false;
}

void ChessPiece::setCurrentBlock(BoardBlock *block){
    this->currentBlock = block;
    if(block == nullptr){
        this->isPlaced = false;
    }
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
    if(this->_team == 0){
        return "Black";
    }
    else{
        return "White";
    }
}

QList <BoardBlock*> ChessPiece::getPossibleLocations(){// returns locations
    return this->location;
}

void ChessPiece::colorPossibleLocations(BoardBlock *box){ //changes color of possible move locations

    box->setColor(QColor(148, 173, 214));
}

void ChessPiece::unselect(){  //returns original color of possible locations
    int locs = location.count();
    for(int i = 0; i < locs; i++){
        QColor org_color = location[i]->getOriginalColor();
        location[i]->setColor(org_color);
    }
}
