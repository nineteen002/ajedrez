#ifndef KNIGHT_H
#define KNIGHT_H

#include "chesspiece.h"

//Clase derivada para la pieza del caballo

class Knight : public ChessPiece {
    public:
        Knight(bool team = 0, QGraphicsItem *parent = 0);
        void setImage() override;
        void move() override;
};

#endif // KNIGHT_H
