#ifndef ROOK_H
#define ROOK_H

#include "chesspiece.h"

//Clase derivada de la pieza de ajedrez Torre

class Rook : public ChessPiece {
    public:
        Rook();
        void move();
};

#endif // ROOK_H
