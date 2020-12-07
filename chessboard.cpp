#include "chessboard.h"
#include "boardblock.h"

#include <QDebug>
#include <QWidget>
#include <QtWidgets>
#include <QLineEdit>
#include "loby.h"
#include "socket.h"

extern Loby *loby;
ChessBoard::ChessBoard(QWidget* parent): QGraphicsView(parent) {
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1280,730);    //Window size not sure yet

    //Window properties
    setFixedSize(1280,730); //Size of window can NOT change
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //No scroll bar
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //No scroll bar
    setScene(scene);

    //Background for the window
    QBrush bkg_brush;
    bkg_brush.setColor(Qt::white);
    bkg_brush.setStyle(Qt::SolidPattern);
    setBackgroundBrush(bkg_brush);

    selectedPiece = nullptr;
    this->isGameOver = false;
    QPushButton *send = new QPushButton(this);
    send->setText(tr("Enviar"));
    send->move(1100,690);
    QLineEdit *message = new QLineEdit(this);
    message->move(800,690);
    message->setMinimumSize(280,10);
    message->setMaxLength(100);
    QTextEdit *chat = new QTextEdit(this);
    chat->move(800, 100);
    chat->setMinimumSize(375, 570);
    chat->setReadOnly(true);
}

void ChessBoard::start(){
    drawBoard(width()/2-630,8); //Draws chessboard squares
    //Setup pieces
    setupBlack();
    setupWhite();
    //show pieces on the board
    setupBoard();
    qDebug() << "DEAD KING" ;
    qDebug() << "3" << this->blocks;
    //blocks[3][4]->setChessPiece(white[9]);//Move horse 1 to middle
    //blocks[1][1]->getChessPiece()->move();//try to move pawn
}



void ChessBoard::gameOver(ChessPiece* king){
    QGraphicsTextItem* gameOver = new QGraphicsTextItem();
    gameOver->setPos(900,50);
    gameOver->setZValue(1);
    gameOver->setDefaultTextColor(Qt::red);
    gameOver->setFont(QFont("",30));

    if(king->getSide() == "Black"){
        gameOver->setPlainText("GAME OVER: White won!");
    }
    else{
        gameOver->setPlainText("GAME OVER: Black won!");
    }

    addToWindow(gameOver);

    //ChessBoard::close();
}

void ChessBoard::closeEvent(QCloseEvent *)
{
    loby->closeConnection();
    loby->show();
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

void ChessBoard::chat()
{

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
    kings[1] = piece;

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
    kings[0] = piece;

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
    int b = 0;
    int w = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){ //Go though board

            BoardBlock* block = blocks[i][j];

            if(i < 2){ //first two rows add black chess piece
                block->setChessPiece(black[b]); //add piece to block
                addToWindow(black[b]); //add piece to window
                b++;
            }

            if(i > 5){ //last two rows add black chess piece
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
