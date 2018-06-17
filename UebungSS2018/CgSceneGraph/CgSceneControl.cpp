#include "CgSceneControl.h"
#include "CgBase/CgEnums.h"
#include "CgEvents/CgMouseEvent.h"
#include "CgEvents/CgKeyEvent.h"
#include "CgEvents/CgWindowResizeEvent.h"
#include "CgBase/CgBaseRenderer.h"
#include "CgEvents/slidermoveevent.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "CgClass/meshfactory.h"
#include "CgClass/Zylinder.h"
#include "CgClass/kegel.h"
#include <stdio.h>
#include <string.h>
#include "CgUtils/ObjLoader.h"
#include "CgEvents/objectopenevent.h"0.8 0.5 0.5 0.7
#include "CgEvents/allgemeinesEvent.h"
#include "CgClass/scenegraph.h"
#include "CgClass/sceneentity.h"


void CgSceneControl::createScene()
{
    delete sc;
    sc=NULL;
    kugel=MeshFactory::createKugel(1,20,20);
    Appearance* appear = new Appearance();
    Mats *ma = new Mats();
    ma->setAmb(glm::vec4(1.,0,0,1.));
    ma->setDef(glm::vec4(0,1.,1.,1.));
    ma->setScalar(10.2);
    ma->setSpec(glm::vec4(1.,1.,1.,1.));
    appear->setMaterial(ma);
    sc1 = new SceneEntity(kugel,Cg::Stern,glm::vec3(0,0,0),appear);
    sc2 = new SceneEntity(kugel,Cg::Erde,glm::vec3(7,0,0),appear);
    sc3 = new SceneEntity(kugel,Cg::Mond1,glm::vec3(2,0,0),appear);

    sc4 = new SceneEntity(kugel,Cg::Planet1,glm::vec3(12,0,0),appear);
    sc5 = new SceneEntity(kugel,Cg::Planet2,glm::vec3(17,0,0),appear);
    sc6 = new SceneEntity(kugel,Cg::Mond2,glm::vec3(4,0,0),appear);
    sc7 = new SceneEntity(kugel,Cg::Mond3,glm::vec3(2,0,0),appear);
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
    lighton=false;
    cam = new Kamera();

    cam->setProjection(cam->perspective(100,eye.x,eye.y,eye.z));

    sc=NULL;
    wuerfel=NULL;
    shownormals=false;
    ObjLoader loader;
    s=0.5;
    y=0.0;
    kugel=NULL;
    zylinder=NULL;
    kegel=NULL;

    //rotationkörper
    rotationbody = NULL;
    //kegel, zlinder
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
    if(rotationbody!=NULL){
        if((rotationbody->getPolyVec().size())>0){
            for(unsigned int i = 0; i<rotationbody->getPolyVec().size();i++){
                m_renderer->init(rotationbody->getPolyVec().at(i));
            }
        }
        if((rotationbody->getKeisVec().size())>0){
            for(unsigned int i = 0; i<rotationbody->getKeisVec().size();i++){
                m_renderer->init(rotationbody->getKeisVec().at(i));
            }
        }
        if((rotationbody->getNormale().size())>0){
            for(unsigned int i = 0; i<rotationbody->getNormale().size();i++){
                m_renderer->init(rotationbody->getNormale().at(i));
            }

        }

    }
}

void CgSceneControl::setRenderer(CgBaseRenderer *r) {
    m_renderer = r;

    //  setShaderSourceFiles("../UebungSS2018/CgShader/lighton.vert","../UebungSS2018/CgShader/simple.frag");
    m_renderer->setSceneControl(this);

    m_renderer->setShaderSourceFiles("../UebungSS2018/CgShader/lightsoff.vert","../UebungSS2018/CgShader/lightsoff.frag");
}
void CgSceneControl::resetObject(){
    delete dreiecke;
    this->dreiecke=(Dreiecke*) MeshFactory::createDreiecke(dreickevertices,dreieckecords);
}


void CgSceneControl::renderRotationsBody()
{
    if(rotationbody){
        if(!rotationbody->getKeisVec().empty())
            if(rotationbody->getKeisVec().size()>0){
                for(unsigned int i = 0; i<rotationbody->getKeisVec().size();i++){
                    m_renderer->setUniformValue("mamp",glm::vec4(1.,1.,1.,1.));
                    m_renderer->render(rotationbody->getKeisVec().at(i),old);
                }
            }
        if(!rotationbody->getPolyVec().empty()){
            if(rotationbody->getPolyVec().size()>0){
                for(unsigned int i = 0; i<rotationbody->getPolyVec().size();i++){
                    m_renderer->setUniformValue("mamp",glm::vec3(1.,1.,1.));
                    m_renderer->render(rotationbody->getPolyVec().at(i),old);
                }
            }
        }
        if(!rotationbody->getNormale().empty()){
            if(rotationbody->getNormale().size()>0){
                for(unsigned int i = 0; i<rotationbody->getNormale().size();i++){
                    m_renderer->setUniformValue("mamp",glm::vec3(255.,2.,3.));
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
        for(unsigned int i =0; i<wuerfel->getGeraden().size();i++){
            m_renderer->render(wuerfel->getGeraden().at(i),old);
        }
    }
}

void CgSceneControl::renderCoords()
{

    koordinatensystem=new Koordinatensystem(m_renderer,m_current_transformation);
    koordinatensystem->renderO();
}


void CgSceneControl::renderDreiecke()
{
    if(dreiecke){
        m_renderer->render(dreiecke,old);
        if(!dreiecke->getGeraden().empty()){
            for(unsigned int i=0; i<dreiecke->getGeraden().size();i++){
                m_renderer->render(dreiecke->getGeraden().at(i),old);
            }
        }
    }
}

void CgSceneControl::renderObjects() {


    m_renderer->setProjectionMatrix(m_proj_matrix);
    m_renderer->setLookAtMatrix(cam->getLookAt());
    m_renderer->redraw();
    renderCoords();
    renderWurfel();
    renderRotationsBody();
    renderDreiecke();
    renderKegel();
    renderZylinder();
    pfeil = new Pfeil(m_renderer,new Appearance("mamb",glm::vec4(1,0,2,1)),old);
    pfeil->render();

    if(sc!=NULL){
        sc->render(m_renderer,sc->getSc());
    }
    m_renderer->redraw();
}
void CgSceneControl::reset(){
    if(dreiecke!=NULL){delete dreiecke;
        dreiecke=NULL;}
    if(rotationbody!=NULL){
        delete rotationbody;
        rotationbody=NULL;
    }
    //objecte.clear();
    changed=1;
    if(sc!=NULL){
        delete sc;
        sc=NULL;
    }
    if(wuerfel!=NULL){
        delete wuerfel;
        wuerfel=NULL;
    }
    if(kugel!=NULL){
        delete kugel;
        kugel=NULL;
    }
    if(zylinder!=NULL){
        delete zylinder;
        zylinder=NULL;
    }
    if(kegel!=NULL){
        delete zylinder;
        zylinder=NULL;
    }

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
        for(unsigned int i=0;i<=e->getChildren().size()-1;i++){
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
        for(unsigned int i=0;i<=e->getChildren().size()-1;i++){
            r->render(e->getChildren().at(i)->getOb(),e->getChildren().at(i)->getTransformation());
            if(!e->getChildren().at(i)->getChildren().empty()){
                drawSceneGraph(r,e->getChildren().at(i));
            }
        }
    }
}

glm::mat4x4 CgSceneControl::transform(glm::vec3 k,float winkely,float winkelz,float wunschwinkel)
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
        reset();
        glm::vec3 colors=((allgemeinesEvent*) e)->getTraegerKlasse()->getDreiDVector();
        delete wuerfel;
        wuerfel=NULL;
        wuerfel = MeshFactory::createWuerfel(colors);
    }

}

void CgSceneControl::renderKegel()
{
    if(kegel){
        m_renderer->render(kegel,old);
        for(unsigned int i=0;i< kegel->getGeraden().size();i++){

            m_renderer->render(kegel->getGeraden().at(i),old);
        }


    }
}

void CgSceneControl::initKegel()
{
    if(kegel){
        m_renderer->init(kegel);
        for(unsigned int j=0; j<kegel->getGeraden().size();j++){
            m_renderer->init(kegel->getGeraden().at(j));
        }
    }
}

void CgSceneControl::changeKegel(CgBaseEvent *e)
{
    if (e->getType() == Cg::KegelChange){
        reset();
        traeger = ((allgemeinesEvent*) e)->getTraegerKlasse();

        float hoehe = traeger->getDreiDVector().x;
        float radius = traeger->getDreiDVector().y;
        float refine = traeger->getDreiDVector().z;
        kegel = MeshFactory::createKegel(refine,hoehe,radius,shownormals);
        //kegel->setAppear(k);
        //resetRenderKegel(refine,hoehe,radius);
        initKegel();
    }
}

void CgSceneControl::setLight()
{
    m_renderer->setUniformValue("adir",light->getAdir());
    m_renderer->setUniformValue("aspec",light->getAspec());
    m_renderer->setUniformValue("adif",light->getAdif());
    m_renderer->setUniformValue("aamb",light->getAamb());
}

void CgSceneControl::setZylinderColor()
{
    m_renderer->setUniformValue("mamb",zylinder->getAppear()->getMaterial()->getAmb());
    m_renderer->setUniformValue("mdif",zylinder->getAppear()->getMaterial()->getDef());
    m_renderer->setUniformValue("mspec",zylinder->getAppear()->getMaterial()->getSpec());
    m_renderer->setUniformValue("mshine",zylinder->getAppear()->getMaterial()->getScalar());

}

void CgSceneControl::renderZylinder()
{
    if(zylinder!=NULL){

        setZylinderColor();
        m_renderer->render(zylinder,old);
        if(!zylinder->getGeraden().empty()){

            for(unsigned int j=0; j<zylinder->getGeraden().size();j++){
                m_renderer->render(zylinder->getGeraden().at(j),old);
            }
        }
    }
}

void calc(){

}

void CgSceneControl::initZylinder()
{
    if(zylinder!=NULL){
        m_renderer->init(zylinder);
        if(!zylinder->getGeraden().empty())
            for(unsigned int j=0; j<zylinder->getGeraden().size()-1;j++){
                m_renderer->init(zylinder->getGeraden().at(j));
            }
    }
}

void CgSceneControl::changeZylinder(CgBaseEvent *e)
{
    if(e->getType() == Cg::ZylinderChange){
        reset();
        traeger = ((allgemeinesEvent*) e)->getTraegerKlasse();

        float hoehe = traeger->getDreiDVector().x;
        float radius = traeger->getDreiDVector().y;
        float refine = traeger->getDreiDVector().z;
        Appearance* k;
        if(zylinder==NULL){
            k = new Appearance();
            k->getMaterial()->setAmb(glm::vec4(.1,.1,.1,1));
            k->getMaterial()->setDef(glm::vec4(.1,.1,.1,1));
            k->getMaterial()->setSpec(glm::vec4(.1,.1,.1,1));
            k->getMaterial()->setScalar(25);
        }
        else{
            k = zylinder->getAppear();
        }
        zylinder = zylinder = MeshFactory::createZylinder(refine,hoehe,radius,shownormals);
        zylinder->setAppear(k);

        //resetRenderKegel(refine,hoehe,radius);
        initZylinder();
    }



}


void CgSceneControl::changeRefineRota(CgBaseEvent *e)
{
    if(e->getType() == Cg::CgChangeRota){
        unsigned int refine= ((allgemeinesEvent*)e)->getTraegerKlasse()->getDreiDVector().x;
        unsigned int hoehe= ((allgemeinesEvent*)e)->getTraegerKlasse()->getDreiDVector().y;
        rotationbody= MeshFactory::createRotationKoerper(refine,hoehe,false,shownormals);
        initRotationBody();
        renderRotationsBody();

    }
}

void CgSceneControl::handleKeyY()
{
    old=old*rotationY(y);
    if(y==3){
        y=0;
    }
    else{
        y=y+.5;
    }


}

void CgSceneControl::handleKeyX()
{
    std::cout<<"taste x"<<std::endl;
    old=old*rotationX(x);
    if(x==3){
        x=0;
    }
    else{
        x=x+0.5;
    }


}

void CgSceneControl::handleKeyZ()
{
    old=old*rotationZ(z);
    if(z==3){
        z=0;
    }

    //1 0 0 -4
    //0 1 0 0
    //0 0 1 0
    //0 0 0 1
    else{
        z=z+0.5;
    }


}

void CgSceneControl::handleKeyMinus()
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

void CgSceneControl::handleKeyPlus()
{

    if(s>0.9){
        s=0.9;
    }else{
        s=s+0.02;
    }


    calculateNewTransformation(verschiebung);

    if(sc){
        sc->getSc()->setTransformation(glm::mat4x4(          glm::vec4(s,0,0,0),
                                                             glm::vec4(0,s,0,0),
                                                             glm::vec4(0,0,s,0),
                                                             glm::vec4(0,0,0,1)));
    }

}

void CgSceneControl::handleKeyD()
{

    countA+=.1;
    cam->strafePLUS(countA);

}

void CgSceneControl::handleKeyA()
{
    countA-=.1;
    cam->strafeMINUS((-1)*countA);
}

void CgSceneControl::handleKeyW()
{
    countW+=.1;
    cam->towardPLUS(countW);
}

void CgSceneControl::handleKeyS()
{
    countW-=.1;
    cam->towardMINUS((-1)*countW);
}

void CgSceneControl::handleKeyU()
{
    cam->rotateMinus();
}

void CgSceneControl::handleKeyI()
{
    cam->rotatePlus();
}

void CgSceneControl::handleKeyEvents(CgBaseEvent*e)
{
    switch(((CgKeyEvent*)e)->key()){
    case Cg::Key_Y:handleKeyY();
        break;
    case Cg::Key_X:handleKeyX();
        break;
    case Cg::Key_Z:handleKeyZ();
        break;
    case Cg::Key_Minus : handleKeyMinus();
        break;
    case Cg::Key_Plus:handleKeyPlus();
        break;
    case Cg::Key_D:handleKeyD();
        break;
    case Cg::Key_A:handleKeyA();
        break;
    case Cg::Key_W:handleKeyW();
        break;
    case Cg::Key_S:handleKeyS();
        break;
    case Cg::Key_U:handleKeyU();
        break;
    case Cg::Key_I:handleKeyI();
        break;
    default:
        break;
    }
}

void CgSceneControl::changeRota(CgBaseEvent *e)
{
    if(e->getType()==Cg::CgChangeRota){
        float x =((allgemeinesEvent*)e)->getTraegerKlasse()->getIntvec().x/10;
        float y =((allgemeinesEvent*)e)->getTraegerKlasse()->getIntvec().y/10;
        float z =((allgemeinesEvent*)e)->getTraegerKlasse()->getIntvec().z/10;
        verschiebung = glm::vec3(x,y,z);
        old = transform(verschiebung,10,20,30);
        x=true;
    }
}

void CgSceneControl::windowresize(CgBaseEvent *e)
{
    if (e->getType() == Cg::WindowResizeEvent) {
        CgWindowResizeEvent *ev = (CgWindowResizeEvent *) e;
        m_proj_matrix = glm::perspective(45.0f, (float) (ev->w()) / ev->h(), 0.01f, 100.0f);

    }
}

void CgSceneControl::changePage(CgBaseEvent *e)
{

    if(e->getType()==Cg::TabChange){
        page =((allgemeinesEvent*)e)->getTraegerKlasse()->getTab();
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
        dreiecke = new Dreiecke();
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
        dreiecke = objecte.at(((allgemeinesEvent*)e)->getTraegerKlasse()->getAn_aus());
        //   dreiecke = objecte.at(((ObjectOpenEvent*) e)->getWahl());
        if(!dreiecke->getGeraden().empty()){
            for(unsigned int i=0; i<dreiecke->getGeraden().size();i++){
                m_renderer->init(dreiecke->getGeraden().at(i));
            }
        }
        this->m_renderer->init(dreiecke);
        renderDreiecke();
        this->m_renderer->redraw();


    }
}

void CgSceneControl::handleMaterial(CgBaseEvent *e)
{
    if(e->getType()==Cg::CgChangeMaterial){
        glm::vec4 ding1 =((allgemeinesEvent*)e)->getTraegerKlasse()->getAmb();
        glm::vec4 ding2 =((allgemeinesEvent*)e)->getTraegerKlasse()->getDef();
        glm::vec4 ding3 =((allgemeinesEvent*)e)->getTraegerKlasse()->getSpec();
        double ding4 =((allgemeinesEvent*)e)->getTraegerKlasse()->getScala();

        std::string st = ((allgemeinesEvent*)e)->getTraegerKlasse()->getName().toStdString();
        Appearance* k = new Appearance();
        Mats* ma =new Mats();
        ma->setAmb(ding1);
        ma->setDef(ding2);
        ma->setSpec(ding3);
        ma->setScalar(ding4);
        k->setMaterial(ma);
        if(st.compare("Zylinder")==0){
            delete zylinder;
            zylinder=NULL;
            zylinder = MeshFactory::createZylinder(10,10,10,false);
            zylinder->setAppear(k);
            m_renderer->init(zylinder);
            renderZylinder();
        }
        if(st.compare("Stern")==0 ||st.compare("Mond")==0 || st.compare("Mond2")==0
                || st.compare("Erde")==0 || st.compare("Planet1")==0 || st.compare("Planet2")==0 || st.compare("Mond1")==0){
            if(sc==NULL){
                createScene();
            }

            if(st.compare("Stern")==0){
                std::cout<<"sdad"<<std::endl;
                sc->findAndSetAppear(k,Cg::Stern);
            }
            if(st.compare("Erde")==0){
                sc->findAndSetAppear(k,Cg::Erde);
            }
            if(st.compare("Mond1")==0){
                sc->findAndSetAppear(k,Cg::Mond1);
            }
            if(st.compare("Mond2")==0){
                sc->findAndSetAppear(k,Cg::Mond2);
            }
            if(st.compare("Mond2")==0){
                sc->findAndSetAppear(k,Cg::Mond3);
            }
            if(st.compare("Planet1")==0){
                sc->findAndSetAppear(k,Cg::Planet1);
            }
            if(st.compare("Planet2")==0){
                sc->findAndSetAppear(k,Cg::Planet2);
            }
            sc->render(m_renderer,sc->getSc());
        }

    }

}



void CgSceneControl::testeMatrizen(CgBaseEvent *e)
{
    if(e->getType()==Cg::CgMatritzeChecken){
        glm::mat4 standart = glm::mat4(glm::vec4(1,0,0,0),glm::vec4(0,1,0,0),glm::vec4(0,0,1,0),glm::vec4(0,0,0,1));
        std::cout << "asdasd"<<std::endl;
        glm::vec3 ankle = glm::vec3(30.0,20.0,40.0);
        glm::mat4 trans;
        trans = glm::rotate(trans, glm::radians(30.0f), glm::vec3(1.0, 0.0, 0.0));
        trans = glm::rotate(trans, glm::radians(20.0f), glm::vec3(0.0, 1.0, 0.0));
        trans = glm::rotate(trans, glm::radians(40.0f), glm::vec3(0.0, 0.0, 1.0));
        glm::mat4 j = standart *rotationX(30.)*rotationY(20.)*rotationZ(40.);

        for(float i= 1000000.0 ; i>10.0 ; i=i+1000.0){
            if(!compateMat(trans,j,1/i)){
                std::cout <<"beide matrizen gleich bis zu einem epsilon von "<<(1/i)<<std::endl;
                i=0.0;
                break;
            }
        }

        glm::mat4 trans2;
        trans2 = glm::rotate(trans2, glm::radians(-11.0f), glm::vec3(1.0, 0.0, 0.0));
        trans2 = glm::rotate(trans2, glm::radians(4.f), glm::vec3(0.0, 1.0, 0.0));
        trans2 = glm::rotate(trans2, glm::radians(-0.1f), glm::vec3(0.0, 0.0, 1.0));
        j = standart *rotationX(-11.)*rotationY(4.)*rotationZ(-.1f);
        for(float i= 1000000.0 ; i>10.0 ; i=i+1000.0){
            if(!compateMat(trans2,j,1/i)){
                std::cout <<"beide matrizen gleich bis zu einem epsilon von "<<(1/i)<<std::endl;
                i=0.0;
                break;
            }
        }

    }
}

void CgSceneControl::handleLightChange(CgBaseEvent *e)
{
    if(e->getType()==Cg::CgTurnLightOnOff){
        lighton=!lighton;

        if(lighton){

            m_renderer->setShaderSourceFiles("../UebungSS2018/CgShader/phong/phong.vert","../UebungSS2018/CgShader/phong/phong.frag");
            light = new Light();
            light->setAamb(glm::vec4(1.0,1.0,1.0,1.));
            light->setAdir(glm::vec3(0.,4.,1.));
            light->setAdif(glm::vec4(0.3,0.2,.5,1.0));
            light->setAspec(glm::vec4(1.0,1.0,1.0,1.0));
            setLight();
            initZylinder();
            renderZylinder();

        }
        else{
            if(light!=NULL){
                delete light;
                light=NULL;
            }
            m_renderer->setShaderSourceFiles("../UebungSS2018/CgShader/lightsoff.vert","../UebungSS2018/CgShader/lightsoff.frag");
            renderZylinder();
        }

    }
}

void CgSceneControl::handleEvent(CgBaseEvent *e) {
    if (e->getType() == Cg::CgKeyEvent) {
        CgKeyEvent *ev = (CgKeyEvent *) e;
        handleKeyEvents(ev);

        // hier kommt  jetzt die Abarbeitung des Events hin...
    }

    // die Enums sind so gebaut, dass man alle Arten von MausEvents über CgEvent::CgMouseEvent abprüfen kann,
    // siehe dazu die CgEvent enums im CgEnums.h
    if (e->getType() == Cg::CgMouseEvent) {
        // hier kommt jetzt die Abarbeitung des Events hin...
    }
    testeMatrizen(e);

    //setDreiDVector
    if(e->getType()==Cg::CgChangeLichtFarbe){
        if(lighton){
            glm::vec3 c = ((allgemeinesEvent*)e)->getTraegerKlasse()->getDreiDVector();
            glm::vec4 d = glm::vec4(c.x,c.y,c.z,1);
            light->setAamb(d);
        }

    }


    if(e->getType()==Cg::CgChangeLichtPosition){
        if(lighton){

            glm::vec3 c = ((allgemeinesEvent*)e)->getTraegerKlasse()->getDreiDVector();
            light->setAdir(c);
            setLight();
        }


    }

    handleLightChange(e);

    if(e->getType()== Cg::CgZeigeNormalePage2){
        shownormals=!shownormals;
        if(kegel!=NULL){
            kegel->setNormalsberechnen(shownormals);
            initKegel();
        }
        if(zylinder!=NULL){
            zylinder->setNormalsberechnen(shownormals);
            initZylinder();
        }
        else{
            std::cout<<"MUH!"<<std::endl;
        }

    }
    handleMaterial(e);
    if(e->getType()==Cg::CgZeigeSonnenSystem){
        createScene();
    }

    if(e->getType()==Cg::CgZeigePolyline){
        this->rotationbody=MeshFactory::createRotationKoerper(1,1,true,false);
        initRotationBody();
    } if(e->getType()==Cg::CgResetPolyline){
        delete rotationbody;
        this->rotationbody=NULL;
    }
    if(e->getType()==Cg::CgLaneRefine){
        delete rotationbody;
        this->rotationbody=NULL;
        int x = ((allgemeinesEvent*)e)->getTraegerKlasse()->getDreiDVector().x;
        std::cout<<x<<std::endl;
        this->rotationbody=MeshFactory::createRotationKoerper(1,x,true,false);
        initRotationBody();
    }
    if(e->getType()==Cg::CgChangeRota){
        delete rotationbody;
        this->rotationbody=NULL;
        int x = ((allgemeinesEvent*)e)->getTraegerKlasse()->getDreiDVector().x;
        int k = ((allgemeinesEvent*)e)->getTraegerKlasse()->getDreiDVector().y;
        std::cout<<x<<std::endl;
        std::cout<<k<<std::endl;
        this->rotationbody=MeshFactory::createRotationKoerper(x,k,false,false);
        initRotationBody();
    }


    // die Enums sind so gebaut, dass man alle Arten von KeyEvents über CgEvent::CgKeyEvent abprüfen kann,
    // siehe dazu die CgEvent eolynums im CgEnums.h
    // momentan werden nur KeyPressEvents gefangen.


    changePage(e);
    windowresize(e);
    //(int refine,float hoehe,float radius)
    changeColorCube(e);
    changeKegel(e);
    changeZylinder(e);
    changeRefineRota(e);
    changeRota(e);
    handleKeyEvents(e);
    loadObject(e);
    changeObjectRota(e);
    changeObjectTranslate(e);
    changeTageswert(e);
    // an der Stelle an der ein Event abgearbeitet ist wird es auch gelöscht.
    delete e;

}

void CgSceneControl::changeTageswert(CgBaseEvent* e){
    if(e->getType()==Cg::CgChangeTageswert){
        if(((allgemeinesEvent*)e)->getTraegerKlasse()->getAn_aus()==1){
            sc->setCounterIncre(sc->getCounterIncre()+2);
            std::cout<<"erhöht "<<sc->getCounterIncre()<<std::endl;
        }else{
            if(sc->getCounterIncre()<3){

            }else{
                sc->setCounterIncre(sc->getCounterIncre()-2);
                            std::cout<<"verringert "<<sc->getCounterIncre()<<std::endl;
            }
        }

    }

}

void CgSceneControl::changeObjectRota(CgBaseEvent* e){
    if(e->getType()==Cg::CgObjRotate){
        glm::vec3 a = ((allgemeinesEvent*)e)->getTraegerKlasse()->getDreiDVector();
        x = a.x;
        y = a.y;
        z = a.z;
        old = old * rotationX(x);// * rotationY(y) * rotationZ(z) * rotationX(-x) * rotationY(-y);
        old = old * rotationY(y);
        old = old * rotationZ(z);
    }

}

void CgSceneControl::changeObjectTranslate(CgBaseEvent* e){
    if(e->getType()==Cg::CgObjTranslate){
        glm::vec3 a = ((allgemeinesEvent*)e)->getTraegerKlasse()->getDreiDVector();
        old = transform(a,0,0,0);

    }



}


void CgSceneControl::page1(){
    //würfel
    reset();

}
void CgSceneControl::page2(){
    reset();
}
void CgSceneControl::page3(){
    reset();
    std::cout<<"tyra porsche"<<std::endl;
}
void CgSceneControl::page4(){
    reset();
    std::cout<<"sonnensystem"<<std::endl;
}
void CgSceneControl::page5(){

}
void CgSceneControl::resetAll(){
    delete sc;
    sc=NULL;
    delete dreiecke;
    dreiecke=NULL;
    wuerfel=NULL;
    delete wuerfel;

}
void CgSceneControl::renew(){

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

bool CgSceneControl::compateMat(const glm::mat4& x, const glm::mat4& y, float epsilon){
    glm::vec4 x1 = x[0];
    glm::vec4 x2 = x[1];
    glm::vec4 x3 = x[2];
    glm::vec4 x4 = x[3];

    glm::vec4 y1 = y[0];
    glm::vec4 y2 = y[1];
    glm::vec4 y3 = y[2];
    glm::vec4 y4 = y[3];
    return compateVec4(x1,y1,epsilon) && compateVec4(x2,y2,epsilon) && compateVec4(x3,y3,epsilon) && compateVec4(x4,y4,epsilon);
}
bool CgSceneControl::compateVec4(const glm::vec4& x, const glm::vec4& y,float epsilon){
    float a = x.x;
    float b = x.y;
    float c = x.z;
    float d = x.w;

    float e = y.x;
    float f = y.y;
    float g = y.z;
    float h = y.w;
    return compateFloat(a,e,epsilon) && compateFloat(b,f,epsilon) && compateFloat(c,g,epsilon) && compateFloat(d,h,epsilon);

}

bool CgSceneControl::compateFloat(float x, float y,float epsilon){
    if(y==x) return true;
    return glm::abs(x-y) <epsilon;
}
