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

void Pfeil::render(glm::mat4x4 transformation,bool lighton)
{

    if(lighton){
        renderer->setUniformValue("material.mamb",getZylinder()->getAppear()->getMaterial()->getAmb());
        renderer->setUniformValue("material.mdif",getZylinder()->getAppear()->getMaterial()->getDef());
        renderer->setUniformValue("material.mspec",getZylinder()->getAppear()->getMaterial()->getSpec());
        renderer->setUniformValue("material.mshine",getZylinder()->getAppear()->getMaterial()->getScalar());
    }else{
        renderer->setUniformValue("rgb",getZylinder()->getAppear()->getMaterial()->getAmb());
    }
    renderer->render(this->getZylinder(),transformation);
    if(lighton){
        renderer->setUniformValue("material.mamb",getKegel()->getAppear()->getMaterial()->getAmb());
        renderer->setUniformValue("material.mdif",getKegel()->getAppear()->getMaterial()->getDef());
        renderer->setUniformValue("material.mspec",getKegel()->getAppear()->getMaterial()->getSpec());
        renderer->setUniformValue("material.mshine",getKegel()->getAppear()->getMaterial()->getScalar());
    }
    else{
        renderer->setUniformValue("rgb",getKegel()->getAppear()->getMaterial()->getAmb());
    }
    renderer->render(this->getKegel(),transformation*transform());

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
    return glm::mat4x4( glm::vec4(01,0,0,0),
                        glm::vec4(0,1,0,0),
                        glm::vec4(0,0,1,0),
                        glm::vec4(0,0,0,1));
}




