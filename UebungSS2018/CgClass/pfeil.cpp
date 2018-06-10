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

void Pfeil::render(glm::mat4x4 p)
{
    renderer->setUniformValue("mycolor",appear->getVierDcolor());
    renderer->render(this->getZylinder(),p);
    renderer->setUniformValue("mycolor",appear->getVierDcolor());
    renderer->render(this->getKegel(),p*transform());
}

void Pfeil::render()
{
    renderer->setUniformValue("mycolor",appear->getVierDcolor());
    renderer->render(this->getZylinder(),xyz);
    renderer->setUniformValue("mycolor",appear->getVierDcolor());
    renderer->render(this->getKegel(),xyz*transform());
}

Pfeil::Pfeil(CgBaseRenderer *render,Appearance* appear)
{
    this->appear=appear;
    this->renderer = render;
    zylinder = MeshFactory::createZylinder(100,100,.0001,false);
    kegel = MeshFactory::createKegel(100,100,.0001,false);
    render->init(this->getKegel());
    render->init(this->getZylinder());
}

Pfeil::Pfeil(CgBaseRenderer *renderer, Appearance *appear, glm::mat4x4 mat):renderer(renderer),appear(appear),xyz(mat)
{
    zylinder = MeshFactory::createZylinder(100,100,.0001,false);
    kegel = MeshFactory::createKegel(100,100,.0001,false);
    renderer->init(this->getKegel());
    renderer->init(this->getZylinder());
}


glm::mat4x4 Pfeil::transform(){
    return glm::mat4x4( glm::vec4(0.01,0,0,0),
                        glm::vec4(0,0.01,0,0),
                        glm::vec4(0,0,.01,0),
                        glm::vec4(0,0,100,.01));
}




