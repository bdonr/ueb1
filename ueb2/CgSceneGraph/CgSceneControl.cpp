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
// bla dingens
CgSceneControl::CgSceneControl() {
  /* m_triangle.push_back(MeshFactory::createKegel());
   m_triangle.push_back(MeshFactory::createZylinder());
*/
std::string file = "../CgData/bunny.obj";
ObjLoader loader;
x=0.5;
loader.load(file);
loader.getPositionData(dreickevertices);

loader.getFaceIndexData(dreieckecords);
dreiecke = MeshFactory::createDreiecke(dreickevertices,dreieckecords);


poly = MeshFactory::createRotationKoerper(1);
m_triangle.push_back(MeshFactory::createKegel(0,.0,0));

//resetRender(100);


m_current_transformation = glm::mat4(1.);
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


for(int i = 0; i<=poly->getPolyVec().size()-1;i++){
    m_renderer->init(poly->getPolyVec().at(i));
}
    this->m_renderer->init(dreiecke);



for(int i = 0; i<=poly->getKeisVec().size()-1;i++){
    m_renderer->init(poly->getKeisVec().at(i));
}
for(int i = 0; i<=poly->getNormale().size()-1;i++){
    m_renderer->init(poly->getNormale().at(i));
}
    m_renderer->init(m_triangle.at(0));

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
    for(int i = 0; i<poly->getPolyVec().size()-1;i++){

        m_renderer->render(poly->getPolyVec().at(i),m_current_transformation);
    }

    if(!m_triangle.empty()){
    for(int i =0;i<=m_triangle.size()-1;i++){
    m_renderer->render(m_triangle.at(i),m_current_transformation);

    }
    for(int i = 0; i<=poly->getKeisVec().size()-2;i++){
        m_renderer->render(poly->getKeisVec().at(i),m_current_transformation);
    }
    for(int i = 0; i<=poly->getNormale().size()-1;i++){

        m_renderer->render(poly->getNormale().at(i),m_current_transformation);
    }
    m_renderer->render(dreiecke,m_current_transformation);


    }
m_renderer->redraw();
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
        for(int i = 0;i<=m_triangle.size()-1;i++){
                resetRenderKegel(refine,hoehe,radius);
                m_renderer->init(m_triangle.at(i));
        }

    }

    if(e->getType() & Cg::ZylinderChange){
        int refine= ((SliderMoveEvent*)e)->getRefine();
        float radius= ((SliderMoveEvent*)e)->getRadius();
        float hoehe= ((SliderMoveEvent*)e)->getHoehe();
        for(int i = 0; i<=m_triangle.size()-1;i++){
            resetRenderZylinder(refine,hoehe,radius);
            m_renderer->init(m_triangle.at(i));
        }
    }
    if(e->getType() & Cg::RefineRota){
        int refine= ((SliderMoveEvent*)e)->getRefine();
        delete this->poly;
        this->poly = MeshFactory::createRotationKoerper(refine);

        for(int i = 0; i<=poly->getKeisVec().size()-1;i++){
             m_renderer->init(poly->getKeisVec().at(i));
        }

        for(int i = 0; i<=poly->getNormale().size()-1;i++){
             m_renderer->init(poly->getNormale().at(i));
        }
        for(int i = 0; i<=poly->getPolyVec().size()-1;i++){
             m_renderer->init(poly->getPolyVec().at(i));
        }

    }
    std::cout<<"code key "<<((CgKeyEvent*)e)->getType()<<"spezial "<<Cg::Key_0<<" "<<((CgKeyEvent*)e)->key()<<std::endl;
    if(((CgKeyEvent*)e)->key()==Cg::Key_Minus){
        if(x<0.01){
            x=0.01;
        }else{
            x=x-0.02;
        }
            m_current_transformation=(glm::mat4x4(glm::vec4(x,0,0,0),
                                                  glm::vec4(0,x,0,0),
                                                  glm::vec4(0,0,x,0),
                                                  glm::vec4(0,0,0,1)));
        m_renderer->init(dreiecke);
        m_renderer->render(dreiecke, m_current_transformation);

         /* m_current_transformation=(glm::mat4x4(glm::vec4(-x,0,0,0),
                                                  glm::vec4(0,-x,0,0),
                                                  glm::vec4(0,0,-x,0),
                                                  glm::vec4(0,0,0,1)));
        */


        resetObject();
        m_renderer->init(dreiecke);
        //renderObjects();
        m_renderer->render(dreiecke,m_current_transformation);
    }

    if(((CgKeyEvent*)e)->key()==Cg::Key_Plus){
        if(x>0.9){
            x=0.9;
        }else{
            x=x+0.02;
        }

        m_current_transformation=(glm::mat4x4(glm::vec4(x,0,0,0),
                                              glm::vec4(0,x,0,0),
                                              glm::vec4(0,0,x,0),
                                              glm::vec4(0,0,0,1)));
    m_renderer->init(dreiecke);
    m_renderer->render(dreiecke, m_current_transformation);
/*
        m_current_transformation=(glm::mat4x4(glm::vec4(x,0,0,0),
                                              glm::vec4(0,x,0,0),
                                              glm::vec4(0,0,x,0),
                                              glm::vec4(0,0,0,1)));
                                              */

        resetObject();
        m_renderer->init(dreiecke);
        //renderObjects();
        m_renderer->render(dreiecke,m_current_transformation);
    }

    // an der Stelle an der ein Event abgearbeitet ist wird es auch gelöscht.
    delete e;
}

