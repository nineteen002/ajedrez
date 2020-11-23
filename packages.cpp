#include "packages.h"

#include <string>

Packages::Packages(int type, QString text)
{
    if (type == 0){
        std::string packag = std::to_string(type) + std::to_string(text.toStdString().length()) + text.toStdString();
        strcpy(packMsm, packag.c_str());
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
