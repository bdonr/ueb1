#include "kamera.h"

glm::mat4 Kamera::getLookAt() const
{
    return lookAt;
}

void Kamera::setLookAt(const glm::mat4 &value)
{
    lookAt = value;
}

glm::mat4 Kamera::getProjection() const
{
    return projection;
}

void Kamera::setProjection(const glm::mat4 &value)
{
    projection = value;
}

glm::vec2 Kamera::getFenster() const
{

}

void Kamera::setFenster(const glm::vec2 &value)
{

}

Kamera::Kamera()
{

}

