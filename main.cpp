#include <QApplication>
//#include "chessboard.h"
#include <QDebug>
#include "loby.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    board = new ChessBoard();
//    qDebug() << "1" <<board;
//    board->show();
//    board->start();
    Loby loby;
    loby.show();
    return a.exec();

}
