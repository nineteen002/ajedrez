#include "bishop.h"
#include "chessboard.h"
#include <QDebug>

extern ChessBoard *board;
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
    location.clear();
    int row = this->getCurrentBlock()->getRowLocation();
    int column = this->getCurrentBlock()->getColumnLocation();
    int i = 0;
    int j = 0;
    QString team = this->getCurrentBlock()->getChessPiece()->getSide();

    //Move rigt-top
    i = row - 1;
    j = column + 1;
    for (; i >= 0 && j <= 7; i--, j++) {
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

    //Move lefth-top
    i = row - 1;
    j = column - 1;
    for (; i >= 0 && j >= 0; i--, j-- ){
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

    //Move left-down
    i = row + 1;
    j = column + 1;
    for (; i <= 7 && j <= 7; i++, j++){
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

    //Move rigth-down
    i = row + 1;
    j = column -1;
    for (; i <=7 && j >= 0; i++ , j--){
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
