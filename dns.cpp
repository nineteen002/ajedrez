#include "dns.h"
#include "ui_dns.h"
#include <QLineEdit>
#include "chessboard.h"
#include "packages.h"
#include "loby.h"

extern ChessBoard* board;
extern Loby* loby;

DNS::DNS(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DNS)
{
    ui->setupUi(this);

}

DNS::~DNS()
{
    delete ui;
}

void DNS::on_pushButton_2_clicked()
{
    this->close();
    respuesta = 0;
    board->close();
    Packages *pack = new Packages(5, this->respuesta, 0 );
    loby->socket->sendData(pack->getPackMsm());
}

void DNS::on_pushButton_clicked()
{
    //delete board;

    board->hide();
    board= new ChessBoard();
    board->show();
    board->start();
    this->close();
    respuesta = 1;
    Packages *pack = new Packages(5, this->respuesta, 0 );
    loby->socket->sendData(pack->getPackMsm());
}
