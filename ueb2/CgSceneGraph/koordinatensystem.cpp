#include "koordinatensystem.h"
#include "meshfactory.h"
Koordinatensystem::Koordinatensystem()
{
    std::vector<glm::vec3>vecx;
    std::vector<glm::vec3>vecy;
    std::vector<glm::vec3>vecz;

    vecx.push_back(glm::vec3(0,0,0));
    vecx.push_back(glm::vec3(20,0,0));
    MyPolyline* xachse = MeshFactory::createMyPolyline(glm::vec3(0,0,255),vecx);
    vecy.push_back(glm::vec3(0,0,0));
    vecy.push_back(glm::vec3(0,20,0));
    MyPolyline* yachse = MeshFactory::createMyPolyline(glm::vec3(255,0,0),vecy);


    vecz.push_back(glm::vec3(0,0,0));
    vecz.push_back(glm::vec3(0,0,20));
    MyPolyline* zachse = MeshFactory::createMyPolyline(glm::vec3(255,255,255),vecz);
    polylines.push_back(xachse);
    polylines.push_back(yachse);
    polylines.push_back(zachse);

}
std::vector<MyPolyline*> Koordinatensystem::getPolylines(){
    return polylines;
}

