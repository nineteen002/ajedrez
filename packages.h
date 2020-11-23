#ifndef PACKAGES_H
#define PACKAGES_H

#include <QString>
#include <QDebug>

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
