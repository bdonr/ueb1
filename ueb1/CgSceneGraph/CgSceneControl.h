#ifndef CGSCENECONTROL_H
#define CGSCENECONTROL_H

#include "CgBase/CgObserver.h"
#include "CgBase/CgBaseSceneControl.h"
#include <glm/glm.hpp>
#include "mypolyline.h"
#include "mybox.h"

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

    void renderObjects();

private:
    MyBox*h;
    std::vector<MyPolyline*> polies;
    CgBaseRenderer* m_renderer;
    std::vector<CgExampleTriangle*> m_triangle;
    glm::mat4 m_current_transformation;
    glm::mat4 m_proj_matrix;

};

#endif // CGSCENECONTROL_H
