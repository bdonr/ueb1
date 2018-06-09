#include "koordinatensystem.h"
#include "meshfactory.h"
Koordinatensystem::Koordinatensystem()
{
    pfeile.push_back(new Pfeil());
    pfeile.push_back(new Pfeil());
    pfeile.push_back(new Pfeil());
}

void Koordinatensystem::render(CgBaseRenderer *render)
{
        pfeile.at(0)->render(render,rotationX());
        pfeile.at(1)->render(render,rotationY());
        pfeile.at(2)->render(render,rotationZ());
}

std::vector<Pfeil *> Koordinatensystem::getPfeile() const
{
    return pfeile;
}

void Koordinatensystem::setPfeile(const std::vector<Pfeil *> &value)
{
    pfeile = value;
}

glm::mat4x4 Koordinatensystem::rotationX()
{


    return glm::mat4x4(glm::vec4(1,0,0,0),
                       glm::vec4(0,glm::cos(glm::radians(90)),glm::sin(glm::radians(90)),0),
                       glm::vec4(0,(-1)*glm::sin(glm::radians(90)),glm::cos(glm::radians(90)),0),
                       glm::vec4(0,0,0,1));
}

glm::mat4x4 Koordinatensystem::rotationY()
{
    return glm::mat4x4(glm::vec4(glm::cos(glm::radians(90)),0,(-1)*glm::sin(glm::radians(90)),0),
                       glm::vec4(0,1,0,0),
                       glm::vec4(glm::sin(glm::radians(90)),0,glm::cos(glm::radians(90)),0),
                       glm::vec4(0,0,0,1));
}

glm::mat4x4 Koordinatensystem::rotationZ()
{
    return glm::mat4x4(glm::vec4(glm::cos(glm::radians(90)),glm::sin(glm::radians(90)),0,0),
                       glm::vec4((-1)*glm::sin(glm::radians(90)),glm::cos(glm::radians(90)),0,0),
                       glm::vec4(0,0,1,0),
                       glm::vec4(0,0,0,1));
}
