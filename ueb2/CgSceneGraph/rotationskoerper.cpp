#include "rotationskoerper.h"
#include "meshfactory.h"
#include <glm/vec3.hpp>
#include <vector>

RotationsKoerper::RotationsKoerper(MyPolyline* poly, int refine):poly(poly), refine(refine)
{

}

RotationsKoerper::RotationsKoerper(int id, int refine):refine(refine), id(id)
{
drehe();
}

std::vector <MyPolyline*> RotationsKoerper::getPolyVec(){
    return this->polyVec;
}

void RotationsKoerper::drehe(){
    int count = 0;
float y = 0;
    for( float y = 0.0;y<360.0+360.0/refine;y=y+(360.0/refine))
    {
        std::vector<glm::vec3> vect;
      /* vect.push_back(glm::vec3(0,0,0));
        vect.push_back(glm::vec3(0.1,0.075,0));
        vect.push_back(glm::vec3(0.2,0,0));*/
        /*
        1,0,0
        0,cosa,-sina
        0,sina,cosa
        */
        vect.push_back(glm::vec3(0,0,0));
        vect.push_back(glm::vec3(0.1,0.5*glm::cos(glm::radians(y+0.075)),0.5*(glm::sin(glm::radians(y+0)))*(-1)));
        vect.push_back(glm::vec3(0.2,0.5*glm::sin(glm::radians(y+0)),0.5*glm::cos(glm::radians(y+0))));
//                                   /krümung x                     /krümung y
        polyVec.push_back(MeshFactory::createMyPolyline(vect));
        polyVec.at(count)->fuelleAuf();
        polyVec.at(count)->fuelleAuf();

    count++;
    }
}

