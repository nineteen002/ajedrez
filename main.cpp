#include "mainwindow.h"

#include <QApplication>
#include "chessboard.h"
#include <QDebug>

ChessBoard* board;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    board = new ChessBoard();
    qDebug() << "SHOW" ;
    board->show();

    //MainWindow w;
    //w.show();
    return a.exec();
}
