#include "CgSceneControl.h"
#include "CgBase/CgEnums.h"
#include "CgEvents/CgMouseEvent.h"
#include "CgEvents/CgKeyEvent.h"
#include "CgEvents/CgWindowResizeEvent.h"
#include "CgBase/CgBaseRenderer.h"
#include "CgExampleTriangle.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <CgBase/CgBasePolyline.h>
#include "mypolyline.h"
#include "mybox.h"
#include "CgEvents/slidermoveevent.h"

CgSceneControl::CgSceneControl()
{

    h = new MyBox();
    // std::cout<< "hier"<<this->poly->getLineWidth();
     m_current_transformation=glm::mat4(1.);
     m_proj_matrix= glm::mat4x4(glm::vec4(1.792591, 0.0, 0.0, 0.0), glm::vec4(0.0, 1.792591, 0.0, 0.0), glm::vec4(0.0, 0.0, -1.0002, -1.0), glm::vec4(0.0, 0.0, -0.020002, 0.0));
}


CgSceneControl::~CgSceneControl()
{
     m_triangle.clear();
     polies.clear();
     delete h;
}

void CgSceneControl::setRenderer(CgBaseRenderer* r)
{
    m_renderer=r;
    m_renderer->setSceneControl(this);
    m_renderer->init(h);
    for(int i=0;i<=h->getDreiecke().size()-1;i++){
        m_renderer->init(h->getDreiecke().at(i));
        m_renderer->init(h->getDreiecke().at(i)->getPoly());
    }

}


void CgSceneControl::renderObjects()
{


    m_renderer->setProjectionMatrix(m_proj_matrix);

    m_renderer->setLookAtMatrix(glm::mat4x4(glm::vec4(1.0, 0.0, 0.0, 0.0), glm::vec4(0.0, 1.0, 0.0, 0.0), glm::vec4(0.0, 0.0, 1.0, -1.0), glm::vec4(0.0, 0.0, -1.0, 1.0)));


    for(int i=0;i<=h->getDreiecke().size()-1;i++){
        m_renderer->render(h->getDreiecke().at(i),m_current_transformation);
        m_renderer->render(h->getDreiecke().at(i)->getPoly(),m_current_transformation);
    }
}



void CgSceneControl::handleEvent(CgBaseEvent* e)
{
    // die Enums sind so gebaut, dass man alle Arten von MausEvents über CgEvent::CgMouseEvent abprüfen kann,
    // siehe dazu die CgEvent enums im CgEnums.h

    if(e->getType() && Cg::Arschgeburt){
        int x = ((SliderMoveEvent*)e)->getFarbe().x;
        int y= ((SliderMoveEvent*)e)->getFarbe().y;
        int z= ((SliderMoveEvent*)e)->getFarbe().z;
        for(int i=0;i<=h->getDreiecke().size()-1;i++){

            h->getDreiecke().at(i)->getPoly()->setColor(glm::vec3(x,y,z));

        }
        renderObjects();
    }

    if(e->getType() & Cg::CgMouseEvent)
    {
        CgMouseEvent* ev = (CgMouseEvent*)e;
        std::cout << *ev << std::endl;

         // hier kommt jetzt die Abarbeitung des Events hin...
    }

    // die Enums sind so gebaut, dass man alle Arten von KeyEvents über CgEvent::CgKeyEvent abprüfen kann,
    // siehe dazu die CgEvent enums im CgEnums.h
    // momentan werden nur KeyPressEvents gefangen.

    if(e->getType() & Cg::CgKeyEvent)
    {
        CgKeyEvent* ev = (CgKeyEvent*)e;
        std::cout << *ev <<std::endl;

        // hier kommt jetzt die Abarbeitung des Events hin...
    }

    if(e->getType() & Cg::WindowResizeEvent)
    {
         CgWindowResizeEvent* ev = (CgWindowResizeEvent*)e;
         std::cout << *ev <<std::endl;
         m_proj_matrix=glm::perspective(45.0f, (float)(ev->w()) / ev->h(), 0.01f, 100.0f);
    }



    // an der Stelle an der ein Event abgearbeitet ist wird es auch gelöscht.
    delete e;


}
