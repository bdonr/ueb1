#include "mats.h"

glm::vec4 Mats::getAmb() const
{
    return mamb;
}

void Mats::setAmb(const glm::vec4 &value)
{
    mamb = value;
}

glm::vec4 Mats::getDef() const
{
    return mdif;
}

void Mats::setDef(const glm::vec4 &value)
{
    mdif = value;
}

glm::vec4 Mats::getSpec() const
{
    return mspec;
}

void Mats::setSpec(const glm::vec4 &value)
{
    mspec = value;
}

double Mats::getScalar() const
{
    return mshine;
}

void Mats::setScalar(double value)
{
    mshine = value;
}

Mats::Mats()
{

}

