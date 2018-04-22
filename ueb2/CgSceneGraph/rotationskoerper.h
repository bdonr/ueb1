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
    std::vector <MyPolyline*> kreisVec;
    glm::vec3 vectorMalMatrix(glm::vec3 vector,std::vector<glm::vec3>matrix);

public:
    std::vector <MyPolyline*> getPolyVec();
    std::vector <MyPolyline*> getKeisVec();
    RotationsKoerper(MyPolyline*, int);
    RotationsKoerper(int id, int refine);

    void drehe();
    void zieheLinieZwischenZweiNachBarSegmenten();

};

#endif // ROTATIONSKOERPER_H
