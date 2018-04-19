#ifndef MESHFACTORY_H
#define MESHFACTORY_H
#include <CgBase/CgBaseTriangleMesh.h>
#include <CgBase/CgBasePolyline.h>
#include "Mypolyline.h"
class MeshFactory
{

private: int id;
    static int all_id;
public:
    static CgBaseTriangleMesh* createZylinder(int refine);
    static CgBaseTriangleMesh* createKegel(int refine);
    static MyPolyline* createMyPolyline(std::vector<glm::vec3> x);

    MeshFactory();

};
#endif // MESHFACTORY_H
