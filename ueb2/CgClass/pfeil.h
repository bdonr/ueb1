#ifndef PFEIL_H
#define PFEIL_H
#include <CgClass/kegel.h>
#include <CgClass/Zylinder.h>

class Pfeil
{
private: Kegel* kegel;
    Zylinder* zylinder;
public:
    Pfeil();
    Kegel *getKegel() const;
    void setKegel(Kegel *value);
    Zylinder *getZylinder() const;
    void setZylinder(Zylinder *value);
};

#endif // PFEIL_H
