#include "sceneentity.h"
#include "CgBase/CgBaseRenderableObject.h"
#include <iostream>
#include "unistd.h"
SceneEntity::SceneEntity(CgBaseRenderableObject* ob,enum Cg::ObjectType type,glm::vec3 ausrichtung):ob(ob),type(type),ausrichtung(ausrichtung)
{

    if(type==Cg::Stern){

        skala=1;
        this->winkelx=0;
        this->winkely=0;
        this->winkelz=10;
        this->transformation=transform();
    }

    if(type==Cg::Erde){

        skala=.5;
        this->winkelx=0;
        this->winkely=0;
        this->winkelz=0;
        this->transformation=transform();
    }

    if(type==Cg::Mond1){

        skala=.5;
        this->winkelx=0;
        this->winkely=0;
        this->winkelz=0;
        this->transformation=transform();
    }

        if(type==Cg::Planet1){

            skala=.2;
            this->winkelx=10;
            this->winkely=20;
            this->winkelz=10;
            this->transformation=transform();
        }

        if(type==Cg::Mond2){

            skala=.5;
            this->winkelx=10;
            this->winkely=20;
            this->winkelz=10;
            this->transformation=transform();
        }

        if(type==Cg::Planet2){

            skala=1;
            this->winkelx=10;
            this->winkely=100;
            this->winkelz=10;
            this->transformation=transform();
        }

}
CgBaseRenderableObject *SceneEntity::getOb() const
{
    return ob;
}

void SceneEntity::setOb(CgBaseRenderableObject *value)
{
    ob = value;
}

void SceneEntity::setAusrichtung(){
    ausrichtung.x+=.10;
    transformation=transform();
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



void SceneEntity::rotate(float winkely,float winkelz,float wunschwinkel,glm::mat4x4 matrix)
{

    if(type==Cg::Stern){

        //wunschwinkel+=wunschwinkel/360;
        transformation*=
                rotationZ(-this->winkelz)*
                rotationY(-this->winkely)*
                rotationZ(wunschwinkel)*
                rotationY(this->winkely)*
                rotationZ(this->winkelz);

    }
    if(type!=Cg::Stern){
    if(type==Cg::Erde){
        transformation*=
                rotationZ(-this->winkelz)*
                rotationY(-this->winkely)*
                rotationZ(wunschwinkel)*
                rotationY(this->winkely)*
                rotationZ(this->winkelz);

        wunschwinkel=wunschwinkel/1.2;

    }


    if(type==Cg::Mond1){


        wunschwinkel=wunschwinkel*28;

    }

    if(type==Cg::Mond2){
        wunschwinkel=wunschwinkel*100;

    }

    if(type==Cg::Planet1){
        wunschwinkel=wunschwinkel*.1;
    }

    if(type==Cg::Planet2){
        wunschwinkel=wunschwinkel*(-10);
        winkely=winkely*1.2;
    }

    glm::mat3x3 matrixcoole = glm::mat3x3(glm::vec3(glm::cos(glm::radians(wunschwinkel)),(-1)*glm::sin(glm::radians(wunschwinkel)),0),
                                          glm::vec3(glm::sin(glm::radians(wunschwinkel)),glm::cos(glm::radians(wunschwinkel)),0),
                                          glm::vec3(0,0,1));
    ausrichtung=ausrichtung*matrixcoole;
    transformation=transform();

}

}

glm::mat4x4 SceneEntity::rotationX(float winkelx)
{
    glm::mat4x4(glm::vec4(1,0,0,0),
                glm::vec4(0,glm::cos(glm::radians(winkelx*10.0)),(-1)*glm::sin(glm::radians(winkelx*10.0)),0),
                glm::vec4(0,glm::sin(glm::radians(winkelx*10.0)),glm::cos(glm::radians(winkelx*10.0)),0),
                glm::vec4(0,0,0,1));


    return glm::mat4x4(glm::vec4(1,0,0,0),
                       glm::vec4(0,glm::cos(glm::radians(winkelx*1.0)),glm::sin(glm::radians(winkelx*1.0)),0),
                       glm::vec4(0,(-1)*glm::sin(glm::radians(winkelx*1.0)),glm::cos(glm::radians(winkelx*1.0)),0),
                       glm::vec4(0,0,0,1));
}

glm::mat4x4 SceneEntity::rotationY(float winkely)
{
    return glm::mat4x4(glm::vec4(glm::cos(glm::radians(winkely*1.0)),0,(-1)*glm::sin(glm::radians(winkely*1.0)),0),
                       glm::vec4(0,1,0,0),
                       glm::vec4(glm::sin(glm::radians(winkely*1.0)),0,glm::cos(glm::radians(winkely*1.0)),0),
                       glm::vec4(0,0,0,1));
}

glm::mat4x4 SceneEntity::rotationZ(float winkelz)
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

glm::mat4x4 SceneEntity::transform(){
    return

            rotationZ(-winkelz)*
            rotationY(-winkely)*
            rotationZ(winkely)*
            rotationY(winkely)*
            rotationZ(winkelz)*translatetoVectot()*glm::mat4x4(         glm::vec4(skala,0,0,0),
                                                                        glm::vec4(0,skala,0,0),
                                                                        glm::vec4(0,0,skala,0),
                                                                        glm::vec4(0,0,0,1));
}

glm::mat4x4 SceneEntity::translatetoVectot()
{
    return glm::mat4x4( glm::vec4(1,0,0,0),
                        glm::vec4(0,1,0,0),
                        glm::vec4(0,0,1,0),
                        glm::vec4(ausrichtung.x,ausrichtung.y,ausrichtung.z,1));
}
