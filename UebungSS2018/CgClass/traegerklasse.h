#ifndef TRAEGERKLASSE_H
#define TRAEGERKLASSE_H

#include "glm/glm.hpp"
#include <vector>
#include <QString>

/**
 * @brief The TraegerKlasse class
 *
 * Hilfsklasse zum Transport von Informationen zwischen GUI und SceneControl
 */
class TraegerKlasse
{

private: glm::vec3 intvec;
    std::vector<int> x;
    glm::vec3 dreiDVector;
    QString name;
    glm::vec4 amb;
    glm::vec4 def;
    glm::vec4 spec;
    int shading;
    int interpol;
    double scala;
    int an_aus;
    int tab;
    std::string log;

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
    std::string getLog() const;
    void setLog(const std::string &value);
    int getShading() const;
    void setShading(int value);
    int getInterpol() const;
    void setInterpol(int value);

};

#endif // TRAEGERKLASSE_H
