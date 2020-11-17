#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include <QTcpSocket>

class Socket : public QObject
{
    Q_OBJECT
public:
    explicit Socket(QObject *parent = nullptr);

    void connect();
    void sendInitialConectionPackage();

signals:
private:
    QTcpSocket *socket;
};

#endif // SOCKET_H
