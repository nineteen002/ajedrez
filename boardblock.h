#ifndef BOARDBLOCK_H
#define BOARDBLOCK_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QColor>

//Represents each block in the chess board
class ChessPiece;
class BoardBlock : public QGraphicsRectItem {
    private:
        int rowNum;
        int columnNum;
        ChessPiece* piece;

        QColor color;
        QBrush brush;
        bool hasChessPiece;

    public:
        BoardBlock(QGraphicsItem *parent=0);
        ~BoardBlock();

        void setColor(QColor color);
        QColor getColor();

        void setLocation(int x, int y);
        void setChessPiece(ChessPiece* piece);
        ChessPiece* getChessPiece();

        bool hasPiece();
};

#endif // BOARDBLOCK_H
