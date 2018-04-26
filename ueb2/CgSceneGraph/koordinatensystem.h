#ifndef KOORDINATENSYSTEM_H
#define KOORDINATENSYSTEM_H

#include <vector>
#include "Mypolyline.h"
class Koordinatensystem
{

private:
    std::vector<MyPolyline*> polylines;

public:
    Koordinatensystem();
    std::vector<MyPolyline*> getPolylines();
};

#endif // KOORDINATENSYSTEM_H
