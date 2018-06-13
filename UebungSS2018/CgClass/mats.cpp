#include "mats.h"

glm::vec4 Mats::getAmb() const
{
    return amb;
}

void Mats::setAmb(const glm::vec4 &value)
{
    amb = value;
}

glm::vec4 Mats::getDef() const
{
    return def;
}

void Mats::setDef(const glm::vec4 &value)
{
    def = value;
}

glm::vec4 Mats::getSpec() const
{
    return spec;
}

void Mats::setSpec(const glm::vec4 &value)
{
    spec = value;
}

double Mats::getScalar() const
{
    return scalar;
}

void Mats::setScalar(double value)
{
    scalar = value;
}

Mats::Mats()
{

}

