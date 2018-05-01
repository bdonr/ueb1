#ifndef CGSCENECONTROL_H
#define CGSCENECONTROL_H

#include "CgBase/CgObserver.h"
#include "CgBase/CgBaseSceneControl.h"
#include <glm/glm.hpp>
#include <CgBase/CgBaseTriangleMesh.h>
#include "CgBase/CgBaseTriangleMesh.h"
#include "rotationskoerper.h"
#include "koordinatensystem.h"
class CgBaseEvent;
class CgBaseRenderer;
class CgExampleTriangle;

class CgSceneControl : public CgObserver, public CgBaseSceneControl
{
public:
    CgSceneControl();
    ~CgSceneControl();
    void handleEvent(CgBaseEvent* e);
    void setRenderer(CgBaseRenderer* r);
    void resetRenderKegel(int refine,float hoehe,float radius);
    void resetRenderZylinder(int refine,float hoehe,float radius);
    void renderObjects();
    void resetObject();
    void reset();
    int getChanged();
private:
    CgBaseRenderer* m_renderer;
    Dreiecke* dreiecke;
    RotationsKoerper* poly;
    std::vector<CgBaseTriangleMesh*> m_triangle;
    glm::mat4 m_current_transformation;
    glm::mat4 m_proj_matrix;
    float s;
    float x;
    float y;
    float z;
    int changed;
    std::vector<glm::vec3> dreickevertices;
    Koordinatensystem* koordinatensystem;
    std::vector<unsigned int> dreieckecords;



};

#endif // CGSCENECONTROL_H
