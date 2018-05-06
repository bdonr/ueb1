#include "CgSceneControl.h"
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

// bla dingens
CgSceneControl::CgSceneControl() {
    /* m_triangle.push_back(MeshFactory::createKegel());
   m_triangle.push_back(MeshFactory::createZylinder());
*/
    //  koordinatensystem = new Koordinatensystem();
    // changed=1;
    //koordinatensystem = new Koordinatensystem();
    ObjLoader loader;
    s=0.5;
    y=0.0;
    koordinatensystem=new Koordinatensystem();
    poly = MeshFactory::createRotationKoerper(1);
    m_triangle.push_back(MeshFactory::createKegel(0,.0,0));
    dreiecke=NULL;
    glm::vec3 b2 = glm::vec3(9.,1.,1.);
    glm::vec3 b1 = glm::vec3(0,0,0);
    std::vector<glm::vec3> st;
    st.push_back(b1);
    st.push_back(b2);

    rotaAchse = MeshFactory::createMyPolyline(glm::vec3(220,9,200),st);
    //resetRender(100);

    m_current_transformation = glm::mat4(1.);

    glm::mat4x4 old=m_current_transformation;
    m_proj_matrix = glm::mat4x4(glm::vec4(1.792591, 0.0, 0.0, 0.0), glm::vec4(0.0, 1.792591, 0.0, 0.0),
                                glm::vec4(0.0, 0.0, -1.0002, -1.0), glm::vec4(0.0, 0.0, -0.020002, 0.0));
    /*
m_proj_matrix = glm::mat4x4(glm::vec4(1.792591, 0.0, 0.0, 0.0), glm::vec4(0.0, 1.792591, 0.0, 0.0),
                glm::vec4(0.0, 0.0, -1.0002, -1.0), glm::vec4(0.0, 0.0, -0.020002, 0.0));
*/
}

CgSceneControl::~CgSceneControl() {
    //delete m_triangle;

}

void CgSceneControl::setRenderer(CgBaseRenderer *r) {
    m_renderer = r;
    m_renderer->setSceneControl(this);
    for(int i = 0; i<koordinatensystem->getPolylines().size();i++){
        m_renderer->init(koordinatensystem->getPolylines().at(i));

    }
    if(!poly){
        if(!poly->getPolyVec().size()>0){
            for(int i = 0; i<poly->getPolyVec().size()-1;i++){
                m_renderer->init(poly->getPolyVec().at(i));
            }
        }


        if(poly->getKeisVec().size()>1){
            for(int i = 0; i<=poly->getKeisVec().size()-2;i++){
                m_renderer->init(poly->getKeisVec().at(i));
            }
        }
        if(poly->getNormale().size()>0){
            for(int i = 0; i<=poly->getNormale().size()-1;i++){
                m_renderer->init(poly->getNormale().at(i));
            }

        }
        if(rotaAchse){
            std::cout<<"huhu"<<std::endl;
            m_renderer->init(rotaAchse);
        }
    }



}
void CgSceneControl::resetRenderKegel(int refine,float hoehe,float radius){

    Kegel* x = (Kegel*)MeshFactory::createKegel(refine,hoehe,radius);
    this->m_triangle.pop_back();
    this->m_triangle.push_back(x);
}
void CgSceneControl::resetRenderZylinder(int refine,float hoehe,float radius){

    Zylinder* x = (Zylinder*)MeshFactory::createZylinder(refine,hoehe,radius);
    this->m_triangle.pop_back();
    this->m_triangle.push_back(x);
}

void CgSceneControl::resetObject(){
    delete dreiecke;
    this->dreiecke=(Dreiecke*) MeshFactory::createDreiecke(dreickevertices,dreieckecords);
}


void CgSceneControl::renderObjects() {
    m_renderer->setProjectionMatrix(m_proj_matrix);
    m_renderer->setLookAtMatrix(
                glm::mat4x4(glm::vec4(1.0, 0.0, 0.0, 0.0), glm::vec4(0.0, 1.0, 0.0, 0.0), glm::vec4(0.0, 0.0, 1.0, -1.0),
                            glm::vec4(0.0, 0.0, -1.0, 1.0)));
    for(int i = 0; i<=koordinatensystem->getPolylines().size()-1;i++){
        m_renderer->render(koordinatensystem->getPolylines().at(i),m_current_transformation);
    }
    if(rotaAchse!=NULL){
        m_renderer->render(rotaAchse,m_current_transformation);
    }
    if(poly){
        if(!poly->getKeisVec().empty())
            if(poly->getPolyVec().size()>0){
                for(int i = 0; i<poly->getPolyVec().size()-1;i++){
                    m_renderer->render(poly->getPolyVec().at(i),m_current_transformation);
                }
            }
        if(!poly->getKeisVec().empty()){
            if(poly->getKeisVec().size()>1){
                for(int i = 0; i<=poly->getKeisVec().size()-2;i++){
                    m_renderer->render(poly->getKeisVec().at(i),m_current_transformation);
                }
            }
        }
        if(!poly->getNormale().empty()){
            if(poly->getNormale().size()>0){
                for(int i = 0; i<=poly->getNormale().size()-1;i++){
                    m_renderer->render(poly->getNormale().at(i),m_current_transformation);
                }
            }
        }
    }
    if(m_triangle.size()>0){
        for(int i =0;i<=m_triangle.size()-1;i++){
            m_renderer->render(m_triangle.at(i),m_current_transformation);
        }
    }

    if(dreiecke){
        m_renderer->render(dreiecke,m_current_transformation);
    }



    m_renderer->redraw();
}
void CgSceneControl::reset(){
    delete dreiecke;
    dreiecke=NULL;
    delete poly;
    poly=NULL;
    m_triangle.clear();
    //objecte.clear();
    changed=1;
}
int CgSceneControl::getChanged(){
    return changed;
}

glm::mat4x4 CgSceneControl::rotationX(int winkelx)
{
    return glm::mat4x4(glm::vec4(1,0,0,0),
                       glm::vec4(0,glm::cos(glm::radians(winkelx*1.0)),(-1)*glm::sin(glm::radians(winkelx*1.0)),0),
                       glm::vec4(0,glm::sin(glm::radians(winkelx*1.0)),glm::cos(glm::radians(winkelx*1.0)),0),
                       glm::vec4(0,0,0,1));
}

glm::mat4x4 CgSceneControl::rotationY(int winkely)
{
    return glm::mat4x4(glm::vec4(glm::cos(glm::radians(winkely*1.0)),0,glm::sin(glm::radians(winkely*1.0)),0),
                       glm::vec4(0,1,0,0),
                       glm::vec4((-1)*glm::sin(glm::radians(winkely*1.0)),0,glm::cos(glm::radians(winkely*1.0)),0),
                       glm::vec4(0,0,0,1));
}

glm::mat4x4 CgSceneControl::rotationZ(int winkelz)
{
    return glm::mat4x4(glm::vec4(glm::cos(glm::radians(winkelz*1.0)),(-1)*glm::sin(glm::radians(winkelz*1.0)),0,0),
                       glm::vec4(glm::sin(glm::radians(winkelz*1.0)),glm::cos(glm::radians(winkelz*1.0)),0,0),
                       glm::vec4(0,0,1,0),
                       glm::vec4(0,0,0,1));
}

glm::mat4x4 CgSceneControl::transform(glm::vec3 k)
{
    return glm::mat4x4(glm::vec4(s,0,0,k.x),
                glm::vec4(0,s,0,k.y),
                glm::vec4(0,0,s,k.z),
                glm::vec4(0,0,0,s));
}

void CgSceneControl::handleEvent(CgBaseEvent *e) {

    // die Enums sind so gebaut, dass man alle Arten von MausEvents über CgEvent::CgMouseEvent abprüfen kann,
    // siehe dazu die CgEvent enums im CgEnums.h
    if (e->getType() & Cg::CgMouseEvent) {
        CgMouseEvent *ev = (CgMouseEvent *) e;

        // hier kommt jetzt die Abarbeitung des Events hin...
    }

    // die Enums sind so gebaut, dass man alle Arten von KeyEvents über CgEvent::CgKeyEvent abprüfen kann,
    // siehe dazu die CgEvent eolynums im CgEnums.h
    // momentan werden nur KeyPressEvents gefangen.

    if (e->getType() & Cg::CgKeyEvent) {
        CgKeyEvent *ev = (CgKeyEvent *) e;
        std::cout << *ev << std::endl;

        // hier kommt jetzt die Abarbeitung des Events hin...
    }

    if (e->getType() & Cg::WindowResizeEvent) {
        CgWindowResizeEvent *ev = (CgWindowResizeEvent *) e;
        std::cout << *ev << std::endl;
        m_proj_matrix = glm::perspective(45.0f, (float) (ev->w()) / ev->h(), 0.01f, 100.0f);

    }
    //(int refine,float hoehe,float radius)
    if (e->getType() & Cg::KegelChange){

        int refine= ((SliderMoveEvent*)e)->getRefine();
        float radius= ((SliderMoveEvent*)e)->getRadius();
        float hoehe= ((SliderMoveEvent*)e)->getHoehe();

        if(refine<=3){
            this->reset();
        }

        if(changed==1 && refine>3){
            changed=0;
            this->m_triangle.push_back(MeshFactory::createKegel(refine,hoehe,radius));

        }
        if(changed==0 && refine>3){
            if(m_triangle.size()>0){
                for(int i = 0; i<=m_triangle.size()-1;i++){
                    resetRenderKegel(refine,hoehe,radius);
                    m_renderer->init(m_triangle.at(i));
                }
            }
        }
    }

    if(e->getType() & Cg::ZylinderChange){
        int refine= ((SliderMoveEvent*)e)->getRefine();
        float radius= ((SliderMoveEvent*)e)->getRadius();
        float hoehe= ((SliderMoveEvent*)e)->getHoehe();

        if(refine<=3){
            this->reset();
        }

        if(changed==1 && refine>3){
            changed=0;
            this->m_triangle.push_back(MeshFactory::createZylinder(refine,hoehe,radius));

        }
        if(changed==0 && refine>3){
            if(m_triangle.size()>0){
                for(int i = 0; i<=m_triangle.size()-1;i++){
                    resetRenderZylinder(refine,hoehe,radius);
                    m_renderer->init(m_triangle.at(i));
                }
            }
        }
    }

    if(e->getType() & Cg::RefineRota){
        int refine= ((SliderMoveEvent*)e)->getRefine();
        if(refine<=3){
            delete this->poly;
            poly =NULL;
            changed=0;
        }
        else{
            this->poly = MeshFactory::createRotationKoerper(refine);
            if(poly->getKeisVec().size()>0){
                for(int i = 0; i<poly->getKeisVec().size();i++){
                    m_renderer->init(poly->getKeisVec().at(i));
                    m_renderer->render(poly->getKeisVec().at(i),m_current_transformation);
                }
            }
            if(poly->getNormale().size()>0){
                for(int i = 0; i<poly->getNormale().size();i++){
                    m_renderer->init(poly->getNormale().at(i));
                    m_renderer->render(poly->getNormale().at(i),m_current_transformation);
                }
            }
            if(poly->getPolyVec().size()>0){
                for(int i = 0; i<poly->getPolyVec().size();i++){
                    m_renderer->init(poly->getPolyVec().at(i));
                    m_renderer->render(poly->getPolyVec().at(i),m_current_transformation);
                }
            }

        }

    }

    if(((CgKeyEvent*)e)->key()==Cg::Key_Minus){
        if(s<0.01){
            s=0.01;
        }else{
            s=s-0.2;
        }
        m_current_transformation=m_current_transformation*(glm::mat4x4(glm::vec4(s,0,0,0),
                                                                       glm::vec4(0,s,0,0),
                                                                       glm::vec4(0,0,s,0),
                                                                       glm::vec4(0,0,0,1)));
    }
    if(((CgKeyEvent*)e)->key()==Cg::Key_Plus){
        std::cout<<"§§"<<std::endl;
        if(s>0.9){
            s=0.9;
        }else{
            s=s*1.2;
        }

        m_current_transformation=m_current_transformation*(glm::mat4x4(glm::vec4(s,0,0,0),
                                                                       glm::vec4(0,s,0,0),
                                                                       glm::vec4(0,0,s,0),
                                                                       glm::vec4(0,0,0,1)));

    }

    if(((CgKeyEvent*)e)->key()==Cg::Key_Y){
        m_current_transformation=m_current_transformation*rotationY(y);
        if(y==3){
            y=0;
        }
        else{
            y=y+.5;
        }

    }
    if(((CgKeyEvent*)e)->key()==Cg::Key_X){
        m_current_transformation=m_current_transformation*rotationX(x);
        if(x==3){
            x=0;
        }
        else{
            x=x+0.5;
        }

    }

    if(((CgKeyEvent*)e)->key()==Cg::Key_Z){
        m_current_transformation=m_current_transformation*rotationZ(z);
        if(z==3){
            z=0;
        }
        else{
            z=z+0.5;
        }

    }

    if(((CgKeyEvent*)e)->key()==Cg::Key_Minus){
        if(s<0.01){
            s=0.01;
        }else{
            s=s-0.02;
        }
        m_current_transformation=(glm::mat4x4(glm::vec4(s,0,0,0),
                                              glm::vec4(0,s,0,0),
                                              glm::vec4(0,0,s,0),
                                              glm::vec4(0,0,0,1)));
    }
    if(((CgKeyEvent*)e)->key()==Cg::Key_Plus){
        if(s>0.9){
            s=0.9;
        }else{
            s=s+0.02;
        }

        m_current_transformation=(glm::mat4x4(glm::vec4(s,0,0,0),
                                              glm::vec4(0,s,0,0),
                                              glm::vec4(0,0,s,0),
                                              glm::vec4(0,0,0,1)));

    }

    if(e->getType()==Cg::CgChangeRota){
        bool k=false;
        int x =((bestersliderMoveEvent*)e)->getTraegerKlasse()->getIntvec().x;
        std::cout<<x<<"x"<<std::endl;


        int y =((bestersliderMoveEvent*)e)->getTraegerKlasse()->getIntvec().y;
        int z =((bestersliderMoveEvent*)e)->getTraegerKlasse()->getIntvec().z;
        //glm::vec3 b3=glm::vec3((-1.)*b2.x,(-1.)*b2.y,(-1.)*b2.z);
        //std::cout<<b3.x<<b3.y<<b3.z<<std::endl;
        glm::mat4x4 bla=(rotationZ(z)*rotationY(y)*rotationX(x)*rotationZ(-1.*z)*rotationY(-1.*y));
        m_current_transformation=old*bla;
        x=true;
    }


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
        }
        dreiecke = objecte.at(((ObjectOpenEvent*) e)->getWahl());
        this->m_renderer->init(dreiecke);
        this->m_renderer->redraw();
    }

    // an der Stelle an der ein Event abgearbeitet ist wird es auch gelöscht.
    delete e;

}

glm::mat4x4 CgSceneControl::allgemineRotation(int x, int y, int z){
    float x1=x*1.;
    float y1=y*1.;
    float z1=z*1.0;
}

glm::mat4x4 rotationX(int x){

}

//glm::mat4x4 CgSceneControl::rotation(int x, int y, int z)

