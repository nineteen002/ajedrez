#include "packages.h"

#include <string>

Packages::Packages(int type, QString text)
{
    if (type == 0){
        std::string packag = std::to_string(type) + "." + std::to_string(text.toStdString().length()) + "." + text.toStdString() + "";

        packMsm = new char[packag.size()+1];

        strcpy(packMsm, packag.c_str());
        qDebug() << "Tamaño de la cadena" <<strlen(packMsm) << "cadena: "<< packMsm;
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
