#include "meshfactory.h"
#include "Zylinder.h"
#include "kegel.h"
#include "Mypolyline.h"
int MeshFactory::all_id=1;
MeshFactory::MeshFactory()
{

}
CgBaseTriangleMesh* MeshFactory::createZylinder(){
    return (CgBaseTriangleMesh*) new Zylinder(++all_id,0.1,-1,20);
}
CgBaseTriangleMesh* MeshFactory::createKegel(int refine){
    return (CgBaseTriangleMesh*) new Kegel(++all_id,0.2,0.3,refine);
}

MyPolyline* MeshFactory::createMyPolyline(std::vector<glm::vec3> x){
    return new MyPolyline(++all_id,glm::vec3(255,255,0),x);
}

