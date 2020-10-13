#ifndef KING_H
#define KING_H

#include "chesspiece.h"

//Clase derivada para la pieza del REY

class King : public ChessPiece{
    public:
        King();
        void move();
};

#endif // KING_H
