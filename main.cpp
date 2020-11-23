#include <QApplication>
#include <QDebug>
#include <QTcpSocket>
#include <QObject>

//#include "chessboard.h"
#include "socket.h"
#include "loby.h"

Loby* loby;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    char port[5] = "4994";
    Socket socket;
    socket.startConnectionWithServer(serverName, port);
    //try sending
    char buffer[1024];
    strcpy(buffer,"I AM THE KING OF THE WORLD");
    socket.sendData(buffer);
  
    loby=new Loby();
    loby->show();
    loby->show();
    return a.exec();
}
