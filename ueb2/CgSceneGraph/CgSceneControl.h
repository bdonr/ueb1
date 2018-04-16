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
    std::vector<glm::vec3>& rechne(std::vector<glm::vec3> &x);
    std::vector<glm::vec3> &fuelleAuf(std::vector<glm::vec3>&x);

    void renderObjects();

private:
    CgBaseRenderer* m_renderer;
    std::vector<CgBasePolyline*> poly;
    std::vector<CgBaseTriangleMesh*> m_triangle;
    glm::mat4 m_current_transformation;
    glm::mat4 m_proj_matrix;

};

#endif // CGSCENECONTROL_H
