#ifndef KAMERA_H
#define KAMERA_H
#include "glm/glm.hpp"
#include "vector"

class Kamera
{
private:
    glm::mat4 projection;
    glm::mat4 lookAt;
    glm::vec2 fenster;
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

};

#endif // KAMERA_H
