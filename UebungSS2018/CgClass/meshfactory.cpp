#include "CgClass/meshfactory.h"
#include "CgClass/Zylinder.h"
#include "CgClass/kegel.h"
#include "CgClass/Mypolyline.h"
#include "CgClass/dreiecke.h"
#include <iostream>



MeshFactory::MeshFactory()
{

}
int MeshFactory::all_id=1;

Wuerfel *MeshFactory::createWuerfel(glm::vec3 colors)
{
    return new Wuerfel(++all_id,colors);
}

Zylinder* MeshFactory::createZylinder(int refine,float hoehe,float radius,bool berechnenormale){
    return new Zylinder(++all_id,radius,hoehe,refine,berechnenormale);

}
Kegel* MeshFactory::createKegel(int refine,float hoehe,float radius,bool berechnenormale){
    return new Kegel(++all_id,radius,hoehe,refine,berechnenormale);
}

MyPolyline* MeshFactory::createMyPolyline(glm::vec3 color,std::vector<glm::vec3> x){
    return new MyPolyline(++all_id,color,x);

}

RotationsKoerper* MeshFactory::createRotationKoerper(int refine,int hoehe,bool showline,bool shownormals){
return new RotationsKoerper(++all_id, refine,hoehe,showline,shownormals);
}

Dreiecke * MeshFactory::createDreiecke(std::vector<glm::vec3>x,std::vector<unsigned int>k){
    return new Dreiecke(++all_id,x,k);
}

Kugel * MeshFactory::createKugel(float radius, float hoehe, int refine){
    return new Kugel(++all_id,radius,hoehe, refine);
}



