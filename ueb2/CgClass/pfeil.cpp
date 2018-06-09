#include "pfeil.h"

Kegel *Pfeil::getKegel() const
{
    return kegel;
}

void Pfeil::setKegel(Kegel *value)
{
    kegel = value;
}

Zylinder *Pfeil::getZylinder() const
{
    return zylinder;
}

void Pfeil::setZylinder(Zylinder *value)
{
    zylinder = value;
}

Pfeil::Pfeil()
{
    zylinder = MeshFactory::createZylinder(100,1,1,false);
    kegel = MeshFactory::createKegel(100,1,1,false);
}
glm::mat4x4 Pfeil::transform(int i){
    return glm::mat4x4( glm::vec4(1,0,0,0),
                        glm::vec4(0,1,0,0),
                        glm::vec4(0,0,1,0),
                        glm::vec4(i+1,0,0,0));
}
void Pfeil::render(CgBaseRenderer *render, glm::mat4x4 p)
{
        std::cout<< "pfeil"<<std::endl;
        render->init(this->getKegel());
        render->init(this->getZylinder());
        render->render(this->getZylinder(),p);
        render->render(this->getKegel(),transform(1));
}




