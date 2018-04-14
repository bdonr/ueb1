#include "meshfactory.h"
#include "Kegel.h"

int MeshFactory::all_id=1;
MeshFactory::MeshFactory()
{

}
CgBaseTriangleMesh* MeshFactory::createKegel(){
    return (CgBaseTriangleMesh*) new Kegel(++all_id,0.1,-1,180);
}
