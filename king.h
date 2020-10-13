#ifndef KING_H
#define KING_H

#include "chesspiece.h"

//Clase derivada para la pieza del REY

class King : public ChessPiece{
    public:
        King(bool team = 0, QGraphicsItem *parent = 0);
        void setImage() override;
        void move() override;
};

#endif // KING_H
