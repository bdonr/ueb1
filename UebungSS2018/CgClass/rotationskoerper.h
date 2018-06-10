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
    int hoehe;
    std::vector <MyPolyline*> polyVec;
    std::vector <MyPolyline*> kreisVec;
    glm::vec3 vectorMalMatrix(glm::vec3 vector,std::vector<glm::vec3>matrix);
    std::vector<MyPolyline*> normale;

public:
    std::vector<MyPolyline*> getNormale();
    std::vector <MyPolyline*> getPolyVec();
    std::vector <MyPolyline*> getKeisVec();
    RotationsKoerper(MyPolyline*, int);
    RotationsKoerper(int id, int refine,int hoehe);

    void erstelleKugel();
    void zieheLinieZwischenZweiNachBarSegmenten();
    glm::vec3 mittelPunkt(glm::vec3 a,glm::vec3 b, glm::vec3 c);

    glm::vec3 normalen(glm::vec3 a,glm::vec3 b, glm::vec3 c,glm::vec3 mittelpunkt);
    void erstelleRotationsKoerper();
    void drehe();
};

#endif // ROTATIONSKOERPER_H
