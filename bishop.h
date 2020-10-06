#ifndef BISHOP_H
#define BISHOP_H

#include "chesspiece.h"

//Clase derivada para la pieza del alfil

class Bishop : public ChessPiece {
    public:
        Bishop();
        void move(); //sobrecarga de funcion
};

#endif // BISHOP_H
