﻿#include "CgSceneControl.h"
#include "CgBase/CgEnums.h"
#include "CgEvents/CgMouseEvent.h"
#include "CgEvents/CgKeyEvent.h"
#include "CgEvents/CgWindowResizeEvent.h"
#include "CgBase/CgBaseRenderer.h"
#include "slidermoveevent.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "meshfactory.h"
#include "Zylinder.h"
#include "kegel.h"
#include <stdio.h>
#include <string.h>
#include "CgUtils/ObjLoader.h"
#include "../CgEvents/objectopenevent.h"
#include "besterslidermoveevent.h"
#include "scenegraph.h"
#include "sceneentity.h"

// bla dingens
void CgSceneControl::createScene()
{

    kugel=MeshFactory::createKugel(1,20,20);
    SceneEntity * sc1 = new SceneEntity(kugel,Cg::Stern,glm::vec3(0,0,0));
    SceneEntity * sc2 = new SceneEntity(kugel,Cg::Erde,glm::vec3(7,0,0));
    SceneEntity * sc3 = new SceneEntity(kugel,Cg::Mond1,glm::vec3(2,0,0));

    SceneEntity * sc4 = new SceneEntity(kugel,Cg::Planet1,glm::vec3(12,0,0));
    SceneEntity * sc5 = new SceneEntity(kugel,Cg::Planet2,glm::vec3(17,0,0));
    SceneEntity * sc6 = new SceneEntity(kugel,Cg::Mond2,glm::vec3(4,0,0));
    SceneEntity * sc7 = new SceneEntity(kugel,Cg::Mond3,glm::vec3(2,0,0));
    //sc5->setTransformation(transform((11,2,0),0,0,0,.1));
    sc1->addChildren(sc2);
    sc1->addChildren(sc4);
    sc1->addChildren(sc5);
    sc2->addChildren(sc3);
    sc4->addChildren(sc6);
    sc4->addChildren(sc7);

    sc = new Scenegraph(sc1);
}

void CgSceneControl::createStandartMatrix()
{
    old=glm::mat4(           glm::vec4(1,0,0,0),
                             glm::vec4(0,1,0,0),
                             glm::vec4(0,0,1,0),
                             glm::vec4(0,0,0,1));
}

CgSceneControl::CgSceneControl() {
    /* m_triangle.push_back(MeshFactory::createKegel());
   m_triangle.push_back(MeshFactory::createZylinder());
*/
    //  koordinatensystem = new Koordinatensystem();
    // changed=1;
    //koordinatensystem = new Koordinatensystem();
    tab=0;
    countW=0.0;
    countA=0.0;
    countS=0.0;
    countD=0.0;
    countQ=0.0;
    countE=0.0;
    s=1;
    cam = new Kamera();

    //  cam->setProjection(cam->perspective(100,eye.x,eye.y,eye.z));

    sc=NULL;
    wuerfel=NULL;
    ObjLoader loader;
    s=0.5;
    y=0.0;
    koordinatensystem=new Koordinatensystem();
    //rotationkörper
    rotationbody = MeshFactory::createRotationKoerper(1);
    //kegel, zlinder
    zylinderOderKegel.push_back(MeshFactory::createKegel(0,.0,0));
    //figuren
    dreiecke=NULL;

    m_current_transformation = glm::mat4(1.);
    m_proj_matrix = glm::mat4x4(glm::vec4(1.792591, 0.0, 0.0, 0.0), glm::vec4(0.0, 1.792591, 0.0, 0.0),
                                glm::vec4(0.0, 0.0, -1.0002, -1.0), glm::vec4(0.0, 0.0, -0.020002, 0.0));

    createStandartMatrix();
    verschiebung=glm::vec3(0,0,0);

}

CgSceneControl::~CgSceneControl() {
    //delete m_triangle;

}

void CgSceneControl::initRotationBody()
{
    if(!rotationbody){
        if(!rotationbody->getPolyVec().size()>0){
            for(int i = 0; i<rotationbody->getPolyVec().size()-1;i++){
                m_renderer->init(rotationbody->getPolyVec().at(i));
            }
        }
        if(rotationbody->getKeisVec().size()>1){
            for(int i = 0; i<=rotationbody->getKeisVec().size()-2;i++){
                m_renderer->init(rotationbody->getKeisVec().at(i));
            }
        }
        if(rotationbody->getNormale().size()>0){
            for(int i = 0; i<=rotationbody->getNormale().size()-1;i++){
                m_renderer->init(rotationbody->getNormale().at(i));
            }

        }

    }
}

void CgSceneControl::setRenderer(CgBaseRenderer *r) {
    m_renderer = r;
    m_renderer->setSceneControl(this);
    for(int i = 0; i<koordinatensystem->getPolylines().size();i++){
        m_renderer->init(koordinatensystem->getPolylines().at(i));

    }
    //sc->render(m_renderer,sc->getSc());
    // registerSceneGraph(m_renderer,sc->getSc());

    // m_renderer->init(kugel);

    //initRotationBody();




}
void CgSceneControl::resetRenderKegel(int refine,float hoehe,float radius){

    Kegel* x = (Kegel*)MeshFactory::createKegel(refine,hoehe,radius);
    pushpop(x);
}
void CgSceneControl::pushpop(CgBaseTriangleMesh* x)
{
    this->zylinderOderKegel.pop_back();
    this->zylinderOderKegel.push_back(x);
}

void CgSceneControl::resetRenderZylinder(int refine,float hoehe,float radius){

    Zylinder* x = (Zylinder*)MeshFactory::createZylinder(refine,hoehe,radius);
    pushpop(x);
}
void CgSceneControl::resetRenderKugel(int refine,float hoehe,float radius){

    Kugel* x = (Kugel*)MeshFactory::createZylinder(refine,hoehe,radius);
    pushpop(x);
}
void CgSceneControl::resetObject(){
    delete dreiecke;
    this->dreiecke=(Dreiecke*) MeshFactory::createDreiecke(dreickevertices,dreieckecords);
}


void CgSceneControl::renderRotationsBody()
{
    if(rotationbody){
        if(!rotationbody->getKeisVec().empty())
            if(rotationbody->getPolyVec().size()>0){
                for(int i = 0; i<rotationbody->getPolyVec().size()-1;i++){
                    m_renderer->render(rotationbody->getPolyVec().at(i),old);
                }
            }
        if(!rotationbody->getKeisVec().empty()){
            if(rotationbody->getKeisVec().size()>1){
                for(int i = 0; i<=rotationbody->getKeisVec().size()-2;i++){
                    m_renderer->render(rotationbody->getKeisVec().at(i),old);
                }
            }
        }
        if(!rotationbody->getNormale().empty()){
            if(rotationbody->getNormale().size()>0){
                for(int i = 0; i<=rotationbody->getNormale().size()-1;i++){
                    m_renderer->render(rotationbody->getNormale().at(i),old);
                }
            }
        }
    }
}

void CgSceneControl::renderWurfel()
{
    if(wuerfel){
        m_renderer->render(wuerfel,old );
        for(int i =0; i<wuerfel->getGeraden().size();i++){
            m_renderer->render(wuerfel->getGeraden().at(i),old);
        }
    }
}

void CgSceneControl::renderCoords()
{
    for(int i = 0; i<=koordinatensystem->getPolylines().size()-1;i++){
        m_renderer->render(koordinatensystem->getPolylines().at(i),m_current_transformation);
    }
}

void CgSceneControl::renderTriangle()
{
    if(zylinderOderKegel.size()>0){
        for(int i =0;i<=zylinderOderKegel.size()-1;i++){
            m_renderer->render(zylinderOderKegel.at(i),m_current_transformation);
        }
    }
}

void CgSceneControl::renderDreiecke()
{
    if(dreiecke){
        m_renderer->render(dreiecke,old);
    }
}

void CgSceneControl::renderObjects() {
    m_renderer->setProjectionMatrix(m_proj_matrix);
    m_renderer->setLookAtMatrix(cam->getLookAt());
    renderCoords();
    renderWurfel();
    renderRotationsBody();
    renderTriangle();
    renderDreiecke();





    if(sc){
        sc->render(m_renderer,sc->getSc());
    }
    m_renderer->redraw();
}
void CgSceneControl::reset(){
    delete dreiecke;
    dreiecke=NULL;
    delete rotationbody;
    rotationbody=NULL;
    zylinderOderKegel.clear();
    //objecte.clear();
    changed=1;
}
int CgSceneControl::getChanged(){
    return changed;
}

glm::mat4x4 CgSceneControl::rotationX(int winkelx)
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

glm::mat4x4 CgSceneControl::rotationY(int winkely)
{
    return glm::mat4x4(glm::vec4(glm::cos(glm::radians(winkely*1.0)),0,(-1)*glm::sin(glm::radians(winkely*1.0)),0),
                       glm::vec4(0,1,0,0),
                       glm::vec4(glm::sin(glm::radians(winkely*1.0)),0,glm::cos(glm::radians(winkely*1.0)),0),
                       glm::vec4(0,0,0,1));
}

glm::mat4x4 CgSceneControl::rotationZ(int winkelz)
{
    return glm::mat4x4(glm::vec4(glm::cos(glm::radians(winkelz*1.0)),glm::sin(glm::radians(winkelz*1.0)),0,0),
                       glm::vec4((-1)*glm::sin(glm::radians(winkelz*1.0)),glm::cos(glm::radians(winkelz*1.0)),0,0),
                       glm::vec4(0,0,1,0),
                       glm::vec4(0,0,0,1));
}

void CgSceneControl::registerSceneGraph(CgBaseRenderer *r, SceneEntity* e)
{
    if(e->getChildren().empty()){
        r->init(e->getOb());
    }
    else{
        for(int i=0;i<=e->getChildren().size()-1;i++){
            r->init(e->getChildren().at(i)->getOb());
            if(!e->getChildren().at(i)->getChildren().empty()){
                registerSceneGraph(r,e->getChildren().at(i));
            }
        }
    }
}

void CgSceneControl::drawSceneGraph(CgBaseRenderer *r, SceneEntity *e)
{

    if(e->getChildren().empty()){
        r->render(e->getOb(),e->getTransformation());
    }
    else{
        for(int i=0;i<=e->getChildren().size()-1;i++){
            r->render(e->getChildren().at(i)->getOb(),e->getChildren().at(i)->getTransformation());
            if(!e->getChildren().at(i)->getChildren().empty()){
                drawSceneGraph(r,e->getChildren().at(i));
            }
        }
    }
}

glm::mat4x4 CgSceneControl::transform(glm::vec3 k,float winkely,float winkelz,float wunschwinkel,float skala)
{
    calculateNewTransformation(verschiebung);
    return
            rotationZ(-winkelz)*
            rotationY(-winkely)*
            rotationZ(wunschwinkel)*
            rotationY(winkely)*
            rotationZ(winkelz)*translatetoVectot(k)*old;
}

glm::mat4x4 CgSceneControl::transform(glm::vec3 k,int winkely,int winkelz,int wunschwinkel)
{
    return translatetoVectot(k)*translatetoVectot(glm::vec3((-1)*k.x,(-1)*k.y,(-1)*k.z))*
            rotationZ(-winkelz)*
            rotationY(-winkely)*
            rotationZ(wunschwinkel)*
            rotationY(winkely)*
            rotationZ(winkelz)*translatetoVectot(k)*glm::mat4x4(         glm::vec4(s,0,0,0),
                                                                         glm::vec4(0,s,0,0),
                                                                         glm::vec4(0,0,s,0),
                                                                         glm::vec4(0,0,0,1));
}


glm::mat4x4 CgSceneControl::translatetoVectot(glm::vec3 k)
{
    return glm::mat4x4( glm::vec4(1,0,0,0),
                        glm::vec4(0,1,0,0),
                        glm::vec4(0,0,1,0),
                        glm::vec4(k.x,k.y,k.z,1));
}

void CgSceneControl::changeColorCube(CgBaseEvent *e)
{
    if (e->getType() == Cg::CgChangeColor){
        glm::vec3 colors=((bestersliderMoveEvent*) e)->getTraegerKlasse()->getDreiDVector();
        delete wuerfel;
        wuerfel=NULL;
        wuerfel = MeshFactory::createWuerfel(colors);
    }
}

void CgSceneControl::changeKegel(CgBaseEvent *e)
{
    if (e->getType() == Cg::KegelChange){

        traeger = ((bestersliderMoveEvent*) e)->getTraegerKlasse();

        float hoehe = traeger->getDreiDVector().x;
        float radius = traeger->getDreiDVector().y;
        float refine = traeger->getDreiDVector().z;

        std::cout<<"change kegel" << hoehe<<" "<<radius<<" "<<refine<<std::endl;
        if(refine<=3){
            this->reset();
        }

        if(refine>3){
           if(zylinderOderKegel.size()==0){
               zylinderOderKegel.push_back(MeshFactory::createKegel(refine,hoehe,radius));
           }
                for(int i = 0; i<=zylinderOderKegel.size()-1;i++){
                    //resetRenderKegel(refine,hoehe,radius);
                    m_renderer->init(zylinderOderKegel.at(i));
                    m_renderer->render(zylinderOderKegel.at(i),m_current_transformation);
                }

        }
    }
}

void CgSceneControl::changeZylinder(CgBaseEvent *e)
{
    if(e->getType() & Cg::ZylinderChange){
        int refine= ((SliderMoveEvent*)e)->getRefine();
        float radius= ((SliderMoveEvent*)e)->getRadius();
        float hoehe= ((SliderMoveEvent*)e)->getHoehe();

        if(refine<=3){
            this->reset();
        }

        if(changed==1 && refine>3){
            changed=0;
            this->zylinderOderKegel.push_back(MeshFactory::createZylinder(refine,hoehe,radius));

        }
        if(changed==0 && refine>3){

                for(int i = 0; i<=zylinderOderKegel.size()-1;i++){
                    resetRenderZylinder(refine,hoehe,radius);
                    m_renderer->init(zylinderOderKegel.at(i));
                }

        }
    }
}


void CgSceneControl::changeRefineRota(CgBaseEvent *e)
{
    if(e->getType() == Cg::RefineRota){
        int refine= ((SliderMoveEvent*)e)->getRefine();
        if(refine<=3){
            delete this->rotationbody;
            rotationbody =NULL;

            changed=0;
        }
        else{
            delete rotationbody;
            rotationbody=NULL;
            this->rotationbody = MeshFactory::createRotationKoerper(refine);
            if(rotationbody->getKeisVec().size()>0){
                for(int i = 0; i<rotationbody->getKeisVec().size();i++){
                    m_renderer->init(rotationbody->getKeisVec().at(i));

                }
            }
            if(rotationbody->getNormale().size()>0){
                for(int i = 0; i<rotationbody->getNormale().size();i++){
                    m_renderer->init(rotationbody->getNormale().at(i));
                }
            }
            if(rotationbody->getPolyVec().size()>0){
                for(int i = 0; i<rotationbody->getPolyVec().size();i++){
                    m_renderer->init(rotationbody->getPolyVec().at(i));
                }
            }

        }

    }
}

void CgSceneControl::handleKeyY(CgBaseEvent *e)
{
    m_current_transformation=m_current_transformation*rotationY(y);
    if(y==3){
        y=0;
    }
    else{
        y=y+.5;
    }


}

void CgSceneControl::handleKeyX(CgBaseEvent *e)
{

    m_current_transformation=m_current_transformation*rotationX(x);
    if(x==3){
        x=0;
    }
    else{
        x=x+0.5;
    }


}

void CgSceneControl::handleKeyZ(CgBaseEvent *e)
{
    m_current_transformation=m_current_transformation*rotationZ(z);
    if(z==3){
        z=0;
    }

    //1 0 0 -4
    //0 1 0 0
    //0 0 1 0
    //0 0 0 1
    else{  old=glm::mat4x4(         glm::vec4(1,0,0,0),
                                    glm::vec4(0,1,0,0),
                                    glm::vec4(0,0,1,0),
                                    glm::vec4(z,0,0,1))*glm::mat4x4(         glm::vec4(s,0,0,0),
                                                                             glm::vec4(0,s,0,0),
                                                                             glm::vec4(0,0,s,0),
                                                                             glm::vec4(0,0,0,1))*glm::mat4x4(         glm::vec4(1,0,0,0),
                                                                                                                      glm::vec4(0,1,0,0),
                                                                                                                      glm::vec4(0,0,1,0),
                                                                                                                      glm::vec4(-z,0,0,1));
        z=z+0.5;
    }


}

void CgSceneControl::handleKeyMinus(CgBaseEvent *e)
{

    if(s<0.01){
        s=0.01;
    }else{
        s=s-0.02;
    }

    calculateNewTransformation(verschiebung);

    if(sc){
        sc->getSc()->setTransformation(glm::mat4x4(          glm::vec4(s,0,0,0),
                                                             glm::vec4(0,s,0,0),
                                                             glm::vec4(0,0,s,0),
                                                             glm::vec4(0,0,0,1)));
    }



}

void CgSceneControl::handleKeyPlus(CgBaseEvent *e)
{

    if(s>0.9){
        s=0.9;
    }else{
        s=s+0.02;
    }

    std::cout<<"3: "<<"s"<<s<<""<<std::endl;
    calculateNewTransformation(verschiebung);

    if(sc){
        sc->getSc()->setTransformation(glm::mat4x4(          glm::vec4(s,0,0,0),
                                                             glm::vec4(0,s,0,0),
                                                             glm::vec4(0,0,s,0),
                                                             glm::vec4(0,0,0,1)));
    }

}

void CgSceneControl::handleKeyD(CgBaseEvent *e)
{

    countA+=.1;
    cam->strafePLUS(countA);

}

void CgSceneControl::handleKeyA(CgBaseEvent *e)
{
    countA-=.1;
    cam->strafeMINUS((-1)*countA);
}

void CgSceneControl::handleKeyW(CgBaseEvent *e)
{
    countW+=.1;
    cam->towardPLUS(countW);
}

void CgSceneControl::handleKeyS(CgBaseEvent *e)
{
    countW-=.1;
    cam->towardMINUS((-1)*countW);
}

void CgSceneControl::handleKeyU(CgBaseEvent *e)
{
    cam->rotateMinus();
}

void CgSceneControl::handleKeyI(CgBaseEvent *e)
{
    cam->rotatePlus();
}

void CgSceneControl::handleKeyEvents(CgBaseEvent *e)
{
    switch(((CgKeyEvent*)e)->key()){
    case Cg::Key_Y:handleKeyX(e);
        break;
    case Cg::Key_Z:handleKeyZ(e);
        break;
    case Cg::Key_Minus : handleKeyMinus(e);
        break;
    case Cg::Key_Plus:handleKeyPlus(e);
        break;
    case Cg::Key_D:handleKeyD(e);
        break;
    case Cg::Key_A:handleKeyA(e);
        break;
    case Cg::Key_W:handleKeyW(e);
        break;
    case Cg::Key_S:handleKeyS(e);
        break;
    case Cg::Key_U:handleKeyU(e);
        break;
    case Cg::Key_I:handleKeyI(e);
        break;
    default:
        break;
    }
}

void CgSceneControl::changeRota(CgBaseEvent *e)
{
    if(e->getType()==Cg::CgChangeRota){
        bool k=false;
        float x =((bestersliderMoveEvent*)e)->getTraegerKlasse()->getIntvec().x/10;
        float y =((bestersliderMoveEvent*)e)->getTraegerKlasse()->getIntvec().y/10;
        float z =((bestersliderMoveEvent*)e)->getTraegerKlasse()->getIntvec().z/10;
        verschiebung = glm::vec3(x,y,z);
        old = transform(verschiebung,10,20,30);
        x=true;
    }
}

void CgSceneControl::windowresize(CgBaseEvent *e)
{
    if (e->getType() == Cg::WindowResizeEvent) {
        CgWindowResizeEvent *ev = (CgWindowResizeEvent *) e;
        std::cout <<"2: "<< *ev << std::endl;
        m_proj_matrix = glm::perspective(45.0f, (float) (ev->w()) / ev->h(), 0.01f, 100.0f);

    }
}

void CgSceneControl::changePage(CgBaseEvent *e)
{

    if(e->getType()==Cg::TabChange){
        page =((bestersliderMoveEvent*)e)->getTraegerKlasse()->getTab();
        std::cout<<"page "<<page<<std::endl;
        if(page==0)page1();
        if(page==1)page2();
        if(page==2)page3();
        if(page==3)page4();
        if(page==4)page5();
    }
}

void CgSceneControl::loadObject(CgBaseEvent *e)
{
    if(e->getType()==Cg::CgChangeWahl){

        if(objecte.empty()){
            ObjLoader loader;
            loader.load("../CgData/bunny.obj");
            loader.getPositionData(dreickevertices);
            loader.getFaceIndexData(dreieckecords);
            objecte.push_back(MeshFactory::createDreiecke(dreickevertices,dreieckecords));
            loader.load("../CgData/tyra.obj");
            loader.getPositionData(dreickevertices);
            loader.getFaceIndexData(dreieckecords);
            objecte.push_back(MeshFactory::createDreiecke(dreickevertices,dreieckecords));
            loader.load("../CgData/porsche.obj");
            loader.getPositionData(dreickevertices);
            loader.getFaceIndexData(dreieckecords);
            objecte.push_back(MeshFactory::createDreiecke(dreickevertices,dreieckecords));
            //            loader.load("../CgData/kugel.obj");
            //            loader.getPositionData(dreickevertices);
            //            loader.getFaceIndexData(dreieckecords);
            //            objecte.push_back(MeshFactory::createDreiecke(dreickevertices,dreieckecords));
        }
        dreiecke = objecte.at(((ObjectOpenEvent*) e)->getWahl());
        this->m_renderer->init(dreiecke);
        this->m_renderer->redraw();

    }
}

void CgSceneControl::handleEvent(CgBaseEvent *e) {

    // die Enums sind so gebaut, dass man alle Arten von MausEvents über CgEvent::CgMouseEvent abprüfen kann,
    // siehe dazu die CgEvent enums im CgEnums.h
    if (e->getType() == Cg::CgMouseEvent) {
        std::cout<<"6: "<<((CgMouseEvent *) e)->getLocalPos().x<<std::endl;
        std::cout<<"7: "<<((CgMouseEvent *) e)->getLocalPos().y<<std::endl;
        // hier kommt jetzt die Abarbeitung des Events hin...
    }

    // die Enums sind so gebaut, dass man alle Arten von KeyEvents über CgEvent::CgKeyEvent abprüfen kann,
    // siehe dazu die CgEvent eolynums im CgEnums.h
    // momentan werden nur KeyPressEvents gefangen.

    if (e->getType() == Cg::CgKeyEvent) {
        CgKeyEvent *ev = (CgKeyEvent *) e;
        std::cout <<"1: "<< *ev << std::endl;
        handleKeyEvents(ev);

        // hier kommt jetzt die Abarbeitung des Events hin...
    }
    changePage(e);
    windowresize(e);
    //(int refine,float hoehe,float radius)
    changeColorCube(e);
    changeKegel(e);
    changeZylinder(e);
    changeRefineRota(e);
    changeRota(e);
    loadObject(e);


    // an der Stelle an der ein Event abgearbeitet ist wird es auch gelöscht.
    delete e;

}
void CgSceneControl::page1(){
    //würfel
    resetAll();

}
void CgSceneControl::page2(){
    resetAll();
}
void CgSceneControl::page3(){
    //figuren
    std::cout<<"tyra porsche"<<std::endl;
}
void CgSceneControl::page4(){
    //sonnesystem
    std::cout<<"sonnensystem"<<std::endl;
}
void CgSceneControl::page5(){

}
void CgSceneControl::resetAll(){
    delete sc;
    sc=NULL;
    delete dreiecke;
    dreiecke=NULL;
    zylinderOderKegel.clear();
    wuerfel=NULL;
    delete wuerfel;

}
glm::mat4x4 CgSceneControl::overallRotation(int x, int y, int z){
    float x1=x*1.;
    float y1=y*1.;
    float z1=z*1.0;
}
void CgSceneControl::renew(){

}

glm::mat4x4 rotationX(int x){

}

void CgSceneControl::calculateNewTransformation(glm::vec3 verschiebung){
    old=m_current_transformation*
            glm::mat4x4(         glm::vec4(s,0,0,0),
                                 glm::vec4(0,s,0,0),
                                 glm::vec4(0,0,s,0),
                                 glm::vec4(verschiebung.x,verschiebung.y,verschiebung.z,1));
    //glm::mat4x4 CgSceneControl::rotation(int x, int y, int z)

    //
}
