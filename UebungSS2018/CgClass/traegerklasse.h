#ifndef TRAEGERKLASSE_H
#define TRAEGERKLASSE_H

#include "glm/glm.hpp"
#include <vector>
#include <QString>
class TraegerKlasse
{

private: glm::vec3 intvec;
    std::vector<int> x;
    glm::vec3 dreiDVector;
    QString name;
    glm::vec4 amb;
    glm::vec4 def;
    glm::vec4 spec;
    double scala;
    int an_aus;
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
    int getAn_aus() const;
    void setAn_aus(int value);



    glm::vec4 getDef() const;
    void setDef(const glm::vec4 &value);
    glm::vec4 getSpec() const;
    void setSpec(const glm::vec4 &value);
    double getScala() const;
    void setScala(double value);
    glm::vec4 getAmb() const;
    void setAmb(const glm::vec4 &value);

    QString getName() const;
    void setName(const QString &value);
};

#endif // TRAEGERKLASSE_H
