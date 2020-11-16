#include <QApplication>
#include "chessboard.h"
#include <QDebug>
#include "mainwindow.h"

ChessBoard* board;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    board = new ChessBoard();
//    qDebug() << "1" <<board;
//    board->show();
//    board->start();
    MainWindow w;
    w.show();
    return a.exec();

}
