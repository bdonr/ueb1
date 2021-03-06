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
    int counterIncre;
    enum Cg::ObjectType type;
    void findAndSetAppear(SceneEntity *sc, Appearance *appear, Cg::ObjectType type);
public:
    void pushMatrix();
    void popMatrix();
    void applyTransform(glm::mat4 x);
    //void fillStack();
    Scenegraph(SceneEntity*sc);
    void findAndSetAppear(Appearance* appear,enum Cg::ObjectType);
    SceneEntity *getSc() const;
    void setSc(SceneEntity *value);
    void render(CgBaseRenderer * render,SceneEntity* sc);
    // void fillstack(SceneEntity *sc);
    void fillstack(SceneEntity *sc);
    bool h;


    void setUniform(int i, CgBaseRenderer *render, SceneEntity* sc);
    void setUniform(CgBaseRenderer *render, SceneEntity *sc);
    int getCounterIncre() const;
    void setCounterIncre(int value);
};

#endif // SCENEGRAPH_H
