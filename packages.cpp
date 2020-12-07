#include "packages.h"

#include <string>
#include <string.h>
#include <QDebug>

Packages::Packages(int type, QString text)
{
    packMsm = new char[256];
    std::string txt = text.toStdString();
    if (type == 0){
        packMsm[0] = '0';
        packMsm[1] = text.length();
        for (int i = 2; i < (text.length()+2); i++ ){
            packMsm[i] = txt[i-2];
        }
    }
    else if (type == 9){
        packMsm[0] = 9;
        packMsm[1] = 1;
        packMsm[2] = text.length();
        for (int i = 3; i < (text.length()+3); i++ ){
            packMsm[i] = txt[i-3];
        }
    }
}

Packages::Packages(int type , int plase_pos, int final_pos){ //this can send verification of moving
    packMsm = new char[256];
    if (type == 3){// Send move
        packMsm[0] = 3;
        packMsm[1] = plase_pos;
        packMsm[2] = final_pos;
    }
    else if (type == 4){
        packMsm[0] = 4;
        packMsm[1] = plase_pos;
    }
    else if (type == 5){// victoria
        packMsm[0] = 5;
        packMsm[1] = plase_pos;
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
