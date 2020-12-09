#include "chessboard.h"
#include "boardblock.h"
#include <string.h>
#include <iostream>
#include <QDebug>
#include <QWidget>
#include <QtWidgets>

#include "loby.h"
#include "dns.h"

extern Loby *loby;
DNS* dns;

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
    send = new QPushButton("Enviar",this);
    send->move(1100,690);
    connect(send, SIGNAL(released()), this, SLOT (sendMsm()));
    message = new QLineEdit(this);
    message->move(800,690);
    message->setMinimumSize(280,10);
    message->setMaxLength(100);
    chat = new QTextEdit(this);
    chat->move(800, 100);
    chat->setMinimumSize(375, 570);
    chat->setReadOnly(true);

    turnChange = new QGraphicsTextItem();
    _turn = 1;
    showTurn();
}

void ChessBoard::sendMsm()
{
    char buffer[256];
    char buffer1[256];
    std::string cadena = message->text().toStdString(); //message =  qlineedit
    std::string cadena1 = loby->nameUser.toStdString();
    strcpy(buffer, cadena.c_str());
    strcpy(buffer1, cadena1.c_str());
    qDebug() << "Qstring: " << loby->nameUser << "buffer: "<< buffer1;
    this->chatMessage(buffer1, buffer);
    Packages *sendMSM = new Packages(9, message->text());
    loby->socket->sendData(sendMSM->getPackMsm());
    message->clear();
}

void ChessBoard::start(){
    drawBoard(width()/2-630,8); //Draws chessboard squares

    //Setup pieces
    setupBlack();
    setupWhite();
    //show pieces on the board
    setupBoard();
}

void ChessBoard::gameOver(ChessPiece* king){
    QGraphicsTextItem* gameOver = new QGraphicsTextItem();
    gameOver->setPos(800,20);
    gameOver->setZValue(1);
    gameOver->setDefaultTextColor(Qt::red);
    gameOver->setFont(QFont("",20));

    if(king->getSide() == "Black"){
        gameOver->setPlainText("GAME OVER: White won!");
    }
    else{
        gameOver->setPlainText("GAME OVER: Black won!");
    }
    addToWindow(gameOver);
    dns = new DNS();
    dns->show();

    //ChessBoard::close();
}

void ChessBoard::showTurn()
{
    removeFromWindow(turnChange);
    turnChange = new QGraphicsTextItem();
    turnChange->setZValue(1);
    turnChange->setFont(QFont("",20));

    if(this->getTurn() == 0){
        turnChange->setPos(800,50);
        turnChange->setDefaultTextColor(Qt::black);
        turnChange->setPlainText("Turn: Black");
    }
    else{
        turnChange->setPos(1010,50);
        turnChange->setDefaultTextColor(Qt::blue);
        turnChange->setPlainText("Turn: White");
    }
    addToWindow(turnChange);
}

void ChessBoard::sayTeam()
{
    if (loby->socket->current_team == 1){
        //yourTeam->setPlainText("Te tocan Blancas");
        char how[256] = "Server ";
        char msm[256] = "Te tocan Blancas";
        this->chatMessage(how,msm);
    }
    else if (loby->socket->current_team == 0){
        //yourTeam->setPlainText("");
        char how[256] = "Server";
        char msm[256] = "Te tocan negras";
        this->chatMessage(how,msm);
    }
}

void ChessBoard::enemyMove(int posa, int posf)
{

    int row = (posa/8);
    int col = posa%8;
    qDebug()<<"Enemy move "<< "row:"<< row << "col:" << col;
    this->selectedPiece = this->blocks[row][col]->getChessPiece();
    //this->selectedPiece->move();
    int rowf = posf/8;
    int colf = posf%8;
    qDebug()<<"Enemy move "<< "rowf:"<< rowf << "colf:" << colf;

    this->selectedPiece->getCurrentBlock()->setChessPiece(nullptr);
    BoardBlock* final_pos = this->blocks[rowf][colf];
    //check if its box selected is NOT empty
    if(final_pos->hasPiece()){
        ChessPiece* eaten = final_pos->getChessPiece();
        if(eaten == this->kings[0] || eaten == this->kings[1]) {
            qDebug() << "Gameover";
            this->isGameOver = true;
            this->gameOver(eaten);
        }
        eaten->setCurrentBlock(nullptr);
        final_pos->setChessPiece(nullptr);
        this->removeFromWindow(eaten);
    }

    final_pos->setChessPiece(this->selectedPiece);
    if (this->selectedPiece->isFirstMove == true){
        if (this->selectedPiece == this->kings[0] || this->selectedPiece == this->kings[1]){
            qDebug() << "Moving King";
            if (this->selectedPiece->getCurrentBlock()->getColumnLocation() == 6 && (this->selectedPiece->getCurrentBlock()->getRowLocation() == 0 || this->selectedPiece->getCurrentBlock()->getRowLocation() == 7)){
                qDebug() << "short";
                this->selectedPiece->castling = false;
                this->selectedPiece->getCurrentBlock()->castling(this->selectedPiece->getTeam(), true);
            }
            else if (this->selectedPiece->getCurrentBlock()->getColumnLocation() == 2 && (this->selectedPiece->getCurrentBlock()->getRowLocation() == 0 || this->selectedPiece->getCurrentBlock()->getRowLocation() == 7)) {
                qDebug() << "long";
                this->selectedPiece->castling = false;
                this->selectedPiece->getCurrentBlock()->castling(this->selectedPiece->getTeam(), false);
            }
        }
        this->selectedPiece->isFirstMove = false;
    }
    this->selectedPiece = nullptr;
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

void ChessBoard::chatMessage(char how[], char *message)
{
    char nombreUsuario[256];
    memset((char*)&nombreUsuario,0, sizeof(nombreUsuario));
    for (int i = 0; i < strlen(how); i++){
        nombreUsuario[i]=how[i];
    }

    qDebug()<< "how: "<< how << "message" << message << "Nombre de usuario" << nombreUsuario;
    strcat(nombreUsuario, ": ");
    QString mesage = strcat(nombreUsuario, message);
    qDebug() << "Qstring: "<< mesage;
    chat->append(mesage);
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
