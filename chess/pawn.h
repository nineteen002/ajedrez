#ifndef PAWN_H
#define PAWN_H

#include "chesspiece.h"

//Clase derivada de la pieza de ajedrez peon

class Pawn : public ChessPiece {

    public:
        Pawn();
        void move(); //sobrecarga de funcion
};

#endif // PAWN_H
