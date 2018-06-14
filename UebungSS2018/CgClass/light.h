#ifndef LIGHT_H
#define LIGHT_H

#include "glm/common.hpp"
class Light
{
private : glm::vec3 source;
    float itensity;
    glm::vec4 lightcolor;
public:
    Light();

    float getItensity() const;
    void setItensity(float value);
    glm::vec4 getLightcolor() const;
    void setLightcolor(const glm::vec4 &value);
    glm::vec3 getSource() const;
    void setSource(const glm::vec3 &value);
};

#endif // LIGHT_H
