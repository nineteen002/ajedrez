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
    url = ui->urlText->text();
    ports = ui->portText->text();
    packageLog = new Packages(0, nameUser);
    char serverName[50];
    strcpy(serverName,  url.toStdString().c_str());
    char port[5] = "4994";
    strcpy(port, ports.toStdString().c_str());
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
