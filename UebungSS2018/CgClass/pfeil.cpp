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

void Pfeil::renderO(glm::mat4x4 p)
{
    std::cout<< "pfeil"<<std::endl;
        render->setUniformValue("mycolor",glm::vec4(1.,1.,1.,1.));
    render->render(this->getZylinder(),p);
    render->setUniformValue("mycolor",glm::vec4(1.,1.,1.,1.));
    render->render(this->getKegel(),transform(1));
}

Pfeil::Pfeil(CgBaseRenderer *render)
{
    this->render = render;
    zylinder = MeshFactory::createZylinder(100,100,.0001,false);
    kegel = MeshFactory::createKegel(100,100,.0001,false);
    render->init(this->getKegel());
    render->init(this->getZylinder());
}
glm::mat4x4 Pfeil::transform(int i){
    return glm::mat4x4( glm::vec4(0.01,0,0,0),
                        glm::vec4(0,0.01,0,0),
                        glm::vec4(0,0,.01,0),
                        glm::vec4(0,0,100,.01));
}




