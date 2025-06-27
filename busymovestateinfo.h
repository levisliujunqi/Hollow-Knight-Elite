#ifndef BUSYMOVESTATEINFO_H
#define BUSYMOVESTATEINFO_H

#include "busystateinfo.h"

class busymovestateinfo : public busystateinfo
{
public:
    busymovestateinfo(int nowframeid,double movev);
    double movev;
};

#endif // BUSYMOVESTATEINFO_H
