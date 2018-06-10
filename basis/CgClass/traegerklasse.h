#ifndef TRAEGERKLASSE_H
#define TRAEGERKLASSE_H

#include "glm/glm.hpp"
#include <vector>
class TraegerKlasse
{

private: glm::vec3 intvec;
    std::vector<int> x;
    glm::vec3 dreiDVector;
    int zeige_normale;
    int tab;
public:
    TraegerKlasse();
    TraegerKlasse(std::vector<int> x);
    TraegerKlasse(glm::vec3 dreiDVector);

    void setX(int x);
    void setY(int y);
    void setZ (int z);

    glm::vec3 getIntvec() const;
    void setIntvec(const glm::vec3 &value);
    int getTab() const;
    void setTab(int value);
    std::vector<int> getX() const;
    glm::vec3 getDreiDVector() const;
    void setDreiDVector(const glm::vec3 &value);
    int getZeige_normale() const;
    void setZeige_normale(int value);
};

#endif // TRAEGERKLASSE_H
