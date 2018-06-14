#include "light.h"

float Light::getItensity() const
{
    return itensity;
}

void Light::setItensity(float value)
{
    itensity = value;
}

glm::vec4 Light::getLightcolor() const
{
    return lightcolor;
}

void Light::setLightcolor(const glm::vec4 &value)
{
    lightcolor = value;
}

glm::vec3 Light::getSource() const
{
    return source;
}

void Light::setSource(const glm::vec3 &value)
{
    source = value;
}

Light::Light()
{

}

