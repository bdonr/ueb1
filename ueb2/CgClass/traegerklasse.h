#ifndef TRAEGERKLASSE_H
#define TRAEGERKLASSE_H

#include "glm/glm.hpp"
#include <vector>
class TraegerKlasse
{

private: glm::vec3 intvec;
    std::vector<int > x;
    int tab;
public:
    TraegerKlasse();
    TraegerKlasse(std::vector<int> x);
    void setX(int x);
    void setY(int y);
    void setZ (int z);

    glm::vec3 getIntvec() const;
    void setIntvec(const glm::vec3 &value);
    int getTab() const;
    void setTab(int value);
    std::vector<int> getX() const;
};

#endif // TRAEGERKLASSE_H
