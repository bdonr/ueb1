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
    render->setUniformValue("mycolor",appear->getVierDcolor());
    render->render(this->getZylinder(),p);
    render->setUniformValue("mycolor",appear->getVierDcolor());
    render->render(this->getKegel(),transform());
}

Pfeil::Pfeil(CgBaseRenderer *render,Appearance* appear)
{
    this->appear=appear;
    this->render = render;
    zylinder = MeshFactory::createZylinder(100,100,.0001,false);
    kegel = MeshFactory::createKegel(100,100,.0001,false);
    render->init(this->getKegel());
    render->init(this->getZylinder());
}
glm::mat4x4 Pfeil::transform(){
    return glm::mat4x4( glm::vec4(0.01,0,0,0),
                        glm::vec4(0,0.01,0,0),
                        glm::vec4(0,0,.01,0),
                        glm::vec4(0,0,100,.01));
}




