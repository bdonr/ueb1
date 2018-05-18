#include "traegerklasse.h"




glm::vec3 TraegerKlasse::getIntvec() const
{
    return intvec;
}

void TraegerKlasse::setIntvec(const glm::vec3 &value)
{
    intvec = value;
}

int TraegerKlasse::getTab() const
{
    return tab;
}

void TraegerKlasse::setTab(int value)
{
    tab = value;
}

TraegerKlasse::TraegerKlasse()
{
    intvec=glm::vec3(0,0,0);
}

void TraegerKlasse::setX(int x)
{
    intvec.x=x;
}

void TraegerKlasse::setY(int y)
{
    intvec.y=y;
}

void TraegerKlasse::setZ(int z)
{
    intvec.z=z;
}

