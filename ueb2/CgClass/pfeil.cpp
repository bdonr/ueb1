#include "pfeil.h"

Kegel *Pfeil::getKegel() const
{
    return kegel;
}

void Pfeil::setKegel(Kegel *value)
{
    kegel = value;
}

Zylinder *Pfeil::getZylinder() const
{
    return zylinder;
}

void Pfeil::setZylinder(Zylinder *value)
{
    zylinder = value;
}

Pfeil::Pfeil()
{
    zylinder = MeshFactory::createZylinder(100,1,1,false);
    kegel = MeshFactory::createKegel(100,1,1,false);
}

