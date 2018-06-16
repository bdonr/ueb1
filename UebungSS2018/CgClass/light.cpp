#include "light.h"



glm::vec3 Light::getSource() const
{
    return source;
}

void Light::setSource(const glm::vec3 &value)
{
    source = value;
}


glm::vec4 Light::getLdif() const
{
    return ldif;
}

void Light::setLdif(const glm::vec4 &value)
{
    ldif = value;
}

glm::vec4 Light::getLamp() const
{
    return lamp;
}

void Light::setLamp(const glm::vec4 &value)
{
    lamp = value;
}

glm::vec4 Light::getLspec() const
{
    return lspec;
}

void Light::setLspec(const glm::vec4 &value)
{
    lspec = value;
}

glm::vec3 Light::getLDir() const
{
    return lDir;
}

void Light::setLDir(const glm::vec3 &value)
{
    lDir = value;
}

float Light::getShine() const
{
    return shine;
}

void Light::setShine(float value)
{
    shine = value;
}




Light::Light()
{

}

