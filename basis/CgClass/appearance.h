#ifndef APPEARANCE_H
#define APPEARANCE_H

#include "glm/glm.hpp"
class Appearance
{

private:
    glm::vec3 color;
    glm::vec3 mats;

public:
    Appearance();
    glm::vec3 getMats() const;
    void setMats(const glm::vec3 &value);
    glm::vec3 getColor() const;
    void setColor(const glm::vec3 &value);
};

#endif // APPEARANCE_H
