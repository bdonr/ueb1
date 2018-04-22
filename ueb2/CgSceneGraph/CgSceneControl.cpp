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


CgSceneControl::CgSceneControl() {
  /* m_triangle.push_back(MeshFactory::createKegel());
   m_triangle.push_back(MeshFactory::createZylinder());
*/

poly = MeshFactory::createRotationKoerper(20);
m_triangle.push_back(MeshFactory::createKegel(0,.0,0));

//resetRender(100);


m_current_transformation = glm::mat4(1.);
m_proj_matrix = glm::mat4x4(glm::vec4(1.792591, 0.0, 0.0, 0.0), glm::vec4(0.0, 1.792591, 0.0, 0.0),
                glm::vec4(0.0, 0.0, -1.0002, -1.0), glm::vec4(0.0, 0.0, -0.020002, 0.0));
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

for(int i = 0; i<=poly->getKeisVec().size()-1;i++){
    m_renderer->init(poly->getKeisVec().at(i));
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
    std::cout<<poly->getKeisVec().size()<<std::endl;
    for(int i = 0; i<=poly->getKeisVec().size()-2;i++){
        m_renderer->render(poly->getKeisVec().at(i),m_current_transformation);
    }

    }
m_renderer->redraw();
}


void CgSceneControl::handleEvent(CgBaseEvent *e) {
    // die Enums sind so gebaut, dass man alle Arten von MausEvents über CgEvent::CgMouseEvent abprüfen kann,
    // siehe dazu die CgEvent enums im CgEnums.h


    if (e->getType() & Cg::CgMouseEvent) {
        CgMouseEvent *ev = (CgMouseEvent *) e;
        std::cout << *ev << std::endl;

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
std::cout<<refine<<" "<<radius<<" kegel "<<hoehe<<std::endl;
        for(int i = 0;i<=m_triangle.size()-1;i++){
                resetRenderKegel(refine,hoehe,radius);
                m_renderer->init(m_triangle.at(i));
        }

    }

    if(e->getType() & Cg::ZylinderChange){
        int refine= ((SliderMoveEvent*)e)->getRefine();
        float radius= ((SliderMoveEvent*)e)->getRadius();
        float hoehe= ((SliderMoveEvent*)e)->getHoehe();
std::cout<<refine<<" "<<radius<<" Zylinder "<<hoehe<<std::endl;
        for(int i = 0; i<=m_triangle.size()-1;i++){
            resetRenderZylinder(refine,hoehe,radius);
            m_renderer->init(m_triangle.at(i));
        }
    }


    // an der Stelle an der ein Event abgearbeitet ist wird es auch gelöscht.
    delete e;
}

