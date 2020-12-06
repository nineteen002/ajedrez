#include "packages.h"

#include <string>
#include <string.h>
#include <QDebug>

Packages::Packages(int type, QString text)
{
    packMsm = new char[256];
    if (type == 0){
        std::string txt = text.toStdString();
        packMsm[0] = '0';
        packMsm[1] = text.length();
        for (int i = 2; i < (text.length()+2); i++ ){
            packMsm[i] = txt[i-2];
        }
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
