#ifndef BOARDBLOCK_H
#define BOARDBLOCK_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QColor>
#include <QGraphicsSceneMouseEvent>

//Represents each block in the chess board
class ChessPiece;
class BoardBlock : public QGraphicsRectItem {
    private:
        int rowNum;
        int columnNum;
        ChessPiece* piece;

        QColor originalColor;
        QBrush brush;
        bool hasChessPiece;

    public:
        BoardBlock(QGraphicsItem *parent=0);
        ~BoardBlock();

        void mousePressEvent(QGraphicsSceneMouseEvent *event);

        //Color related
        void setColor(QColor color);
        QColor getColor();

        void resetColor();
        void setOriginalColor(QColor color);
        QColor getOriginalColor();

        void setLocation(int x, int y);
        int getRowLocation();
        int getColumnLocation();

        //Chess piece related
        void setChessPiece(ChessPiece* piece);
        ChessPiece* getChessPiece();
        void castling(bool team, bool castling);
        bool hasPiece();
};

#endif // BOARDBLOCK_H
