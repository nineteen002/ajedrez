#include "socket.h"
#include <QDebug>
#include <stdlib.h>
#include <iostream>
#include "chessboard.h"

extern ChessBoard* board;

Socket::Socket(QObject *parent) : QObject(parent)
{
    WSADATA wsaData;
    if(WSAStartup(MAKEWORD(2,2),&wsaData) != 0){
        qDebug() << "Error de inicializacion" ;
        this->error = -1;
    }
}

int Socket::inet_pton(int af, const char *src, char *dst)
{
    switch (af)
    {
    case AF_INET:
        return inet_pton4(src, dst);
    case AF_INET6:
        return inet_pton6(src, dst);
    default:
        return -1;
    }
}

int Socket::inet_pton4(const char *src, char *dst)
{
    uint8_t tmp[NS_INADDRSZ], *tp;
    int saw_digit = 0;
    int octets = 0;
    *(tp = tmp) = 0;
    int ch;
    while ((ch = *src++) != '\0')
    {
        if (ch >= '0' && ch <= '9')
        {
            uint32_t n = *tp * 10 + (ch - '0');
            if (saw_digit && *tp == 0)
                return 0;
            if (n > 255)
                return 0;
            *tp = n;
            if (!saw_digit)
            {
                if (++octets > 4)
                    return 0;
                saw_digit = 1;
            }
        }
        else if (ch == '.' && saw_digit)
        {
            if (octets == 4)
                return 0;
            *++tp = 0;
            saw_digit = 0;
        }
        else
            return 0;
    }
    if (octets < 4)
        return 0;
    memcpy(dst, tmp, NS_INADDRSZ);
    return 1;
}

int Socket::inet_pton6(const char *src, char *dst)
{
    static const char xdigits[] = "0123456789abcdef";
    uint8_t tmp[NS_IN6ADDRSZ];
    uint8_t *tp = (uint8_t*) memset(tmp, '\0', NS_IN6ADDRSZ);
    uint8_t *endp = tp + NS_IN6ADDRSZ;
    uint8_t *colonp = NULL;
    /* Leading :: requires some special handling. */
    if (*src == ':')
    {
        if (*++src != ':')
            return 0;
    }
    const char *curtok = src;
    int saw_xdigit = 0;
    uint32_t val = 0;
    int ch;
    while ((ch = tolower(*src++)) != '\0')
    {
        const char *pch = strchr(xdigits, ch);
        if (pch != NULL)
        {
            val <<= 4;
            val |= (pch - xdigits);
            if (val > 0xffff)
                return 0;
            saw_xdigit = 1;
            continue;
        }
        if (ch == ':')
        {
            curtok = src;
            if (!saw_xdigit)
            {
                if (colonp)
                    return 0;
                colonp = tp;
                continue;
            }
            else if (*src == '\0')
            {
                return 0;
            }
            if (tp + NS_INT16SZ > endp)
                return 0;
            *tp++ = (uint8_t) (val >> 8) & 0xff;
            *tp++ = (uint8_t) val & 0xff;
            saw_xdigit = 0;
            val = 0;
            continue;
        }
        if (ch == '.' && ((tp + NS_INADDRSZ) <= endp) &&
                inet_pton4(curtok, (char*) tp) > 0)
        {
            tp += NS_INADDRSZ;
            saw_xdigit = 0;
            break; /* '\0' was seen by inet_pton4(). */
        }
        return 0;
    }
    if (saw_xdigit)
    {
        if (tp + NS_INT16SZ > endp)
            return 0;
        *tp++ = (uint8_t) (val >> 8) & 0xff;
        *tp++ = (uint8_t) val & 0xff;
    }
    if (colonp != NULL)
    {
        /*
         * Since some memmove()'s erroneously fail to handle
         * overlapping regions, we'll do the shift by hand.
         */
        const int n = tp - colonp;

        if (tp == endp)
            return 0;

        for (int i = 1; i <= n; i++)
        {
            endp[-i] = colonp[n - i];
            colonp[n - i] = 0;
        }
        tp = endp;
    }
    if (tp != endp)
        return 0;

    memcpy(dst, tmp, NS_IN6ADDRSZ);

    return 1;
}

void Socket::processRed(char *buffer)
{
    if (int(buffer[0]) == 1){
        int roomNumber = int(buffer[1]);
        current_team = int(buffer[2]);
        qDebug() << "room number: "<< roomNumber << "team: "<< current_team ;
        board->sayTeam();

        for(int i = 3; i < error; i++){
            buffer[i-3] = buffer[i];
        }
    }    
    if (int(buffer[0]) == 2 ){
        memset((char*)&name_enemy,0, sizeof(name_enemy));
        board->start();
        int _long = int(buffer[1]);
        for  (int i = 2; i < 2+_long; i++){
            name_enemy[i-2] = buffer[i];
        }
    }
    else if (int(buffer[0]) == 4){       
        select_pos = int(buffer[1]);
        mv_pos = int(buffer[2]);
        board->enemyMove(select_pos, mv_pos);
        board->changeTurn();
        board->showTurn();
    }
    else if (int(buffer[0]) == 9){

        int _long = int(buffer[1]);
        char msm[256];
        memset((char*)&msm,0, sizeof(msm));
        for  (int i = 2; i <(2+_long); i++){
            msm[i-2] = buffer[i];
        }
        qDebug() << "Name enemy: "<< name_enemy;
        board->chatMessage(name_enemy, msm);
    }
}

bool Socket::startConnectionWithServer(char* serverName, char* port){
    if (this->doDnsResolution(serverName, port) == true){
        if (this->createServerSocket() == true){
            this->makeNoBlocking();
            return true;
        }
    }
    return false;
}

bool Socket::doDnsResolution(char* serverName, char* port){
    struct addrinfo hints;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    qDebug() << "Name:" << serverName;
    qDebug() << "Port:" << port;

    error = getaddrinfo(serverName, port, &hints, &dnsResults);
    if(error != 0){
        qDebug() << "Error de resolucion DNS";
        return false;
    }
    qDebug() << "Resolucion DNS correcta!!";
    return true;
}

bool Socket::createServerSocket(){
    struct addrinfo *save= dnsResults;
    for(save = dnsResults; dnsResults != nullptr; dnsResults = dnsResults->ai_next){
        //IPV4
        if(dnsResults->ai_family == AF_INET){
            qDebug() << "IPv4";
            createSocket(dnsResults);
        } //IPV6
        else if(dnsResults->ai_family == AF_INET6){
            qDebug() << "IPv6";
            createSocket(dnsResults);
        }
        if (connectSocket() == false){
            return false;
        }
    }
    freeaddrinfo(save);
    return true;
}

void Socket::createSocket(struct addrinfo* dnsResults){
    if((socketConnection = socket(dnsResults->ai_family, SOCK_STREAM, 0)) == INVALID_SOCKET){
        qDebug() << "ERROR: No se pudo crear el socket";
        error = -1;
    }
    qDebug() << "Socket creado correctamente";
}

bool Socket::connectSocket(){
    error = ::connect(socketConnection, dnsResults->ai_addr, dnsResults->ai_addrlen);
    if(error == SOCKET_ERROR){
        qDebug() << "Error de conexion";
        closesocket(socketConnection);
        return false;
    }
    else{
        qDebug() << "Conexion exitosa!!!";
        return true;
    }
}

void Socket::makeNoBlocking(){
    watcher = new QSocketNotifier(socketConnection, QSocketNotifier::Read);
    connect(watcher, SIGNAL(activated(int)),this, SLOT(readFromServer(int)));
}

int Socket::readFromServer(int socketConnection){
    char buffer[1024];
    memset((char*)&buffer,0, sizeof(buffer)); // clean buffer
    error = ::recv(socketConnection, buffer, sizeof(buffer), 0); //negative= errir conectio 0= cerro positive=read bytes
    if(error < 0) {
        //qDebug()  << "ERROR: Conexion cerrada por un error" << socketConnection << endl;
        //::close(socketConnection);
        //delete(watcher);
        return -1;
    } else if(error > 0) {
        qDebug() << "Data recieved:" << buffer << "Bytes resividos: " << error;
        processRed(buffer);
    } else if(error == 0) {
        qDebug()  << "Se cerro la conexion" << socketConnection ;
        ::close(socketConnection);
        delete(watcher);
    }

    memset((char*)&buffer,0, sizeof(buffer));

    return -1;
}

void Socket::sendData(char* buffer){
    //TRY SENDING DATA
    qDebug() << "Sending data";
    qDebug() << buffer ;
    send(socketConnection, buffer, int(strlen(buffer)),0);
}

void Socket::closeSocket()
{
    //::close(socketConnection);
    closesocket(socketConnection);
}
