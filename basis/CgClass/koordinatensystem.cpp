#include "koordinatensystem.h"
#include "meshfactory.h"
Koordinatensystem::Koordinatensystem(CgBaseRenderer *render,glm::mat4x4 x)
{
    this->render=render;
    this->translation=x;
    pfeile.push_back(new Pfeil(render));
    pfeile.push_back(new Pfeil(render));
    pfeile.push_back(new Pfeil(render));
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
                       glm::vec4(0,glm::cos(glm::radians(90.0)),glm::sin(glm::radians(90.0)),0),
                       glm::vec4(0,(-1)*glm::sin(glm::radians(90.0)),glm::cos(glm::radians(90.0)),0),
                       glm::vec4(0,0,0,1));
}

glm::mat4x4 Koordinatensystem::rotationY()
{
    return glm::mat4x4(glm::vec4(glm::cos(glm::radians(90.0)),0,(-1)*glm::sin(glm::radians(90.0)),0),
                       glm::vec4(0,1,0,0),
                       glm::vec4(glm::sin(glm::radians(90.0)),0,glm::cos(glm::radians(90.0)),0),
                       glm::vec4(0,0,0,1));
}

glm::mat4x4 Koordinatensystem::rotationZ()
{
    return glm::mat4x4(glm::vec4(glm::cos(glm::radians(90.0)),glm::sin(glm::radians(90.0)),0,0),
                       glm::vec4((-1)*glm::sin(glm::radians(90.0)),glm::cos(glm::radians(90.0)),0,0),
                       glm::vec4(0,0,1,0),
                       glm::vec4(0,0,0,1));
}


void Koordinatensystem::renderO()
{

    pfeile.at(0)->renderO(getTranslation()*rotationX());
    pfeile.at(1)->renderO(getTranslation()*rotationY());
    pfeile.at(2)->renderO(getTranslation()*rotationZ());
}
