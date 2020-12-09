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
    respuesta = 0;
    Packages *pack = new Packages(5, this->respuesta, 0 );
    loby->socket->sendData(pack->getPackMsm());
    this->close();
    board->close();
    QMessageBox *alert = new QMessageBox();
    alert->setText("Se cerro la conexion");
}

void DNS::on_pushButton_clicked()
{
    //delete board;
    respuesta = 1;
    Packages *pack = new Packages(5, this->respuesta, 0 );
    loby->socket->sendData(pack->getPackMsm());
    board->hide();
    board= new ChessBoard();
    board->show();
    board->start();
    this->close();
}
