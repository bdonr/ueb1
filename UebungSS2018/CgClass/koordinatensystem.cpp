#include "koordinatensystem.h"
#include "meshfactory.h"
Koordinatensystem::Koordinatensystem(CgBaseRenderer *render,glm::mat4x4 x)
{
    this->render=render;
    this->translation=x;
    Appearance* k = new Appearance();
    k->getMaterial()->setAmb(glm::vec4(1,0,0,0));
    k->getMaterial()->setDef(glm::vec4(.1,.1,.1,1));
    k->getMaterial()->setSpec(glm::vec4(.1,.1,.1,1));
    k->getMaterial()->setScalar(70);

    pfeile.push_back(new Pfeil(render,k));
    Appearance* g = new Appearance();
    g->getMaterial()->setAmb(glm::vec4(0,1,0,1));
    g->getMaterial()->setDef(glm::vec4(.1,.1,.1,1));
    g->getMaterial()->setSpec(glm::vec4(.1,.1,.1,1));
    g->getMaterial()->setScalar(70);
    pfeile.push_back(new Pfeil(render,g));

            Appearance* o = new Appearance();
            o->getMaterial()->setAmb(glm::vec4(0,0,1,1));
            o->getMaterial()->setDef(glm::vec4(.1,.1,.1,1));
            o->getMaterial()->setSpec(glm::vec4(.1,.1,.1,1));
            o->getMaterial()->setScalar(70);
    pfeile.push_back(new Pfeil(render,o));
}


std::vector<Pfeil *> Koordinatensystem::getPfeile() const
{
    return pfeile;
}

void Koordinatensystem::setPfeile(const std::vector<Pfeil *> &value)
{
    pfeile = value;
}

glm::mat4x4 Koordinatensystem::getTranslation() const
{
    return translation;
}

void Koordinatensystem::setTranslation(const glm::mat4x4 &value)
{
    translation = value;
}

glm::mat4x4 Koordinatensystem::rotationX()
{


    return glm::mat4x4(glm::vec4(1,0,0,0),
                       glm::vec4(0,glm::cos(glm::radians(-90.)),glm::sin(glm::radians(-90.)),0),
                       glm::vec4(0,(-1)*glm::sin(glm::radians(-90.0)),glm::cos(glm::radians(-90.0)),0),
                       glm::vec4(0,0,0,1));
}

glm::mat4x4 Koordinatensystem::rotationY()
{
    return glm::mat4x4(glm::vec4(glm::cos(glm::radians(90.)),0,(-1)*glm::sin(glm::radians(90.)),0),
                       glm::vec4(0,1,0,0),
                       glm::vec4(glm::sin(glm::radians(90.)),0,glm::cos(glm::radians(90.)),0),
                       glm::vec4(0,0,0,1));
}

glm::mat4x4 Koordinatensystem::rotationZ()
{
    return glm::mat4x4(glm::vec4(glm::cos(glm::radians(90.)),glm::sin(glm::radians(90.)),0,0),
                       glm::vec4((-1)*glm::sin(glm::radians(90.)),glm::cos(glm::radians(90.)),0,0),
                       glm::vec4(0,0,1,0),
                       glm::vec4(0,0,0,1));
}


void Koordinatensystem::renderO(bool lighton)
{

    pfeile.at(0)->render(getTranslation()*rotationX(),lighton);
    pfeile.at(1)->render(getTranslation()*rotationY(),lighton);
    pfeile.at(2)->render(getTranslation()*rotationZ(),lighton);


}
