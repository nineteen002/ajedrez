#ifndef PACKAGES_H
#define PACKAGES_H

#include <QString>
#include <QDebug>
#define p_conect 0
#define p_play 2

class Packages
{
public:
    Packages(int type, QString text);
    Packages(int type, int plase_pos, int final_pos);
    char *getPackMsm() const;
    void setPackMsm(char *value);

private:
    char *packMsm;
};

#endif // PACKAGES_H
