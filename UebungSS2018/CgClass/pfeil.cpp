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

void Pfeil::setMaterialZylinder()
{
    if(lighton){
    renderer->setUniformValue("material.mamb",getZylinder()->getAppear()->getMaterial()->getAmb());
    renderer->setUniformValue("material.mdif",getZylinder()->getAppear()->getMaterial()->getDef());
    renderer->setUniformValue("material.mspec",getZylinder()->getAppear()->getMaterial()->getSpec());
    renderer->setUniformValue("material.mshine",getZylinder()->getAppear()->getMaterial()->getScalar());
    }
    else{
        renderer->setUniformValue("rgb",getZylinder()->getAppear()->getMaterial()->getAmb());
    }
}
void Pfeil::setMaterialKegel()
{
    if(lighton){
    renderer->setUniformValue("material.mamb",getKegel()->getAppear()->getMaterial()->getAmb());
    renderer->setUniformValue("material.mdif",getKegel()->getAppear()->getMaterial()->getDef());
    renderer->setUniformValue("material.mspec",getKegel()->getAppear()->getMaterial()->getSpec());
    renderer->setUniformValue("material.mshine",getKegel()->getAppear()->getMaterial()->getScalar());
    }
    else{
        renderer->setUniformValue("rgb",getKegel()->getAppear()->getMaterial()->getAmb());
    }

}
void Pfeil::render(glm::mat4x4 p, bool lighton)
{
    this->lighton=lighton;
    setMaterialKegel();
    renderer->render(this->getKegel(),p*transform());
    setMaterialZylinder();
    renderer->render(this->getZylinder(),p*xyz);
}


Pfeil::Pfeil(CgBaseRenderer *renderer, Appearance *appear):renderer(renderer)
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




