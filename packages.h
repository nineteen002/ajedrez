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
    char *getPackMsm() const;
    void setPackMsm(char *value);

private:
    char *packMsm;
};

#endif // PACKAGES_H
