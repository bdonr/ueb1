#ifndef KOORDINATENSYSTEM_H
#define KOORDINATENSYSTEM_H

#include <vector>
#include "Mypolyline.h"
#include "pfeil.h"
#include "CgBase/CgBaseRenderer.h"
#include "CgClass/appearance.h"
class Koordinatensystem
{

private:
    std::vector<Pfeil*> pfeile;
    CgBaseRenderer *render;
    glm::mat4x4 translation;
    glm::mat4x4 rotationX();
    glm::mat4x4 rotationY();
    glm::mat4x4 rotationZ();
public:
    Koordinatensystem(CgBaseRenderer *render, glm::mat4x4 x);
    void renderO(bool lighton,glm::mat4x4 x);
    std::vector<Pfeil *> getPfeile() const;
    void setPfeile(const std::vector<Pfeil *> &value);
    glm::mat4x4 getTranslation() const;
    void setTranslation(const glm::mat4x4 &value);
};

#endif // KOORDINATENSYSTEM_H
