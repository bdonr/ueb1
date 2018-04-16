#include "CgSceneControl.h"
#include "CgBase/CgEnums.h"
#include "CgEvents/CgMouseEvent.h"
#include "CgEvents/CgKeyEvent.h"
#include "CgEvents/CgWindowResizeEvent.h"
#include "CgBase/CgBaseRenderer.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "meshfactory.h"
#include "Zylinder.h"
#include "kegel.h"

CgSceneControl::CgSceneControl() {
    MeshFactory *v = new MeshFactory();
    //m_triangle.push_back();
   m_triangle.push_back(MeshFactory::createKegel());
   m_triangle.push_back(MeshFactory::createZylinder());
    //fuelleAuf();
   /* std::vector<glm::vec3> g;
    g.push_back(glm::vec3(.0, 0, 0));
    g.push_back(glm::vec3(.1,.15,0));
    g.push_back(glm::vec3(.2,.2,0));
g.push_back(glm::vec3(.25,.2,0));
g.push_back(glm::vec3(.3,.15,0));
g.push_back(glm::vec3(.35,.0,0));*/
std::vector<glm::vec3> k;
k.push_back(glm::vec3(.0, 0, 0));
k.push_back(glm::vec3(.05,.075,0));
k.push_back(glm::vec3(.1,.1,0));
k.push_back(glm::vec3(.15,.15,0));
k.push_back(glm::vec3(.2,.15,0));
k.push_back(glm::vec3(.25,.1,0));
k.push_back(glm::vec3(.3,.075,0));
k.push_back(glm::vec3(.35,.0,0));


std::vector<glm::vec3> a;
std::vector<glm::vec3> b;
std::vector<glm::vec3> c;

a.push_back(glm::vec3(0,0,0));
a.push_back(glm::vec3(0.1,0.075,0));
a.push_back(glm::vec3(0.2,0,0));

b = fuelleAuf(a);

std::cout<<"----b----"<<std::endl;
for(int i=0;i<=b.size()-1;i++){
    std::cout<<b.at(i).x<<b.at(i).y<<b.at(i).z<<std::endl;
}
std::cout<<"----b----"<<std::endl;
poly.push_back(MeshFactory::createMyPolyline(b));
MyPolyline* x= (MyPolyline*)poly.at(0);
x->setVertices(b);
/*g.push_back(glm::vec3(.0, 0, 0));
g.push_back(glm::vec3(.5,.75,0));
g.push_back(glm::vec3(1,.0,0));*/

    //poly.push_back(MeshFactory::createMyPolyline(k));

   // poly.push_back(MeshFactory::createMyPolyline(k));
   // poly.push_back(MeshFactory::createMyPolyline(g));
   //m_triangle.push_back(MeshFactory::createZylinder());
   // std::cout<<(Kegel*)m_triangle->getID();
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
    std::cout<<"size"<<poly.size()<<std::endl;

    for(int i =0;i<=poly.size()-1;i++){
    m_renderer->init(poly.at(i));
    }
/*
    if(!m_triangle.empty()){
    std::cout<<"size"<<m_triangle.size()<<std::endl;
    for(int j =0;j<=m_triangle.size()-1;j++){
    m_renderer->init(m_triangle.at(j));
    }
*/



}


void CgSceneControl::renderObjects() {
    m_renderer->setProjectionMatrix(m_proj_matrix);
    m_renderer->setLookAtMatrix(
            glm::mat4x4(glm::vec4(1.0, 0.0, 0.0, 0.0), glm::vec4(0.0, 1.0, 0.0, 0.0), glm::vec4(0.0, 0.0, 1.0, -1.0),
                        glm::vec4(0.0, 0.0, -1.0, 1.0)));


    if(!m_triangle.empty()){
    for(int i =0;i<=m_triangle.size()-1;i++){
    m_renderer->render(m_triangle.at(i),m_current_transformation);
    }
    }
    for(int j =0;j<=poly.size()-1;j++){
    m_renderer->render(poly.at(j),m_current_transformation);
    }

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
    // siehe dazu die CgEvent enums im CgEnums.h
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


    // an der Stelle an der ein Event abgearbeitet ist wird es auch gelöscht.
    delete e;
}

std::vector<glm::vec3> & CgSceneControl::fuelleAuf(std::vector<glm::vec3>&x){
    int mitte = x.size() / 2;
    int ende = x.size();
    std::cout << ende << "," << mitte << std::endl;
    //unterscheide grade und ungerade anzahl
    if (x.size() % 2 == 0) {
        //hänge an altes array doppelte ab mitte an
        for (int i = mitte; i < ende; i++) {
            std::cout << "-------" << std::endl;
            x.push_back(x.at(i));
            x.push_back(x.at(i));


        }
        //hänge an altes array doppelte ab mitte an
        int div = 1;
        for (int i = 1; i < ende; i = i + 2) {
            x.at(ende - i) = x.at(mitte - div);
            x.at(ende - i - 1) = x.at(mitte - div);
            div++;
        }
    } else {

        //hänge an altes array doppelte ab mitte an
        x.push_back(x.at(mitte));
        for (int i = mitte + 1; i < ende; i++) {
            std::cout << "-------" << std::endl;
            x.push_back(x.at(i));
            x.push_back(x.at(i));

        }
        // von mitte aus nach links alle doppel eintragen
        x.at(ende - 1) = x.at(mitte);
        int div = 1;
        for (int i = 2; i < ende - 1; i = i + 2) {
            x.at(ende - i) = x.at(mitte - div);
            x.at(ende - i - 1) = x.at(mitte - div);
            div++;
        }

        x.at(1) = x.at(0);
    }
    return this->rechne(x);

}

std::vector<glm::vec3>& CgSceneControl::rechne(std::vector<glm::vec3> &x) {
    int laenge = x.size();
    std::cout << "-------" <<laenge << std::endl;
    for (int i = 1; i <= laenge - 2; i++) {
        x.at(i).z = (x.at(i).z + x.at(i + 1).z) / 2;
        x.at(i).y = (x.at(i).y + x.at(i + 1).y) / 2;
        x.at(i).x = (x.at(i).x + x.at(i + 1).x) / 2;
        std::cout << x.at(i).x << "," << x.at(i).y << "," << x.at(i).z << std::endl;
    }
    return x;
}
