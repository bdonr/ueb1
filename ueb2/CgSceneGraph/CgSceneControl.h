#ifndef CGSCENECONTROL_H
#define CGSCENECONTROL_H

#include "CgBase/CgObserver.h"
#include "CgBase/CgBaseSceneControl.h"
#include <glm/glm.hpp>
#include <CgBase/CgBaseTriangleMesh.h>
#include "CgBase/CgBaseTriangleMesh.h"
#include "rotationskoerper.h"

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

private:
    CgBaseRenderer* m_renderer;

    RotationsKoerper* poly;
    std::vector<CgBaseTriangleMesh*> m_triangle;
    glm::mat4 m_current_transformation;
    glm::mat4 m_proj_matrix;



};

#endif // CGSCENECONTROL_H
