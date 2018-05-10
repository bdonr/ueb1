#ifndef SCENEENTITY_H
#define SCENEENTITY_H
#include "CgBase/CgBaseRenderableObject.h"
#include "glm/glm.hpp"
#include "appearance.h"
#include <vector>
class SceneEntity
{
private:
    glm::mat4x4 rotationX(int winkelx);
    glm::mat4x4 rotationY(int winkely);
    glm::mat4x4 rotationZ(int winkelz);
    CgBaseRenderableObject*ob;
    std::vector<SceneEntity*> children;
    SceneEntity* parent;
    glm::mat4 transformation;
    Appearance* appear;
    float skala;
    glm::mat4 rota;
    enum Cg::ObjectType type;
public:
    void calculateRota(int winkely, int winkelz, int wunschwinkel);
    SceneEntity(CgBaseRenderableObject*ob,enum Cg::ObjectType type);
    CgBaseRenderableObject *getOb() const;
    void setOb(CgBaseRenderableObject *value);
    void addChildren(SceneEntity *value);
    SceneEntity *getParent() const;
    void setParent(SceneEntity *value);
    glm::mat4 getTransformation() const;
    void setTransformation(const glm::mat4 &value);
    Appearance *getAppear() const;
    void setAppear(Appearance *value);
    std::vector<SceneEntity*> getChildren() const;
    void draw();
    //void transform(int winkely, int winkelz, int wunschwinkel);
    void transform(int winkely, int winkelz, int wunschwinkel, glm::mat4x4 matrix);
};

#endif // SCENEENTITY_H
