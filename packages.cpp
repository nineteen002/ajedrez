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
        qDebug() << "CREATING PACKAGE 3";
        tmp_pkg[0] = 3;
        tmp_pkg[1] = plase_pos;
        tmp_pkg[2] = final_pos;
        qDebug() << "Type: " << int(tmp_pkg[0]) << ", pos: " << int(tmp_pkg[1]) << "moved to: " << int(tmp_pkg[2]);
    }
    else if (type == 4){
        tmp_pkg[0] = 4;
        tmp_pkg[1] = plase_pos;
    }
    else if (type == 5){// rematch
        tmp_pkg[0] = 5;
        tmp_pkg[1] = plase_pos; // 0 = no 1 =si
    }
    strncpy(packMsm, tmp_pkg, 3);
    qDebug() << "Type: " << int(packMsm[0]) << ", pos: " << int(packMsm[1]) << "moved to: " << int(packMsm[2]);
}

char *Packages::getPackMsm() const
{
    return packMsm;
}

void Packages::setPackMsm(char *value)
{
    packMsm = value;
}
