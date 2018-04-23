#ifndef MESHFACTORY_H
#define MESHFACTORY_H
#include <CgBase/CgBaseTriangleMesh.h>
#include <CgBase/CgBasePolyline.h>
#include "Mypolyline.h"
#include "rotationskoerper.h"
class RotationsKoerper;
class MeshFactory
{

private: int id;
    static int all_id;
public:
    static CgBaseTriangleMesh* createZylinder(int refine,float hoehe,float radius);
    static CgBaseTriangleMesh* createKegel(int refine,float hoehe,float radius);
    static MyPolyline* createMyPolyline(glm::vec3 color,std::vector<glm::vec3> x);
    static RotationsKoerper* createRotationKoerper(int refine);

    MeshFactory();

};
#endif // MESHFACTORY_H
