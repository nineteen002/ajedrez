#ifndef QUEEN_H
#define QUEEN_H

#include "chesspiece.h"

//Clase derivada de la pieza de ajedrez REINA

class Queen : public ChessPiece  {
    public:
        Queen(bool team = 0, QGraphicsItem *parent = 0);
        void setImage() override;
        void move() override;
};

#endif // QUEEN_H
