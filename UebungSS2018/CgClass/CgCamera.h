#ifndef CGCAMERA_H
#define CGCAMERA_H

#include <vector>
#include <glm/glm.hpp>

class CgCamera
{
public:
    CgCamera(glm::vec3 eye, glm::vec3 center, glm::vec3 up, int windowHeight,int windowWidth);

    //@author Gerrit
    glm::mat4x4 getLookAtMatrix();
    glm::mat4x4 getProjectionMatrix(int projection);
    void matrizenTest();



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


    void print4x4Matrix(glm::mat4x4 &value);

};

#endif // CGCAMERA_H
