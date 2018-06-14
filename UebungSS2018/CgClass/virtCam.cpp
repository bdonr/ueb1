#include "virtCam.h"

virtCam::virtCam()
{

}

glm::vec3 virtCam::getEye(void) const
{
    return eye;
}
void virtCam::setEye(glm::vec3 value)
{
    eye = value;
}

glm::vec3 virtCam::getCenter(void) const
{
    return center;
}
void virtCam::setCenter(glm::vec3 value)
{
    center = value;
}

glm::vec3 virtCam::getUp(void) const
{
    return up;
}

void virtCam::setUp(glm::vec3 value){
    up = value;
}

int virtCam::getWindowHeight() const
{
    return windowHeight;
}

void virtCam::setWindowHeight(int value)
{
    windowHeight = value;
}

int virtCam::getWindowWidth() const
{
    return windowWidth;
}

void virtCam::setWindowWidth(int value)
{
    windowWidth = value;
}

