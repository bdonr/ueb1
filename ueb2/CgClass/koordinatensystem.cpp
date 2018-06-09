#include "koordinatensystem.h"
#include "meshfactory.h"
Koordinatensystem::Koordinatensystem()
{
    polylines.push_back(new Pfeil());
}
std::vector<Pfeil *> Koordinatensystem::getPolylines(){
    return polylines;
}

