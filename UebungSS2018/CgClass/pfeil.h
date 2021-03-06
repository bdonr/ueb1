#ifndef PFEIL_H
#define PFEIL_H
#include <CgClass/kegel.h>
#include <CgClass/Zylinder.h>
#include "CgBase/CgBaseRenderer.h"
#include "glm/glm.hpp"
#include "iostream"
#include "CgClass/appearance.h"
#include "CgClass/mats.h"
class Pfeil
{
private: Kegel* kegel;
    Zylinder* zylinder;
    glm::mat4x4 transform();
    glm::mat4x4 xyz;
    CgBaseRenderer *renderer;
    bool lighton;
public:
    Pfeil(CgBaseRenderer *renderer,Appearance* appear);
    Kegel *getKegel() const;
    void setKegel(Kegel *value);
    Zylinder *getZylinder() const;
    void setZylinder(Zylinder *value);

    glm::mat4 transformation;
    void render(glm::mat4x4 p,bool lighton);

    void setMaterialZylinder();
    void setMaterialKegel();
    void render(glm::mat4 x);
};

#endif // PFEIL_H
