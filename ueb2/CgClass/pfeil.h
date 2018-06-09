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
public:
    Pfeil();
    Kegel *getKegel() const;
    void setKegel(Kegel *value);
    Zylinder *getZylinder() const;
    void setZylinder(Zylinder *value);
    void render(CgBaseRenderer *render,glm::mat4x4);
    glm::mat4 transformation;
};

#endif // PFEIL_H
