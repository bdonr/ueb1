#include "appearance.h"

glm::vec3 Appearance::getMats() const
{
    return mats;
}

void Appearance::setMats(const glm::vec3 &value)
{
    mats = value;
}

glm::vec3 Appearance::getColor() const
{
    return color;
}

void Appearance::setColor(const glm::vec3 &value)
{
    color = value;
}

Appearance::Appearance()
{

}

