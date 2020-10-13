#ifndef BISHOP_H
#define BISHOP_H

#include "chesspiece.h"

//Clase derivada para la pieza del alfil

class Bishop : public ChessPiece {
    public:
        Bishop(bool team = 0, QGraphicsItem *parent = 0);
        void setImage() override;
        void move() override; //sobrecarga de funcion
};

#endif // BISHOP_H
