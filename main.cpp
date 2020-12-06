#include <QApplication>
#include <QDebug>
#include <QTcpSocket>
#include <QObject>

//#include "chessboard.h"
#include "loby.h"

Loby* loby;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    loby=new Loby();
    loby->show();
    return a.exec();
}
