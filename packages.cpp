#include "packages.h"

#include <string>
#include <string.h>
#include <QDebug>

Packages::Packages(int type, QString text)
{
    packMsm = new char[256];
    std::string txt = text.toStdString();
    if (type == 0 || type == 9){
        if (type == 0)
            packMsm[0] = '0';
        else
            packMsm[0] = type;
        packMsm[1] = text.length();
        for (int i = 2; i < (text.length()+2); i++ ){
            packMsm[i] = txt[i-2];
        }
    }
}

Packages::Packages(int type , int plase_pos, int final_pos){ //this can send verification of moving
    char tmp_pkg[256];
    packMsm = new char[256];
    memset((char*)&tmp_pkg, 0, sizeof(tmp_pkg)); // clean buffer

    if (type == 3){// Send move
        tmp_pkg[0] = 3;
        tmp_pkg[1] = plase_pos;
        tmp_pkg[2] = final_pos;
    }
    else if (type == 4){
        tmp_pkg[0] = 4;
        tmp_pkg[1] = plase_pos;
    }
    else if (type == 5){// victoria
        tmp_pkg[0] = 5;
        tmp_pkg[1] = plase_pos;
    }
    strncpy(packMsm, tmp_pkg, 3);
}

char *Packages::getPackMsm() const
{
    return packMsm;
}

void Packages::setPackMsm(char *value)
{
    packMsm = value;
}
