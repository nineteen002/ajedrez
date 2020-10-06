#ifndef KNIGHT_H
#define KNIGHT_H

#include "chesspiece.h"

//Clase derivada para la pieza del caballo

class Knight : public ChessPiece {
    public:
        Knight();
        void move(); //sobrecarga de funcion
};

#endif // KNIGHT_H
