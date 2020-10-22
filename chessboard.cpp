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

    selectedPiece = nullptr;
}

void ChessBoard::start(){
    drawBoard(width()/2-650,50); //Draws chessboard squares
    //Setup pieces
    setupBlack();
    setupWhite();
    //show pieces on the board
    setupBoard();
    qDebug() << "3" << this->blocks;
    //blocks[3][4]->setChessPiece(white[9]);//Move horse 1 to middle
    //blocks[1][1]->getChessPiece()->move();//try to move pawn
}

void ChessBoard::drawBoard(int x, int y){ //recieves inital coordinates
    for(int i = 0; i < 8; i++){ //For each row
        for(int j = 0; j < 8; j++){ //For each column

            BoardBlock *block = new BoardBlock(); //Create a chessboard block
            this->blocks[i][j] = block; //add it to array
            //Calculates position
            int x_step = _size * j;
            int y_step = _size * i;

            block->setLocation(i,j);
            block->setPos(x + x_step, y + y_step); //calculates (x, y) init pos of each block

            if((i+j)%2 == 0){
                block->setOriginalColor(QColor(42,154,79));
                block->setColor(QColor(42,154,79));//set color green
            } else {
                block->setOriginalColor(QColor(186,190,107)); //set color yellowish
                block->setColor(QColor(186,190,107));
            }

            this->addToWindow(block); //Add it to window
        }
    }
}

void ChessBoard::setupWhite(){//sets up black chess pieces
    ChessPiece* piece;
    for(int i = 0; i < 8; i++){
        piece = new Pawn(1);
        white.append(piece);
    }

    piece = new Rook(1);
    white.append(piece);

    piece = new Knight(1);
    white.append(piece);

    piece = new Bishop(1);
    white.append(piece);

    piece = new Queen(1);
    white.append(piece);

    piece = new King(1);
    white.append(piece);

    piece = new Bishop(1);
    white.append(piece);

    piece = new Knight(1);
    white.append(piece);

    piece = new Rook(1);
    white.append(piece);
}

void ChessBoard::setupBlack(){ //sets up black chess pieces
    ChessPiece* piece;

    piece = new Rook();
    black.append(piece);

    piece = new Knight();
    black.append(piece);

    piece = new Bishop();
    black.append(piece);

    piece = new Queen();
    black.append(piece);

    piece = new King();
    black.append(piece);

    piece = new Bishop();
    black.append(piece);

    piece = new Knight();
    black.append(piece);

    piece = new Rook();
    black.append(piece);

    for(int i = 0; i < 8; i++){
        piece = new Pawn();
        black.append(piece);
    }
}

void ChessBoard::setupBoard(){ //Puts pieces in the board
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){ //Go though board

            BoardBlock* block = blocks[i][j];

            if(i < 2){ //first two rows add black chess piece
                static int b = 0;
                block->setChessPiece(black[b]); //add piece to block
                addToWindow(black[b]); //add piece to window
                b++;
            }

            if(i > 5){ //last two rows add black chess piece
                static int w = 0;
                block->setChessPiece(white[w]);
                addToWindow(white[w]);
                w++;
            }
        }
    }
    this->setTurn(1);
}

void ChessBoard::addToWindow(QGraphicsItem* item){
    scene->addItem(item);
}

void ChessBoard::removeFromWindow(QGraphicsItem* item){
    scene->removeItem(item);
}

void ChessBoard::setTurn(bool turn){
    this->_turn = turn;
}

bool ChessBoard::getTurn(){
    return this->_turn;
}

void ChessBoard::changeTurn(){
    if(this->getTurn() == 0){
        this->setTurn(1);
    } else {
        this->setTurn(0);
    }
}

ChessBoard::~ChessBoard(){
    delete this;
}
