#ifndef MESHFACTORY_H
#define MESHFACTORY_H
#include <CgBase/CgBaseTriangleMesh.h>

class MeshFactory
{

private: int id;
    static int all_id;
public:
    static CgBaseTriangleMesh* createZylinder();
    static CgBaseTriangleMesh* createKegel();
    MeshFactory();
};

#endif // MESHFACTORY_H
