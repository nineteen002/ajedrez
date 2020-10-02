#ifndef QUEEN_H
#define QUEEN_H

#include "chesspiece.h"

//Clase derivada de la pieza de ajedrez REINA

class Queen : public ChessPiece  {
    public:
        Queen();
        void move();
};

#endif // QUEEN_H
