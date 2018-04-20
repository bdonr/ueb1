#ifndef ROTATIONSKOERPER_H
#define ROTATIONSKOERPER_H
#include "Mypolyline.h"
#include "meshfactory.h"
class RotationsKoerper
{
private:
    MyPolyline* poly;
    int refine;
    int id;
    std::vector <MyPolyline*> polyVec;

public:
    std::vector <MyPolyline*> getPolyVec();
    RotationsKoerper(MyPolyline*, int);
    RotationsKoerper(int id, int refine);
    void drehe();
};

#endif // ROTATIONSKOERPER_H
