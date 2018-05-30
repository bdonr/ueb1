#ifndef SCENEENTITY_H
#define SCENEENTITY_H
#include "CgBase/CgBaseRenderableObject.h"
#include "glm/glm.hpp"
#include "appearance.h"
#include <vector>
class SceneEntity
{
private:
    glm::mat4x4 rotationY(float winkely);
    glm::mat4x4 rotationX(float winkelx);
    glm::mat4x4 rotationZ(float winkelz);
    float winkely;
    float winkelx;
    float winkelz;
    glm::vec3 ausrichtung;
    CgBaseTriangleMesh*ob;
    std::vector<SceneEntity*> children;
    SceneEntity* parent;
    glm::mat4 transformation;
    Appearance* appear;
    float skala;
    glm::mat4 rota;
    enum Cg::ObjectType type;
public:
    void calculateRota(int winkely, int winkelz, int wunschwinkel);
    SceneEntity(CgBaseTriangleMesh*ob,enum Cg::ObjectType type,glm::vec3 aus);
    CgBaseTriangleMesh *getOb() const;
    void setOb(CgBaseTriangleMesh *value);
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
  //  void transform();

    void rotate(float winkel_y, float winkel_z, float wunschwinkel);
    glm::mat4x4 translatetoVectot();
    void setAusrichtung();
    glm::mat4x4 transform();
};

#endif // SCENEENTITY_H
