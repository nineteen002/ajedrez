#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QGraphicsView>
#include <QGraphicsScene>

#include "chesspiece.h"
#include "boardblock.h"

class ChessBoard : public QGraphicsView{ //Clase para el tablero
    Q_OBJECT
    private:
        QGraphicsScene* scene;

        int const _rows = 8; // filas
        int const _columns = 8; // columnas
        int const _size = 100; //size of each tile
        BoardBlock* blocks[8][8];

        //Chess piece black
        //Chess piece white

    public:
        ChessBoard(QWidget *parent = 0);
        ~ChessBoard();

       //drawing
        void drawBoard(int x, int y);
        void addToWindow(QGraphicsItem* item);
};

#endif // CHESSBOARD_H
