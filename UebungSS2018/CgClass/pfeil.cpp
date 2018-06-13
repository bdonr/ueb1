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

    renderer->setUniformValue("amb",getKegel()->getAppear()->getMaterial()->getAmb());
    renderer->setUniformValue("def",getKegel()->getAppear()->getMaterial()->getDef());
    renderer->setUniformValue("spec",getKegel()->getAppear()->getMaterial()->getSpec());
    renderer->setUniformValue("scalar",getKegel()->getAppear()->getMaterial()->getScalar());
    renderer->render(this->getKegel(),p*transform());

    renderer->setUniformValue("amb",getZylinder()->getAppear()->getMaterial()->getAmb());
    renderer->setUniformValue("def",getZylinder()->getAppear()->getMaterial()->getDef());
    renderer->setUniformValue("spec",getZylinder()->getAppear()->getMaterial()->getSpec());
    renderer->setUniformValue("scalar",getZylinder()->getAppear()->getMaterial()->getScalar());
    renderer->render(this->getZylinder(),p*xyz);
}

void Pfeil::render()
{
    renderer->setUniformValue("amb",getKegel()->getAppear()->getMaterial()->getAmb());
    renderer->setUniformValue("def",getKegel()->getAppear()->getMaterial()->getDef());
    renderer->setUniformValue("spec",getKegel()->getAppear()->getMaterial()->getSpec());
    renderer->setUniformValue("scalar",getKegel()->getAppear()->getMaterial()->getScalar());
    renderer->render(this->getKegel(),xyz*transform());

    renderer->setUniformValue("amb",getZylinder()->getAppear()->getMaterial()->getAmb());
    renderer->setUniformValue("def",getZylinder()->getAppear()->getMaterial()->getDef());
    renderer->setUniformValue("spec",getZylinder()->getAppear()->getMaterial()->getSpec());
    renderer->setUniformValue("scalar",getZylinder()->getAppear()->getMaterial()->getScalar());
    renderer->render(this->getZylinder(),xyz);
}

Pfeil::Pfeil(CgBaseRenderer *render,Appearance* appear)
{

    this->renderer = render;
    zylinder = MeshFactory::createZylinder(100,100,.0001,false);
    zylinder->setAppear(appear);
    kegel = MeshFactory::createKegel(100,100,.0001,false);
    kegel->setAppear(appear);
    render->init(this->getKegel());
    render->init(this->getZylinder());
}

Pfeil::Pfeil(CgBaseRenderer *renderer, Appearance *appear, glm::mat4x4 mat):renderer(renderer),xyz(mat)
{
    zylinder = MeshFactory::createZylinder(100,100,.0001,false);
    kegel = MeshFactory::createKegel(100,100,.0001,false);
    zylinder->setAppear(appear);
    kegel->setAppear(appear);
    renderer->init(this->getKegel());
    renderer->init(this->getZylinder());
}



glm::mat4x4 Pfeil::transform(){
    return glm::mat4x4( glm::vec4(0.01,0,0,0),
                        glm::vec4(0,0.01,0,0),
                        glm::vec4(0,0,.01,0),
                        glm::vec4(0,0,100,.01));
}




