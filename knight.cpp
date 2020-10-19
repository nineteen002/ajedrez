#include "knight.h"
#include "chessboard.h"

extern ChessBoard *board;
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
    int row = this->getCurrentBlock()->getRowLocation();
    int column = this->getCurrentBlock()->getColumnLocation();
    int i, j;
    QString team = this->getCurrentBlock()->getChessPiece()->getSide();

    //top left
    i = row - 2;
    j = column - 1;
    if (board->blocks[i][j]->hasPiece() == true) {
        if (i >= 0 && j >= 0 && (board->blocks[i][j]->getChessPiece()->getSide() != team)){
            location.append(board->blocks[i][j]);
            if (location.last()->hasPiece()){
                colorPossibleLocations(location.last());
            }
            else {
                colorPossibleLocations(location.last());
            }
        }
    }
    else {
        if (i >= 0 && j >= 0 ){
            location.append(board->blocks[i][j]);
            if (location.last()->hasPiece()){
                colorPossibleLocations(location.last());
            }
            else {
                colorPossibleLocations(location.last());
            }
        }
    }


    //top right
    i = row - 2;
    j = column + 1;
    if (board->blocks[i][j]->hasPiece() == true) {
        if (i >= 0 && j <=7 && (board->blocks[i][j]->getChessPiece()->getSide() != team)){
            location.append(board->blocks[i][j]);
            if (location.last()->hasPiece()){
                colorPossibleLocations(location.last());
            }
            else {
                colorPossibleLocations(location.last());
            }
        }
    }
    else {
        if (i >= 0 && j <= 7 ){
            location.append(board->blocks[i][j]);
            if (location.last()->hasPiece()){
                colorPossibleLocations(location.last());
            }
            else {
                colorPossibleLocations(location.last());
            }
        }
    }
//    //right top
//    i = row - 1;
//    j = column + 2;
//    if (i >= 0 && j <= 7 && (board->blocks[i][j]->getChessPiece()->getSide() != team)){
//        location.append(board->blocks[i][j]);
//        if (location.last()->hasPiece()){
//            colorPossibleLocations(location.last());
//        }
//        else {
//            colorPossibleLocations(location.last());
//        }
//    }

//    //right down
//    i = row + 1;
//    j = column + 2;
//    if (i <= 7 && j <= 7 && (board->blocks[i][j]->getChessPiece()->getSide() != team)){
//        location.append(board->blocks[i][j]);
//        if (location.last()->hasPiece()){
//            colorPossibleLocations(location.last());
//        }
//        else {
//            colorPossibleLocations(location.last());
//        }
//    }

//    //left top
//    i = row - 1;
//    j = column - 2;
//    if (i >= 0 && j >= 0 && (board->blocks[i][j]->getChessPiece()->getSide() != team)){
//        location.append(board->blocks[i][j]);
//        if (location.last()->hasPiece()){
//            colorPossibleLocations(location.last());
//        }
//        else {
//            colorPossibleLocations(location.last());
//        }
//    }

//    //left down
//    i = row + 1;
//    j = column - 2;
//    if (i <= 7 && j >= 0 && (board->blocks[i][j]->getChessPiece()->getSide() != team)){
//        location.append(board->blocks[i][j]);
//        if (location.last()->hasPiece()){
//            colorPossibleLocations(location.last());
//        }
//        else {
//            colorPossibleLocations(location.last());
//        }
//    }

//    //down left
//    i = row + 2;
//    j = column - 1;
//    if (i <= 7 && j >= 0 && (board->blocks[i][j]->getChessPiece()->getSide() != team)){
//        location.append(board->blocks[i][j]);
//        if (location.last()->hasPiece()){
//            colorPossibleLocations(location.last());
//        }
//        else {
//            colorPossibleLocations(location.last());
//        }
//    }

//    //down right
//    i = row - 2;
//    j = column - 1;
//    if (i >= 0 && j >= 0 && (board->blocks[i][j]->getChessPiece()->getSide() != team)){
//        location.append(board->blocks[i][j]);
//        if (location.last()->hasPiece()){
//            colorPossibleLocations(location.last());
//        }
//        else {
//            colorPossibleLocations(location.last());
//        }
//    }

}
