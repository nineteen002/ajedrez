#include "loby.h"
#include "ui_loby.h"
#include "chessboard.h"

ChessBoard* board;

Loby::Loby(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Loby)
{
    ui->setupUi(this);
    packageLog = nullptr;
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
    nameUser = ui->userName->text();
    packageLog = new Packages(0, nameUser);
    char serverName[50] = "ajedrez.elinfelix.xserver.fun";
    char port[5] = "4994";
    socket = new Socket();
    if (socket->startConnectionWithServer(serverName, port) ==  true){
        socket->sendData(packageLog->getPackMsm());
        this->hide();
        board = new ChessBoard();
        board->show();
        //board->start();
    }
    else {
        QMessageBox *alert = new QMessageBox();
        alert->setText("Error en la conexión");
        alert->show();
    }
    //try sending
}

void Loby::closeConnection(){
    socket->closeSocket();
}
