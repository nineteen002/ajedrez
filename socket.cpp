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
        socket->write("Ive changed since you tried me.. lets see if it works again\r\n");
        //this->sendInitialConectionPackage();
        socket->close();
    }
    else{
        qDebug() << "Failed connection :C";
    }
}

void Socket::sendInitialConectionPackage(){
    QString typePackage = "0";
    QString rsrv = "0101";

    QByteArray bytes = typePackage.toUtf8();
    int length = bytes.size(); //Number of bytes
    qDebug() << "Bytes: " << bytes <<" Length is:" << length;

    QByteArray rsrv_bytes = rsrv.toUtf8();
    int rsrv_length = rsrv_bytes.size(); //Number of bytes
    qDebug() << "Bytes: " << rsrv_bytes <<" Length is:" << rsrv_length;

}
