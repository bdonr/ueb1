#ifndef KOORDINATENSYSTEM_H
#define KOORDINATENSYSTEM_H

#include <vector>
#include "Mypolyline.h"
#include "pfeil.h"
class Koordinatensystem
{

private:
    std::vector<Pfeil*> polylines;

public:
    Koordinatensystem();
    std::vector<Pfeil*> getPolylines();
};

#endif // KOORDINATENSYSTEM_H
