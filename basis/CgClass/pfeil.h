#ifndef PFEIL_H
#define PFEIL_H
#include <CgClass/kegel.h>
#include <CgClass/Zylinder.h>
#include "CgBase/CgBaseRenderer.h"
#include "glm/glm.hpp"
#include "iostream"
class Pfeil
{
private: Kegel* kegel;
    Zylinder* zylinder;
    glm::mat4x4 transform(int i);
    CgBaseRenderer *render;
public:
    Pfeil(CgBaseRenderer *render);
    Kegel *getKegel() const;
    void setKegel(Kegel *value);
    Zylinder *getZylinder() const;
    void setZylinder(Zylinder *value);

    glm::mat4 transformation;
    void renderO(glm::mat4x4 p);
};

#endif // PFEIL_H
