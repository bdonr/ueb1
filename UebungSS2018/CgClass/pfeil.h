#ifndef PFEIL_H
#define PFEIL_H
#include <CgClass/kegel.h>
#include <CgClass/Zylinder.h>
#include "CgBase/CgBaseRenderer.h"
#include "glm/glm.hpp"
#include "iostream"
#include "CgClass/appearance.h"
class Pfeil
{
private: Kegel* kegel;
    Zylinder* zylinder;
    glm::mat4x4 transform();
    CgBaseRenderer *render;
    Appearance* appear;
public:
    Pfeil(CgBaseRenderer *render,Appearance* appear);
    Kegel *getKegel() const;
    void setKegel(Kegel *value);
    Zylinder *getZylinder() const;
    void setZylinder(Zylinder *value);

    glm::mat4 transformation;
    void renderO(glm::mat4x4 p);
};

#endif // PFEIL_H
