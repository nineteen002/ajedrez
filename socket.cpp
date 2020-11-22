#include "socket.h"

Socket::Socket(QObject *parent) : QObject(parent)
{
    WSADATA wsaData;

    if(WSAStartup(MAKEWORD(2,2),&wsaData) != 0){
        qDebug() << "Error de inicializacion" << endl;
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

void Socket::startConnectionWithServer(char* serverName, char* port){
    this->doDnsResolution(serverName, port);
    this->createServerSocket();
}

void Socket::doDnsResolution(char* serverName, char* port){
    struct addrinfo hints;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    qDebug() << "Name:" << serverName;
    qDebug() << "Port:" << port;

    error = getaddrinfo(serverName, port, &hints, &dnsResults);
    if(error != 0){
        qDebug() << "Error de resolucion DNS";
    }
    qDebug() << "Resolucion DNS correcta!!";
}

void Socket::createServerSocket(){
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
        connect();
    }
    freeaddrinfo(save);
}
/*
 wchar_t ipstringbuffer[46];

this->socketaddr_ip = (LPSOCKADDR) dnsResults->ai_addr;
// The buffer length is changed by each call to WSAAddresstoString
// So we need to set it for each iteration through the loop for safety
DWORD ipbufferlength = 46;
int iRetval = WSAAddressToString(socketaddr_ip, (DWORD) dnsResults->ai_addrlen, NULL,
                             ipstringbuffer, &ipbufferlength);
if (iRetval)
    printf("WSAAddressToString failed with %u\n", WSAGetLastError() );
else
    printf("\tIPv6 address %s\n", ipstringbuffer);
*/

void Socket::createSocket(struct addrinfo* dnsResults){
    if((clientSocket = socket(dnsResults->ai_family, SOCK_STREAM, 0)) == INVALID_SOCKET){
        qDebug() << "ERROR: No se pudo crear el socket";
        error = -1;
    }

    qDebug() << "Socket creado correctamente";
}

void Socket::connect(){
    error = ::connect(clientSocket, dnsResults->ai_addr, dnsResults->ai_addrlen);
    if(error == SOCKET_ERROR){
        qDebug() << "Error de conexion";
        closesocket(clientSocket);
    }
    else{
        qDebug() << "Conexion exitosa!!!";
    }
}

void Socket::sendInitialConectionPackage(){
    QString package = "0";

    QByteArray bytes("hello", 1);
    int length = bytes.size(); //Number of bytes
    qDebug() << "Bytes: " << bytes <<" Length is:" << length;
}
