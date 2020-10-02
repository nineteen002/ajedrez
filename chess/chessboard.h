#ifndef CHESSBOARD_H
#define CHESSBOARD_H

//Clase para el tablero
class ChessBoard {
    private:
        int _rows = 8; // filas
        int _columns = 8; // columnas

        //Chess piece black
        //Chess piece white

    public:
        ChessBoard();

       //drawing
        void drawBoard();

};

#endif // CHESSBOARD_H
