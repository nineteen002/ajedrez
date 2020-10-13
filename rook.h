#ifndef ROOK_H
#define ROOK_H

#include "chesspiece.h"

//Clase derivada de la pieza de ajedrez Torre

class Rook : public ChessPiece {
    public:
        Rook(bool team = 0, QGraphicsItem *parent = 0);
        void setImage() override;
        void move() override;
};

#endif // ROOK_H
