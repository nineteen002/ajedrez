#ifndef CHESSPIECE_H
#define CHESSPIECE_H

//Clase para las piezas
class ChessPiece {
    protected:
        bool _team; //Blaco o negro

        //Posicion en el tablero

    public:

        ChessPiece();

        virtual void move(); //Will get overwritten in derived classes
};

#endif // CHESSPIECE_H
