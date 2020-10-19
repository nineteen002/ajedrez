#ifndef PAWN_H
#define PAWN_H

#include "chesspiece.h"
#include "chessboard.h"

//Clase derivada de la pieza de ajedrez peon
class Pawn : public ChessPiece {

    public:
        Pawn(bool team = 0, QGraphicsItem *parent = 0);
        void setImage() override;
        void move() override;
};

#endif // PAWN_H
