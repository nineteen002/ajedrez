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
        bool _turn;

        QGraphicsScene* scene;

        QList <ChessPiece*> black;//Chess piece black
        QList <ChessPiece*> deadBlack;

        QList <ChessPiece*> white;//Chess piece white
        QList <ChessPiece*> deadWhite;

        QList <QGraphicsItem*> listItems;


    public:
        ChessBoard(QWidget *parent = 0);
        ~ChessBoard();

       //drawing
        void drawBoard(int x, int y);

        //setup of board
        void setupBoard();
        void setupWhite();
        void setupBlack();

        //Window related
        void addToWindow(QGraphicsItem* item);
        void removeFromWindow(QGraphicsItem* item);

        //Turn related
        void setTurn(bool turn);
        bool getTurn();
        void changeTurn();

        void start();
        void gameOver(ChessPiece*);


        BoardBlock* blocks[8][8];
        ChessPiece* kings[2];
        bool isGameOver;
        ChessPiece* selectedPiece;
};

#endif // CHESSBOARD_H
