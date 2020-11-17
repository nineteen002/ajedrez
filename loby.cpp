#include "loby.h"
#include "ui_loby.h"
#include "chessboard.h"

ChessBoard *board;

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
    board = new ChessBoard();
    board->show();
    board->start();
}
