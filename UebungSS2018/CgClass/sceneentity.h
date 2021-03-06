#ifndef SCENEENTITY_H
#define SCENEENTITY_H
#include "CgBase/CgBaseTriangleMesh.h"
#include "glm/glm.hpp"
#include "appearance.h"
#include <vector>
#include "CgClass/kugel.h"
class SceneEntity
{
private:

    float winkely;
    float winkelx;
    float winkelz;
    glm::vec3 bewegung;
    CgBaseTriangleMesh*ob;
    std::vector<SceneEntity*> children;
    SceneEntity* parent;
    glm::mat4 transformation;
    Appearance* appear;
    float skala;
    glm::mat4 rota;
    enum Cg::ObjectType type;
public:
    glm::mat4x4 rotationY(float winkely);
    glm::mat4x4 rotationX(float winkelx);
    glm::mat4x4 rotationZ(float winkelz);
    void calculateRota(int winkely, int winkelz, int wunschwinkel);
    SceneEntity(CgBaseTriangleMesh*ob,enum Cg::ObjectType type,glm::vec3 aus,Appearance* appear);
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
    void rotateMond(float wunschwinkel, float winkel_y);
    void rotateErde(float winkel_y, float wunschwinkel);
    void rotateMond2(float winkel_z, float wunschwinkel);
    void set(float x, float z, float y);
};

#endif // SCENEENTITY_H
