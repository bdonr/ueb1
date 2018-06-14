#ifndef VIRTCAM_H
#define VIRTCAM_H

#include <vector>
#include <glm/glm.hpp>


class virtCam
{
public:
    virtCam();

    glm::vec4 worldToCamCoordinates(glm::vec4);



    //Getter, Setter
    glm::vec3 getEye(void) const;
    void setEye(glm::vec3 eye);

    glm::vec3 getCenter(void) const;
    void setCenter(glm::vec3 center);

    glm::vec3 getUp(void) const;
    void setUp(glm::vec3 up);

    int getWindowHeight() const;
    void setWindowHeight(int value);

    int getWindowWidth() const;
    void setWindowWidth(int value);

private:
    glm::vec3 eye;      //Position
    glm::vec3 center;   //Position
    glm::vec3 up;       //Vector

    int windowHeight;
    int windowWidth;
};

#endif // VIRTCAM_H
