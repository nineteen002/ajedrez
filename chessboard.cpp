#include "chessboard.h"
#include "boardblock.h"

#include <QDebug>

ChessBoard::ChessBoard(QWidget* parent): QGraphicsView(parent) {
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1400,900);    //Window size not sure yet

    //Window properties
    setFixedSize(1400,900); //Size of window can NOT change
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //No scroll bar
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //No scroll bar
    setScene(scene);

    //Background for the window
    QBrush bkg_brush;
    bkg_brush.setColor(Qt::white);
    bkg_brush.setStyle(Qt::SolidPattern);
    setBackgroundBrush(bkg_brush);

    drawBoard(width()/2-650,50);
    this->show();
}

void ChessBoard::drawBoard(int x, int y){ //recieves inital coordinates
    for(int i = 0; i < _rows; i++){ //For each row
        for(int j = 0; j < _columns; j++){ //For each column

            BoardBlock *block = new BoardBlock(); //Create a chessboard block
            this->blocks[i][j] = block; //add it to array
            //Calculates position
            int x_step = _size * j;
            int y_step = _size * i;

            block->setPos(x + x_step, y + y_step); //calculates (x, y) init pos of each block

            if((i+j)%2 == 0){
                block->setColor(QColor(42,154,79)); //set color green
            } else {
                block->setColor(QColor(186,190,107)); //set color yellowish
            }

            this->addToWindow(block); //Add it to window
        }
    }
}

void ChessBoard::addToWindow(QGraphicsItem* item){
    scene->addItem(item);
}

ChessBoard::~ChessBoard(){
    delete this;
}
