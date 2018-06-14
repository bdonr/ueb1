#ifndef LIGHT_H
#define LIGHT_H

#include "glm/common.hpp"
class Light
{

    /**
uniform vec4 mamb;
uniform vec4 mdif;
uniform vec4 mspec;
uniform float mshine;


uniform vec4 lcolor;


uniform vec4 ldif;
uniform vec4 lamb;
uniform vec4 lspec;
uniform vec3 lDir;*/

private : glm::vec3 source;
    glm::vec4 ldif;
    glm::vec4 lamp;
    glm::vec4 lspec;
    glm::vec3 lDir;
    float shine;
public:
    Light();

    glm::vec3 getSource() const;
    void setSource(const glm::vec3 &value);
    glm::vec4 getLdif() const;
    void setLdif(const glm::vec4 &value);
    glm::vec4 getLamp() const;
    void setLamp(const glm::vec4 &value);
    glm::vec4 getLspec() const;
    void setLspec(const glm::vec4 &value);
    glm::vec3 getLDir() const;
    void setLDir(const glm::vec3 &value);
    float getShine() const;
    void setShine(float value);
};

#endif // LIGHT_H
