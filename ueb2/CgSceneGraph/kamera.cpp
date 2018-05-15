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

glm::mat4 Kamera::perspective(float alpha, float aspect, float near, float far)
{
    return frustrum(
                -near * glm::tan(glm::radians(alpha*aspect/2)),
                 near * glm::tan(glm::radians(alpha*aspect/2)),
                 -near * glm::tan(glm::radians(alpha/2)),
                  near * glm::tan(glm::radians(alpha/2)),near,far);
}

Kamera::Kamera()
{

}

glm::mat4 Kamera::frustrum(float left, float right, float bottom,float top, float near, float far)
{
    return glm::mat4(glm::vec4(((2*near)/(right-left)),0,0,0),
                                glm::vec4(0,((2*near)/(top-bottom)),0,0),
                                glm::vec4(((right+left)/(right-left)),((top+bottom)/(top-bottom)),((-1)*((far+near)/(far-near))),-1),
                                glm::vec4(0,0,((-1)*((2*far*near)/(far-near))),0));
}

