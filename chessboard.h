#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QGraphicsView>
#include <QGraphicsScene>

#include "chesspiece.h"
#include "boardblock.h"
#include "queen.h"
#include "rook.h"
#include "pawn.h"
#include "king.h"
#include "knight.h"
#include "bishop.h"

class ChessBoard : public QGraphicsView{ //Clase para el tablero
    Q_OBJECT
    private:
        int const _size = 100;
        QGraphicsScene* scene;
        BoardBlock* blocks[8][8];

        QList <ChessPiece*> black;//Chess piece black
        QList <ChessPiece*> white;//Chess piece white

    public:
        ChessBoard(QWidget *parent = 0);
        ~ChessBoard();

       //drawing
        void drawBoard(int x, int y);
        void addToWindow(QGraphicsItem* item);

        void setupWhite();
        void setupBlack();

        void setupBoard();
};

#endif // CHESSBOARD_H
