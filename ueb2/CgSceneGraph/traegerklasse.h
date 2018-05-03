#ifndef TRAEGERKLASSE_H
#define TRAEGERKLASSE_H

#include "glm/glm.hpp"
class TraegerKlasse
{

private: glm::vec3 intvec;
public:
    TraegerKlasse();
    void setX(int x);
    void setY(int y);
    void setZ (int z);

    glm::vec3 getIntvec() const;
    void setIntvec(const glm::vec3 &value);
};

#endif // TRAEGERKLASSE_H
