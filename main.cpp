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
    char serverName[50] = "ajedrez.elinfelix.xserver.fun";
    if(serverName[strlen(serverName) - 1] == '\n') serverName[strlen(serverName) -1] = '\0';

    char port[5] = "4994";
    Socket socket;
    socket.startConnectionWithServer(serverName, port);

    board = new ChessBoard();
    qDebug() << "1" <<board;
    board->show();
    board->start();
    return a.exec();
    //MainWindow w;
    //w.show();
}
