#include "loby.h"
#include "ui_loby.h"
#include "chessboard.h"

ChessBoard* board;

Loby::Loby(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Loby)
{
    ui->setupUi(this);
}

Loby::~Loby()
{
    delete ui;
}

void Loby::on_pushButton_2_clicked()
{
    this->close();
}

void Loby::on_pushButton_clicked()
{

    char serverName[50] = "ajedrez.elinfelix.xserver.fun";
    char port[5] = "4994";

    socket = new Socket();
    socket->startConnectionWithServer(serverName, port);

    //try sending
    char buffer[1024];
    strcpy(buffer,"I AM THE KING OF THE WORLD");
    socket->sendData(buffer);

    this->hide();
    board = new ChessBoard();
    board->show();
    board->start();

}

void Loby::closeConnection(){
    //socket->closeSocket();
}
