#include "rook.h"
#include "chessboard.h"
#include <QDebug>

extern ChessBoard *board;
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
    location.clear();
    int row = this->getCurrentBlock()->getRowLocation();
    int column = this->getCurrentBlock()->getColumnLocation();
    int i = 0;
    int j = 0;
    QString team = this->getCurrentBlock()->getChessPiece()->getSide();

    //Move top
    i = row - 1;
    j = column;
    for (;i>=0; i--){
        if (board->blocks[i][j]->hasPiece() == true) {
            if (board->blocks[i][j]->getChessPiece()->getSide() != team) {
                location.append(board->blocks[i][j]);
                colorPossibleLocations(location.last());
                break;
            }
            else {
                break;
            }
        }
        else {
            location.append(board->blocks[i][j]);
            colorPossibleLocations(location.last());
        }
    }

    //Move down
    i = row + 1;
    j = column;
    for ( ; i <= 7; i++){
        if (board->blocks[i][j]->hasPiece() == true) {
            if (board->blocks[i][j]->getChessPiece()->getSide() != team) {
                location.append(board->blocks[i][j]);
                colorPossibleLocations(location.last());
                break;
            }
            else {
                break;
            }
        }
        else {
            location.append(board->blocks[i][j]);
            colorPossibleLocations(location.last());
        }
    }

    //Move left
    i = row;
    j = column - 1;
    for (; j >= 0 ; j--){
        if (board->blocks[i][j]->hasPiece() == true) {
            if (board->blocks[i][j]->getChessPiece()->getSide() != team) {
                location.append(board->blocks[i][j]);
                colorPossibleLocations(location.last());
                break;
            }
            else {
                break;
            }
        }
        else {
            location.append(board->blocks[i][j]);
            colorPossibleLocations(location.last());
        }
    }

    //Move rigth
    i = row;
    j = column + 1;
    for (; j <= 7 ; j++){
        if (board->blocks[i][j]->hasPiece() == true) {
            if (board->blocks[i][j]->getChessPiece()->getSide() != team) {
                location.append(board->blocks[i][j]);
                colorPossibleLocations(location.last());
                break;
            }
            else {
                break;
            }
        }
        else {
            location.append(board->blocks[i][j]);
            colorPossibleLocations(location.last());
        }
    }
}
