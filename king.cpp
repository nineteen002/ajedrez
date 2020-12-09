#include "king.h"
#include "chessboard.h"
#include <QDebug>

extern ChessBoard *board;
King::King(bool team, QGraphicsItem *parent) : ChessPiece(team,parent){
    setImage();
    isFirstMove = true;
    castling = false;
}

void King::setImage(){
    if(_team == 0)
        setPixmap(QPixmap(":/images/king_blk.png"));
    else
        setPixmap(QPixmap(":/images/king_white.png"));
}

void King::move(){
    location.clear();
    int row = this->getCurrentBlock()->getRowLocation();
    int column = this->getCurrentBlock()->getColumnLocation();
    int i = 0;
    int j = 0;
    QString team = this->getCurrentBlock()->getChessPiece()->getSide();

    //Castling
        i = row;
        j = column;
        if  (this->isFirstMove == true){
            //Short castling
            if (board->blocks[i][j+1]->hasPiece() == false && board->blocks[i][j+2]->hasPiece() == false && board->blocks[i][j+3]->getChessPiece()->isFirstMove == true){
                location.append(board->blocks[i][j+2]);
                colorPossibleLocations(location.last());
                castling = true;
            }
            //Long castling
            if (board->blocks[i][j-1]->hasPiece() == false && board->blocks[i][j-2]->hasPiece() == false && board->blocks[i][j-3]->hasPiece() == false && board->blocks[i][j-4]->getChessPiece()->isFirstMove == true){
                location.append(board->blocks[i][j-2]);
                colorPossibleLocations(location.last());
                castling = true;
            }
        }

    //Top
    i = row - 1;
    j = column;
    if (i >= 0){
        if (board->blocks[i][j]->hasPiece() == true) {
            if (board->blocks[i][j]->getChessPiece()->getSide() != team) {
                location.append(board->blocks[i][j]);
                colorPossibleLocations(location.last());
                //break;
            }
            else {
                //break;
            }
        }
        else {
            location.append(board->blocks[i][j]);
            colorPossibleLocations(location.last());
        }
    }

    //Down
    i = row + 1;
    j = column;
    if (i <= 7){
        if (board->blocks[i][j]->hasPiece() == true) {
            if (board->blocks[i][j]->getChessPiece()->getSide() != team) {
                location.append(board->blocks[i][j]);
                colorPossibleLocations(location.last());
                //break;
            }
            else {
                //break;
            }
        }
        else {
            location.append(board->blocks[i][j]);
            colorPossibleLocations(location.last());
        }
    }

    //Rigth
    i = row;
    j = column + 1;
    if (j <= 7){
        if (board->blocks[i][j]->hasPiece() == true) {
            if (board->blocks[i][j]->getChessPiece()->getSide() != team) {
                location.append(board->blocks[i][j]);
                colorPossibleLocations(location.last());
                //break;
            }
            else {
                //break;
            }
        }
        else {
            location.append(board->blocks[i][j]);
            colorPossibleLocations(location.last());
        }
    }

    //Left
    i = row;
    j = column - 1;
    if (j >= 0){
        if (board->blocks[i][j]->hasPiece() == true) {
            if (board->blocks[i][j]->getChessPiece()->getSide() != team) {
                location.append(board->blocks[i][j]);
                colorPossibleLocations(location.last());
                //break;
            }
            else {
                //break;
            }
        }
        else {
            location.append(board->blocks[i][j]);
            colorPossibleLocations(location.last());
        }
    }

    //Rigth top
    i = row - 1;
    j = column + 1;
    if (i >= 0 && j <= 7){
        if (board->blocks[i][j]->hasPiece() == true) {
            if (board->blocks[i][j]->getChessPiece()->getSide() != team) {
                location.append(board->blocks[i][j]);
                colorPossibleLocations(location.last());
                //break;
            }
            else {
                //break;
            }
        }
        else {
            location.append(board->blocks[i][j]);
            colorPossibleLocations(location.last());
        }
    }

    //Left top
    i = row - 1;
    j = column - 1;
    if (i >= 0 && j >= 0){
        if (board->blocks[i][j]->hasPiece() == true) {
            if (board->blocks[i][j]->getChessPiece()->getSide() != team) {
                location.append(board->blocks[i][j]);
                colorPossibleLocations(location.last());
                //break;
            }
            else {
                //break;
            }
        }
        else {
            location.append(board->blocks[i][j]);
            colorPossibleLocations(location.last());
        }
    }

    //Down rigth
    i = row + 1;
    j = column + 1;
    if (i <= 7 && j <= 7){
        if (board->blocks[i][j]->hasPiece() == true) {
            if (board->blocks[i][j]->getChessPiece()->getSide() != team) {
                location.append(board->blocks[i][j]);
                colorPossibleLocations(location.last());
                //break;
            }
            else {
                //break;
            }
        }
        else {
            location.append(board->blocks[i][j]);
            colorPossibleLocations(location.last());
        }
    }

    //Down rigth
    i = row + 1;
    j = column - 1;
    if (i <= 7 && j >= 0){
        if (board->blocks[i][j]->hasPiece() == true) {
            if (board->blocks[i][j]->getChessPiece()->getSide() != team) {
                location.append(board->blocks[i][j]);
                colorPossibleLocations(location.last());
                //break;
            }
            else {
                //break;
            }
        }
        else {
            location.append(board->blocks[i][j]);
            colorPossibleLocations(location.last());
        }
    }
}
