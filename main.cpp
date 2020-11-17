#include <QApplication>
#include <QDebug>
#include <QTcpSocket>
#include <QObject>

#include "chessboard.h"
#include "socket.h"

ChessBoard* board;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Socket socket;
    socket.connect();

    board = new ChessBoard();
    qDebug() << "1" <<board;
    board->show();
    board->start();
    return a.exec();
    //MainWindow w;
    //w.show();
}
