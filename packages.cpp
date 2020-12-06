#include "packages.h"

#include <string>
#include <string.h>
#include <QDebug>

Packages::Packages(int type, QString text)
{
    if (type == 0){
        packMsm = new char[256];

        std::string txt = text.toStdString();
        qDebug() << packMsm;
        packMsm[0] = '0';
        qDebug() << int(packMsm[0]);
        packMsm[1] = text.length();
        qDebug() << int(packMsm[1]);
        for (int i = 2; i < (text.length()+2); i++ ){
            packMsm[i] = txt[i-2];
            qDebug() << packMsm[i];
        }
        qDebug() << packMsm;
//        std::string packag = std::to_string(type)  + std::to_string(text.toStdString().length()) + text.toStdString() + "";

//        packMsm = new char[packag.size()+1];

//        strcpy(packMsm, packag.c_str());
//        qDebug() << "Tamaño de la cadena" <<strlen(packMsm) << "cadena: "<< packMsm;
    }
    else if (type == 1){

    }
    else if (type == 2){

    }
    else if (type == 3){

    }
}

char *Packages::getPackMsm() const
{
    return packMsm;
}

void Packages::setPackMsm(char *value)
{
    packMsm = value;
}
