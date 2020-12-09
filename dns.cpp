#include "dns.h"
#include "ui_dns.h"
#include <QLineEdit>
#include "chessboard.h"

extern ChessBoard* board;

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
}
