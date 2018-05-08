#include "meshfactory.h"
#include "Zylinder.h"
#include "kegel.h"
#include "Mypolyline.h"
#include "dreiecke.h"
#include <iostream>

int MeshFactory::all_id=1;
MeshFactory::MeshFactory()
{

}
CgBaseTriangleMesh* MeshFactory::createZylinder(int refine,float hoehe,float radius){
    return (CgBaseTriangleMesh*) new Zylinder(++all_id,radius,hoehe,refine);

}
CgBaseTriangleMesh* MeshFactory::createKegel(int refine,float hoehe,float radius){
    return (CgBaseTriangleMesh*) new Kegel(++all_id,radius,hoehe,refine);
}

MyPolyline* MeshFactory::createMyPolyline(glm::vec3 color,std::vector<glm::vec3> x){
    return new MyPolyline(++all_id,color,x);

}

RotationsKoerper* MeshFactory::createRotationKoerper(int refine){
return new RotationsKoerper(++all_id, refine);
}

Dreiecke * MeshFactory::createDreiecke(std::vector<glm::vec3>x,std::vector<unsigned int>k){
    return new Dreiecke(++all_id,x,k);
}

Kugel * MeshFactory::createKugel(float radius, float hoehe, int refine){
    return new Kugel(++all_id,radius,hoehe, refine);
}


