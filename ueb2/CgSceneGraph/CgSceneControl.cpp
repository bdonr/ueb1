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
    MeshFactory *v = new MeshFactory();
  /* m_triangle.push_back(MeshFactory::createKegel());
   m_triangle.push_back(MeshFactory::createZylinder());
*/
std::vector<glm::vec3> c;


c.push_back(glm::vec3(0,0,0));
c.push_back(glm::vec3(0.1,0.075,0));
c.push_back(glm::vec3(0.2,0,0));
c.push_back(glm::vec3(0.2,0.075,0));

poly.push_back(MeshFactory::createMyPolyline(c));
m_triangle.push_back(MeshFactory::createKegel(10));

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


    m_renderer->init(poly.at(0));
    m_renderer->init(m_triangle.at(0));

}
 void CgSceneControl::resetRender(int d){
     Kegel* x = (Kegel*)MeshFactory::createKegel(d);
     this->m_triangle.pop_back();
     this->m_triangle.push_back(x);


 }


void CgSceneControl::renderObjects() {
    m_renderer->setProjectionMatrix(m_proj_matrix);
    m_renderer->setLookAtMatrix(
            glm::mat4x4(glm::vec4(1.0, 0.0, 0.0, 0.0), glm::vec4(0.0, 1.0, 0.0, 0.0), glm::vec4(0.0, 0.0, 1.0, -1.0),
                        glm::vec4(0.0, 0.0, -1.0, 1.0)));

    m_renderer->render(poly.at(0),m_current_transformation);

    if(!m_triangle.empty()){
    for(int i =0;i<=m_triangle.size()-1;i++){
    m_renderer->render(m_triangle.at(i),m_current_transformation);

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

    if (e->getType() & Cg::KegelChange){
        int x = ((SliderMoveEvent*)e)->getWert();
        enum Cg::EventType y = ((SliderMoveEvent*)e)->getType();
        for(int i = 0;i<=m_triangle.size()-1;i++){
            std::cout<<m_triangle.at(i)->getType()<<"bla"<<std::endl;
            if(m_triangle.at(i)->getType()==4){

               ((Kegel *) m_triangle.at(i))->setRefine(x);
                std::cout<<"bla"<<x<<std::endl;

                resetRender(x);
                m_renderer->init(m_triangle.at(i));

            }
        }

    }


    // an der Stelle an der ein Event abgearbeitet ist wird es auch gelöscht.
    delete e;
}

