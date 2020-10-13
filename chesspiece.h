#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QGraphicsPixmapItem>

#include "boardblock.h"

class BoardBlock;
class ChessPiece : public QGraphicsPixmapItem{
    protected:
        bool _team; //Blaco =1 o negro =0
        bool isPlaced;
        BoardBlock* currentBlock;

        //Posicion en el tablero

    public:

        ChessPiece(bool team = 0, QGraphicsItem *parent = 0);

        virtual void setImage() = 0; //Will get overwritten in derived classes
        virtual void move() = 0; //Will get overwritten in derived classes

        void setCurrentBlock(BoardBlock *block);
        BoardBlock* getCurrentBlock();

        void setTeam(bool team);
        bool getTeam();

};

#endif // CHESSPIECE_H
