#ifndef SOCKET_H
#define SOCKET_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#include <winsock2.h>
#include <winsock.h>
#include <ws2tcpip.h>

#include <QObject>
#include <QTcpSocket>

#define NS_INADDRSZ  4
#define NS_IN6ADDRSZ 16
#define NS_INT16SZ   2

class Socket : public QObject
{
    Q_OBJECT
public:
    explicit Socket(QObject *parent = nullptr);

    int error;
    bool isIpv4, isIpv6;
    void createSocket(struct addrinfo*);

    void startConnectionWithServer(char* serverName, char* port);
    void doDnsResolution(char* serverName, char* port);
    void createServerSocket();

    void connect();
    void sendInitialConectionPackage();

    int inet_pton(int af, const char *src, char *dst);
    int inet_pton4(const char *src, char *dst);
    int inet_pton6(const char *src, char *dst);

signals:
private:
    SOCKET clientSocket;
    struct addrinfo *dnsResults;
    struct sockaddr *server;

};

#endif // SOCKET_H
