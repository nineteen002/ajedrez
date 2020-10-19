#include "pawn.h"
#include "chessboard.h"

extern ChessBoard *board;
Pawn::Pawn(bool team, QGraphicsItem *parent) : ChessPiece(team,parent){
    setImage();
}

void Pawn::setImage(){
    if(_team == 0)
        setPixmap(QPixmap(":/images/pawn_blk.png"));
    else
        setPixmap(QPixmap(":/images/pawn_white.png"));
}

void Pawn::move(){/*
    location.clear(); //clean previous locations
    //get current location
    int row = this->getCurrentBlock()->getRowLocation();
    int column = this->getCurrentBlock()->getColumnLocation();

    if(this->getSide() == "White"){
        //MOVE FORWARD
        BoardBlock *block= board->blocks[row-1][column];
        bool hasPiece = block->hasPiece();
        if(row > 0 && !hasPiece){ //if no one is blocking, move forward
            location.append(board->blocks[row-1][column]);
            colorPossibleLocations(location.last());
            if(isFirstMove && !board->blocks[row-2][column]->hasPiece()){
                location.append(board->blocks[row-1][column]);
                colorPossibleLocations(location.last());
            }
        }
        //EATS TO THE SIDES:
        if(row > 0 && column > 0 && board->blocks[row-1][column-1]->getChessPiece()->getSide() == "Black") {//CHECK LEFT and 1 up
            location.append(board->blocks[row-1][column-1]);
            colorPossibleLocations(location.last());
        }
        if(row > 0 && column < 7 && board->blocks[row-1][column+1]->getChessPiece()->getSide() == "Black") {//CHECK Right and 1 up
            location.append(board->blocks[row-1][column+1]);
            colorPossibleLocations(location.last());
        }
    }*/

}
