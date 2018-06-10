#ifndef KAMERA_H
#define KAMERA_H
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "vector"

class Kamera
{
private:
    glm::mat4 projection;
    glm::mat4 lookAt;
    glm::vec2 fenster;
    glm::vec3 eye;
    glm::vec3 v;
    glm::vec3 u;
    glm::vec3 w;
    glm::vec3 center;
    float countQ;
public:
    Kamera();
    glm::mat4 getLookAt() const;
    void setLookAt(const glm::mat4 &value);
    glm::mat4 getProjection() const;
    void setProjection(const glm::mat4 &value);
    glm::vec2 getFenster() const;
    void setFenster(const glm::vec2 &value);
    glm::mat4 frustrum(float left, float right, float bottom,float top, float near, float far);
    glm::mat4 perspective(float alpha, float aspect,float near, float far);
    void flyPLUS(float x);
    void flyMINUS(float x);
    void strafePLUS(float x);
    void strafeMINUS(float x);
    void towardPLUS(float x);
    void towardMINUS(float x);

    glm::mat4 calculateNew();
    //void rotate();
    void rotatePlus();
    void rotateMinus();
};

#endif // KAMERA_H
