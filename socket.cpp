#include "socket.h"

Socket::Socket(QObject *parent) : QObject(parent)
{

}

void Socket::connect(){
    socket = new QTcpSocket(nullptr);
    socket->connectToHost("2806:2f0:51e1:151a:a00:27ff:fe8c:3a2d", 4994);

    if(socket->waitForConnected(3000)){
        qDebug() << "Coneccted to server";

        //sending info
        socket->write("Socket de Fer Prueba4-1");

        socket->waitForBytesWritten(100);
        socket->waitForReadyRead(3000);
        qDebug() << "Reading: " << socket->bytesAvailable();
        qDebug() << socket->readAll();

        socket->close();
    }
    else{
        qDebug() << "Failed connection :C";
    }
}

void Socket::sendInitialConectionPackage(){
    QString package = "0";

    QByteArray bytes("hello", 1);
    int length = bytes.size(); //Number of bytes
    qDebug() << "Bytes: " << bytes <<" Length is:" << length;
}
