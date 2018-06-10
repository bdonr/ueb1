#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H
#include "sceneentity.h"
#include "CgBase/CgBaseRenderer.h"
#include <stack>
#include "glm/glm.hpp"

class Scenegraph
{

private: SceneEntity *sc;
    std::stack <glm::mat4x4> matrixstack;
    int counter;
    enum Cg::ObjectType type;
public:
    void pushMatrix();
    void popMatrix();
    void applyTransform(glm::mat4 x);
    //void fillStack();
    Scenegraph(SceneEntity*sc);
    SceneEntity *getSc() const;
    void setSc(SceneEntity *value);
    void render(CgBaseRenderer * render,SceneEntity* sc);
    // void fillstack(SceneEntity *sc);
    void fillstack(SceneEntity *sc);
    bool h;

};

#endif // SCENEGRAPH_H
