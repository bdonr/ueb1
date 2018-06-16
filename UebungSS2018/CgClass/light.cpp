#include "light.h"



glm::vec3 Light::getSource() const
{
    return source;
}

void Light::setSource(const glm::vec3 &value)
{
    source = value;
}

glm::vec4 Light::getAdif() const
{
    return adif;
}

void Light::setAdif(const glm::vec4 &value)
{
    adif = value;
}

glm::vec4 Light::getAamb() const
{
    return aamb;
}

void Light::setAamb(const glm::vec4 &value)
{
    aamb = value;
}

glm::vec4 Light::getAspec() const
{
    return aspec;
}

void Light::setAspec(const glm::vec4 &value)
{
    aspec = value;
}

glm::vec3 Light::getAdir() const
{
    return adir;
}

void Light::setAdir(const glm::vec3 &value)
{
    adir = value;
}

Light::Light()
{

}

