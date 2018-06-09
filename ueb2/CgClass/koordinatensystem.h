#ifndef KOORDINATENSYSTEM_H
#define KOORDINATENSYSTEM_H

#include <vector>
#include "Mypolyline.h"
#include "pfeil.h"
#include "CgBase/CgBaseRenderer.h"
class Koordinatensystem
{

private:
    std::vector<Pfeil*> pfeile;

    glm::mat4x4 rotationX();
    glm::mat4x4 rotationY();
    glm::mat4x4 rotationZ();
public:
    Koordinatensystem();
    void render(CgBaseRenderer *render);
    std::vector<Pfeil *> getPfeile() const;
    void setPfeile(const std::vector<Pfeil *> &value);
};

#endif // KOORDINATENSYSTEM_H
