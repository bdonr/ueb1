#include "meshfactory.h"
#include "Zylinder.h"
#include "kegel.h"
#include "Mypolyline.h"
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

MyPolyline* MeshFactory::createMyPolyline(std::vector<glm::vec3> x){
        std::cout<<all_id<<" polyline id"<<std::endl;
    return new MyPolyline(++all_id,glm::vec3(255,255,0),x);

}

RotationsKoerper* MeshFactory::createRotationKoerper(int refine){
return new RotationsKoerper(++all_id, refine);
}
