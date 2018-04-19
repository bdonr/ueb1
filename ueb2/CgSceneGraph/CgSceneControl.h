#ifndef CGSCENECONTROL_H
#define CGSCENECONTROL_H

#include "CgBase/CgObserver.h"
#include "CgBase/CgBaseSceneControl.h"
#include <glm/glm.hpp>
#include <CgBase/CgBaseTriangleMesh.h>
#include "Mypolyline.h"
#include "CgBase/CgBaseTriangleMesh.h"

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
    void resetRenderKegel(int d);
    void resetRenderZylinder(int d);
    void renderObjects();

private:
    CgBaseRenderer* m_renderer;
    std::vector<MyPolyline*> poly;
    std::vector<CgBaseTriangleMesh*> m_triangle;
    glm::mat4 m_current_transformation;
    glm::mat4 m_proj_matrix;



};

#endif // CGSCENECONTROL_H
