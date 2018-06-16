#ifndef LIGHT_H
#define LIGHT_H

#include "glm/common.hpp"

class Light
{


    /*varying vec4 adif;
    varying vec4 aamb;
    varying vec4 aspec;
*/

private : glm::vec3 source;
    glm::vec4 adif;
    glm::vec4 aamb;
    glm::vec4 aspec;
    glm::vec3 adir;

public:
    Light();


    // CgBaseRenderableObject interface


    glm::vec3 getSource() const;
    void setSource(const glm::vec3 &value);
    glm::vec4 getAdif() const;
    void setAdif(const glm::vec4 &value);
    glm::vec4 getAamb() const;
    void setAamb(const glm::vec4 &value);
    glm::vec4 getAspec() const;
    void setAspec(const glm::vec4 &value);
    glm::vec3 getAdir() const;
    void setAdir(const glm::vec3 &value);
};

#endif // LIGHT_H
