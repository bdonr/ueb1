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
#include "scenegraph.h"
#include "sceneentity.h"
// bla dingens
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


    wuerfel=NULL;
    ObjLoader loader;
    s=0.5;
    y=0.0;
    koordinatensystem=new Koordinatensystem();
    //rotationkörper
    poly = MeshFactory::createRotationKoerper(1);
    //kegel, zlinder
    m_triangle.push_back(MeshFactory::createKegel(0,.0,0));
    //figuren
    dreiecke=NULL;
    // kugel=NULL;
    glm::vec3 b2 = glm::vec3(9.,1.,1.);
    glm::vec3 b1 = glm::vec3(0,0,0);
    std::vector<glm::vec3> st;
    st.push_back(b1);
    st.push_back(b2);



    //std::ofstream("../CgData/kugel.obj");


    // rotaAchse = MeshFactory::createMyPolyline(glm::vec3(220,9,200),st);
    //resetRender(100);

    m_current_transformation = glm::mat4(1.);
    m_proj_matrix = glm::mat4x4(glm::vec4(1.792591, 0.0, 0.0, 0.0), glm::vec4(0.0, 1.792591, 0.0, 0.0),
                                glm::vec4(0.0, 0.0, -1.0002, -1.0), glm::vec4(0.0, 0.0, -0.020002, 0.0));
    glm::vec3 b3 = glm::vec3(b2.x*(-1.),b2.y*(-1.),(-1.)*b2.z);
    old=glm::mat4(           glm::vec4(1,0,0,0),
                             glm::vec4(0,1,0,0),
                             glm::vec4(0,0,1,0),
                             glm::vec4(0,0,0,1));
    verschiebung=glm::vec3(0,0,0);
    //sonnensystem
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

CgSceneControl::~CgSceneControl() {
    //delete m_triangle;

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
void CgSceneControl::resetRenderKugel(int refine,float hoehe,float radius){

    Kugel* x = (Kugel*)MeshFactory::createZylinder(refine,hoehe,radius);
    this->m_triangle.pop_back();
    this->m_triangle.push_back(x);
}
void CgSceneControl::resetObject(){
    delete dreiecke;
    this->dreiecke=(Dreiecke*) MeshFactory::createDreiecke(dreickevertices,dreieckecords);
}


void CgSceneControl::renderObjects() {
    m_renderer->setProjectionMatrix(m_proj_matrix);
    m_renderer->setLookAtMatrix(cam->getLookAt());
    for(int i = 0; i<=koordinatensystem->getPolylines().size()-1;i++){
        m_renderer->render(koordinatensystem->getPolylines().at(i),m_current_transformation);
    }

    //m_renderer->render(kugel,old);

    if(wuerfel){
        m_renderer->render(wuerfel,old );
        for(int i =0; i<wuerfel->getGeraden().size();i++){
            m_renderer->render(wuerfel->getGeraden().at(i),old);
        }
    }
    if(poly){
        if(!poly->getKeisVec().empty())
            if(poly->getPolyVec().size()>0){
                for(int i = 0; i<poly->getPolyVec().size()-1;i++){
                    m_renderer->render(poly->getPolyVec().at(i),old);
                }
            }
        if(!poly->getKeisVec().empty()){
            if(poly->getKeisVec().size()>1){
                for(int i = 0; i<=poly->getKeisVec().size()-2;i++){
                    m_renderer->render(poly->getKeisVec().at(i),old);
                }
            }
        }
        if(!poly->getNormale().empty()){
            if(poly->getNormale().size()>0){
                for(int i = 0; i<=poly->getNormale().size()-1;i++){
                    m_renderer->render(poly->getNormale().at(i),old);
                }
            }
        }
    }
    if(m_triangle.size()>0){
        for(int i =0;i<=m_triangle.size()-1;i++){
            m_renderer->render(m_triangle.at(i),m_current_transformation);
        }
    }
    //    drawSceneGraph(m_renderer,sc->getSc());

    // m_renderer->render(kugel,old);

    if(dreiecke){
        m_renderer->render(dreiecke,old);
    }



    if(sc){
    sc->render(m_renderer,sc->getSc());
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

    return
            rotationZ(-winkelz)*
            rotationY(-winkely)*
            rotationZ(wunschwinkel)*
            rotationY(winkely)*
            rotationZ(winkelz)*translatetoVectot(k)*glm::mat4x4(         glm::vec4(skala,0,0,0),
                                                                         glm::vec4(0,skala,0,0),
                                                                         glm::vec4(0,0,skala,0),
                                                                         glm::vec4(verschiebung.x,verschiebung.y,verschiebung.z,1));
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

void CgSceneControl::handleEvent(CgBaseEvent *e) {

    // die Enums sind so gebaut, dass man alle Arten von MausEvents über CgEvent::CgMouseEvent abprüfen kann,
    // siehe dazu die CgEvent enums im CgEnums.h
    if (e->getType() & Cg::CgMouseEvent) {
        std::cout<<"6: "<<((CgMouseEvent *) e)->getLocalPos().x<<std::endl;
        std::cout<<"7: "<<((CgMouseEvent *) e)->getLocalPos().y<<std::endl;
        // hier kommt jetzt die Abarbeitung des Events hin...
    }

    // die Enums sind so gebaut, dass man alle Arten von KeyEvents über CgEvent::CgKeyEvent abprüfen kann,
    // siehe dazu die CgEvent eolynums im CgEnums.h
    // momentan werden nur KeyPressEvents gefangen.

    if (e->getType() & Cg::CgKeyEvent) {
        CgKeyEvent *ev = (CgKeyEvent *) e;
        std::cout <<"1: "<< *ev << std::endl;

        // hier kommt jetzt die Abarbeitung des Events hin...
    }

    if (e->getType() & Cg::WindowResizeEvent) {
        CgWindowResizeEvent *ev = (CgWindowResizeEvent *) e;
        std::cout <<"2: "<< *ev << std::endl;
        m_proj_matrix = glm::perspective(45.0f, (float) (ev->w()) / ev->h(), 0.01f, 100.0f);

    }
    //(int refine,float hoehe,float radius)
    if (e->getType() & Cg::CgChangeColor){
        glm::vec3 colors=glm::vec3(0,0,0);
        colors.x = ((bestersliderMoveEvent*) e)->getTraegerKlasse()->getX().at(0);
        colors.y = ((bestersliderMoveEvent*) e)->getTraegerKlasse()->getX().at(1);
        colors.z = ((bestersliderMoveEvent*) e)->getTraegerKlasse()->getX().at(2);
        delete wuerfel;
        wuerfel=NULL;
        wuerfel = MeshFactory::createWuerfel(colors);
    }

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

    if(e->getType() & Cg::KugelChange){
        int refine= ((SliderMoveEvent*)e)->getRefine();
        float radius= ((SliderMoveEvent*)e)->getRadius();
        float hoehe= ((SliderMoveEvent*)e)->getHoehe();
        if(refine<=3){
            this->reset();
        }

        if(refine>3){
            //   kugel = MeshFactory::createKugel(refine,hoehe,radius);
            //  m_renderer->init(kugel);
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
            delete poly;
            poly=NULL;
            this->poly = MeshFactory::createRotationKoerper(refine);
            if(poly->getKeisVec().size()>0){
                for(int i = 0; i<poly->getKeisVec().size();i++){
                    m_renderer->init(poly->getKeisVec().at(i));
                    m_renderer->render(poly->getKeisVec().at(i),old);
                }
            }
            if(poly->getNormale().size()>0){
                for(int i = 0; i<poly->getNormale().size();i++){
                    m_renderer->init(poly->getNormale().at(i));
                    m_renderer->render(poly->getNormale().at(i),old);
                }
            }
            if(poly->getPolyVec().size()>0){
                for(int i = 0; i<poly->getPolyVec().size();i++){
                    m_renderer->init(poly->getPolyVec().at(i));
                    m_renderer->render(poly->getPolyVec().at(i),old);
                }
            }

        }

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

    if(((CgKeyEvent*)e)->key()==Cg::Key_Minus){
        if(s<0.01){
            s=0.01;
        }else{
            s=s-0.02;
        }

        old=m_current_transformation*
                glm::mat4x4(         glm::vec4(s,0,0,0),
                                     glm::vec4(0,s,0,0),
                                     glm::vec4(0,0,s,0),
                                     glm::vec4(verschiebung.x,verschiebung.y,verschiebung.z,1));
        if(sc){
        sc->getSc()->setTransformation(glm::mat4x4(          glm::vec4(s,0,0,0),
                                                             glm::vec4(0,s,0,0),
                                                             glm::vec4(0,0,s,0),
                                                             glm::vec4(0,0,0,1)));
        }


    }

    if(((CgKeyEvent*)e)->key()==Cg::Key_Plus){
        if(s>0.9){
            s=0.9;
        }else{
            s=s+0.02;
        }

        std::cout<<"3: "<<"s"<<s<<""<<std::endl;
        old=m_current_transformation*
                glm::mat4x4(         glm::vec4(s,0,0,0),
                                     glm::vec4(0,s,0,0),
                                     glm::vec4(0,0,s,0),
                                     glm::vec4(verschiebung.x,verschiebung.y,verschiebung.z,1));

        if(sc){
        sc->getSc()->setTransformation(glm::mat4x4(          glm::vec4(s,0,0,0),
                                                             glm::vec4(0,s,0,0),
                                                             glm::vec4(0,0,s,0),
                                                             glm::vec4(0,0,0,1)));
        }
    }
    if(((CgKeyEvent*)e)->key()==Cg::Key_D){
        countA+=.1;
        cam->strafePLUS(countA);
    }
    if(((CgKeyEvent*)e)->key()==Cg::Key_A){

        countA-=.1;
        cam->strafeMINUS((-1)*countA);
    }


    if(((CgKeyEvent*)e)->key()==Cg::Key_W){
        countW+=.1;
        cam->towardPLUS(countW);
    }

    if(((CgKeyEvent*)e)->key()==Cg::Key_S){
        countW-=.1;
        cam->towardMINUS((-1)*countW);

    }
    if(((CgKeyEvent*)e)->key()==Cg::Key_U){

        cam->rotateMinus();

    }
    if(((CgKeyEvent*)e)->key()==Cg::Key_I){

        cam->rotatePlus();
    }



    if(e->getType()==Cg::CgChangeRota){
        bool k=false;
        float x =((bestersliderMoveEvent*)e)->getTraegerKlasse()->getIntvec().x/10;
        float y =((bestersliderMoveEvent*)e)->getTraegerKlasse()->getIntvec().y/10;
        float z =((bestersliderMoveEvent*)e)->getTraegerKlasse()->getIntvec().z/10;
        verschiebung = glm::vec3(x,y,z);
        old = transform(verschiebung,10,20,30);
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
            //            loader.load("../CgData/kugel.obj");
            //            loader.getPositionData(dreickevertices);
            //            loader.getFaceIndexData(dreieckecords);
            //            objecte.push_back(MeshFactory::createDreiecke(dreickevertices,dreieckecords));
        }
        dreiecke = objecte.at(((ObjectOpenEvent*) e)->getWahl());
        this->m_renderer->init(dreiecke);
        this->m_renderer->redraw();
    }
    if(e->getType()==Cg::TabChange){
        int x =((bestersliderMoveEvent*)e)->getTraegerKlasse()->getTab();
        if(x==0)tab1constructor();
        if(x==1)tab2constructor();
        if(x==2)tab3constructor();
        if(x==3)tab4constructor();
        if(x==4)tab5constructor();
    }


    // an der Stelle an der ein Event abgearbeitet ist wird es auch gelöscht.
    delete e;

}
void CgSceneControl::tab1constructor(){
//würfel
    resetAll();
    glm::vec3 y(255,0,0);
      wuerfel = MeshFactory::createWuerfel(y);
      m_renderer->init(wuerfel);
      if(wuerfel){
          for(int i =0; i<wuerfel->getGeraden().size();i++){
              m_renderer->init(wuerfel->getGeraden().at(i));
          }
      }

      if(wuerfel){
          for(int i =0; i<wuerfel->getGeraden().size();i++){
              m_renderer->render(wuerfel->getGeraden().at(i),m_current_transformation);
          }
      }
    std::cout<<"4: "<<"würfel"<<std::endl;
}
void CgSceneControl::tab2constructor(){
// zylinder, kegel, rota körper
    std::cout<<"kegel zylinder"<<std::endl;
}
void CgSceneControl::tab3constructor(){
//figuren
    std::cout<<"tyra porsche"<<std::endl;
}
void CgSceneControl::tab4constructor(){
//sonnesystem
    std::cout<<"sonnensystem"<<std::endl;
}
void CgSceneControl::tab5constructor(){

}
void CgSceneControl::resetAll(){
    delete sc;
    sc=NULL;
   delete dreiecke;
    dreiecke=NULL;
   m_triangle.clear();
   wuerfel=NULL;
   delete wuerfel;

}
glm::mat4x4 CgSceneControl::allgemineRotation(int x, int y, int z){
    float x1=x*1.;
    float y1=y*1.;
    float z1=z*1.0;
}
void CgSceneControl::renew(){

}

glm::mat4x4 rotationX(int x){

}

//glm::mat4x4 CgSceneControl::rotation(int x, int y, int z)

//
