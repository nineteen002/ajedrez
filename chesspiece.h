#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QGraphicsPixmapItem>
#include <QString>
#include "boardblock.h"

class BoardBlock;
class ChessPiece : public QGraphicsPixmapItem{
    protected:
        bool _team; //WHITE=1 o BLACK=0
        bool isPlaced;

        BoardBlock* currentBlock;
        QList <BoardBlock*> location;

        //Posicion en el tablero

    public:
        bool isFirstMove;
        ChessPiece(bool team = 0, QGraphicsItem *parent = 0);

        virtual void setImage() = 0; //Will get overwritten in derived classes
        virtual void move() = 0; //Will get overwritten in derived classes

        void setCurrentBlock(BoardBlock *block);
        BoardBlock* getCurrentBlock();

        void setTeam(bool team);
        bool getTeam();
        QString getSide();

        void setPlaced(bool placed);
        bool getIsPlaced();

        QList <BoardBlock*> getPossibleLocations();
        void colorPossibleLocations(BoardBlock *box);
        void unselect();

};

#endif // CHESSPIECE_H
