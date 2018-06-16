#ifndef MATS_H
#define MATS_H
#include <glm/common.hpp>

class Mats
{

private: glm::vec4 mamb;
    glm::vec4 mdif;
    glm::vec4 mspec;
    double mshine;
public:
    Mats();
    glm::vec4 getAmb() const;
    void setAmb(const glm::vec4 &value);
    glm::vec4 getDef() const;
    void setDef(const glm::vec4 &value);
    glm::vec4 getSpec() const;
    void setSpec(const glm::vec4 &value);
    double getScalar() const;
    void setScalar(double value);
};

#endif // MATS_H
