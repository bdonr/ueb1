#include "sceneentity.h"
#include "CgBase/CgBaseRenderableObject.h"
CgBaseRenderableObject *SceneEntity::getOb() const
{
    return ob;
}

void SceneEntity::setOb(CgBaseRenderableObject *value)
{
    ob = value;
}



void SceneEntity::addChildren(SceneEntity *value)
{
    value->setParent(this);
    children.push_back(value);
}

SceneEntity *SceneEntity::getParent() const
{
    return parent;
}

void SceneEntity::setParent(SceneEntity *value)
{
    parent = value;

}

glm::mat4 SceneEntity::getTransformation() const
{
    return transformation;
}

void SceneEntity::setTransformation(const glm::mat4 &value)
{
    transformation = value;
}

Appearance *SceneEntity::getAppear() const
{
    return appear;
}

void SceneEntity::setAppear(Appearance *value)
{
    appear = value;
}

std::vector<SceneEntity *> SceneEntity::getChildren() const
{
    return children;
}

SceneEntity::SceneEntity(CgBaseRenderableObject* ob,enum Cg::ObjectType type):ob(ob),type(type)
{
    skala=.2;
}

void SceneEntity::transform(int winkely,int winkelz,int wunschwinkel,glm::mat4x4 matrix)
{
    transformation*=
            rotationZ(-winkelz)*
            rotationY(-winkely)*
            rotationZ(wunschwinkel)*
            rotationY(winkely)*
            rotationZ(winkelz);
}

glm::mat4x4 SceneEntity::rotationX(int winkelx)
{
    glm::mat4x4(glm::vec4(1,0,0,0),
                glm::vec4(0,glm::cos(glm::radians(winkelx*1.0)),(-1)*glm::sin(glm::radians(winkelx*1.0)),0),
                glm::vec4(0,glm::sin(glm::radians(winkelx*1.0)),glm::cos(glm::radians(winkelx*1.0)),0),
                glm::vec4(0,0,0,1));


    return glm::mat4x4(glm::vec4(1,0,0,0),
                       glm::vec4(0,glm::cos(glm::radians(winkelx*1.0)),glm::sin(glm::radians(winkelx*1.0)),0),
                       glm::vec4(0,(-1)*glm::sin(glm::radians(winkelx*1.0)),glm::cos(glm::radians(winkelx*1.0)),0),
                       glm::vec4(0,0,0,1));
}

glm::mat4x4 SceneEntity::rotationY(int winkely)
{
    return glm::mat4x4(glm::vec4(glm::cos(glm::radians(winkely*1.0)),0,(-1)*glm::sin(glm::radians(winkely*1.0)),0),
                       glm::vec4(0,1,0,0),
                       glm::vec4(glm::sin(glm::radians(winkely*1.0)),0,glm::cos(glm::radians(winkely*1.0)),0),
                       glm::vec4(0,0,0,1));
}

glm::mat4x4 SceneEntity::rotationZ(int winkelz)
{
    return glm::mat4x4(glm::vec4(glm::cos(glm::radians(winkelz*1.0)),glm::sin(glm::radians(winkelz*1.0)),0,0),
                       glm::vec4((-1)*glm::sin(glm::radians(winkelz*1.0)),glm::cos(glm::radians(winkelz*1.0)),0,0),
                       glm::vec4(0,0,1,0),
                       glm::vec4(0,0,0,1));
}

void SceneEntity::calculateRota(int winkely, int winkelz, int wunschwinkel)
{
    transformation=

            rotationZ(-winkelz)*
            rotationY(-winkely)*
            rotationZ(wunschwinkel)*
            rotationY(winkely)*
            rotationZ(winkelz);
}

