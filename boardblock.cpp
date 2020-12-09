#include "boardblock.h"
#include "chessboard.h"
#include "chesspiece.h"
#include <QDebug>

#include "socket.h"
#include "loby.h"
#include "packages.h"

extern ChessBoard* board;
extern Loby *loby;

BoardBlock::BoardBlock(QGraphicsItem *parent): QGraphicsRectItem(parent) {
    //make square block
    setRect(0,0,80,80);
    brush.setStyle(Qt::SolidPattern);//bushstyle
    setZValue(-1);

    this->hasChessPiece = false;
    this->rowNum = 0;
    this->columnNum = 0;
    this->piece = nullptr;
}

void BoardBlock::mousePressEvent(QGraphicsSceneMouseEvent *){

    if(!board->isGameOver) { //if game still going
        if (board->getTurn() == loby->socket->current_team){
            //Haven't selected a piece
            if(!board->selectedPiece) {
                //qDebug() <<  board->getTurn() << this->getChessPiece()->getTeam();
                if(this->hasPiece() && board->getTurn() == this->getChessPiece()->getTeam()) { //if it has a piece and its from the side who's turn it is then
                    this->getChessPiece()->move();
                    board->selectedPiece = this->getChessPiece();
                    return;
                }
            }
            else if(board->selectedPiece) { //Had previously selected piece but change this

                if(this->hasPiece() && board->getTurn() == this->getChessPiece()->getTeam()) { //has a piece but its from the same team
                    board->selectedPiece->unselect();
                    this->getChessPiece()->move();
                    board->selectedPiece = this->getChessPiece();
                    return;
                }

                //check if the position selected is available in the possibles moved from the piece

                QList <BoardBlock*> moveLocations = board->selectedPiece->getPossibleLocations();

                bool possible = false;
                for(int i = 0; i < moveLocations.count(); i++) {
                    if(moveLocations[i] == this){
                        possible = true;
                    }
                }
                //IF ITS A POSSIBLE MOVE

                if(possible) {
                    board->selectedPiece->isFirstMove = false;// applies to pawn and king

                    board->selectedPiece->unselect(); //change color back

                    //check if its box selected is NOT empty
                    if(this->hasPiece()){
                        ChessPiece* eaten = this->getChessPiece();
                        if(eaten == board->kings[0] || eaten == board->kings[1]) {
                            board->isGameOver = true;
                            board->gameOver(eaten);
                        }
                        eaten->setCurrentBlock(nullptr);
                        this->setChessPiece(nullptr);
                        board->removeFromWindow(eaten);
                    }

                    int pos = (board->selectedPiece->getCurrentBlock()->rowNum*8)+(board->selectedPiece->getCurrentBlock()->columnNum);
                    int newPos = (this->rowNum*8) + (this->columnNum);


                    Packages *sendMove = new Packages(3, pos, newPos);
                    loby->socket->sendData(sendMove->getPackMsm());
                    qDebug() << "enviar posicion: " << sendMove->getPackMsm() << "posicion:" <<pos<<" new position: "<< newPos;

                    if(board->selectedPiece->isFirstMove == true){
                        board->selectedPiece->getCurrentBlock()->setChessPiece(nullptr); //PREVIOUS BOX CLEAN
                        this->setChessPiece(board->selectedPiece); //Move selected piece to current box

                        if (board->selectedPiece->castling == true) { //Castling
                            if (board->selectedPiece->getCurrentBlock()->getColumnLocation() == 6){
                                castling(board->selectedPiece->getTeam(), true);
                            }
                            else if (board->selectedPiece->getCurrentBlock()->getColumnLocation() == 2) {
                                castling(board->selectedPiece->getTeam(), false);
                            }
                        }
                    }

                    board->selectedPiece = nullptr; //unselect
                    board->changeTurn();
                    board->showTurn();
                }
            }
        }
    }
}

void BoardBlock::castling(bool team, bool castling){
    int row = -1, colum = -1, columo = -1;
    if (team == true){
        row = 7;
    }
    else {
        row = 0;
    }

    if (castling == true){
        colum = 7;
        columo = colum - 2;
    }
    else {
        colum = 0;
        columo = colum + 3;
    }

    board->selectedPiece = board->blocks[row][colum]->getChessPiece();
    board->selectedPiece->getCurrentBlock()->setChessPiece(nullptr);
    board->blocks[row][columo]->setChessPiece(board->selectedPiece);
}

//Color Related
void BoardBlock::setColor(QColor color){ //Sets color of block
    brush.setColor(color);
    setBrush(color);
}

void BoardBlock::setOriginalColor(QColor color){
    this->originalColor = color;
}

QColor BoardBlock::getOriginalColor(){
    return this->originalColor;
}

void BoardBlock::setLocation(int x, int y){
    this->rowNum = x;
    this->columnNum = y;
}

int BoardBlock::getRowLocation(){
    return this->rowNum;
}

int BoardBlock::getColumnLocation(){
    return this->columnNum;
}

//Chesspiece related
void BoardBlock::setChessPiece(ChessPiece* piece){
    if(!piece){
        hasChessPiece = false;
        this->piece = nullptr;
    }
    else{
        //qDebug() << x()+50- piece->pixmap().width()/2 <<  y()+50-piece->pixmap().width()/2;
        piece->setPos(x()+40- piece->pixmap().width()/2  , y()+40-piece->pixmap().width()/2);
        piece->setCurrentBlock(this);
        hasChessPiece = true;
        this->piece = piece;
    }
}

ChessPiece* BoardBlock::getChessPiece(){
    return this->piece;
}

bool BoardBlock::hasPiece(){
    return hasChessPiece;
}

BoardBlock::~BoardBlock(){
    delete this;
}
