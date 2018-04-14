#include "meshfactory.h"
#include "Zylinder.h"
#include "kegel.h"

int MeshFactory::all_id=1;
MeshFactory::MeshFactory()
{

}
CgBaseTriangleMesh* MeshFactory::createZylinder(){
    return (CgBaseTriangleMesh*) new Zylinder(++all_id,0.1,-1,180);
}
CgBaseTriangleMesh* MeshFactory::createKegel(){
    return (CgBaseTriangleMesh*) new Kegel(++all_id,0.2,0.3,360);
}
