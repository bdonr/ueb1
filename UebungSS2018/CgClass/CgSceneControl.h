#ifndef CGSCENECONTROL_H
#define CGSCENECONTROL_H

#include "CgBase/CgObserver.h"
#include "CgBase/CgBaseSceneControl.h"
#include <glm/glm.hpp>
#include <CgBase/CgBaseTriangleMesh.h>
#include "CgBase/CgBaseTriangleMesh.h"
#include "rotationskoerper.h"
#include "koordinatensystem.h"
#include "kugel.h"
#include "scenegraph.h"
#include "kamera.h"
class CgBaseEvent;
class CgBaseRenderer;
class CgExampleTriangle;
class Wuerfel;

class CgSceneControl : public CgObserver, public CgBaseSceneControl
{
public:
    CgSceneControl();
    ~CgSceneControl();
    void handleEvent(CgBaseEvent* e);
    void setRenderer(CgBaseRenderer* r);
    void resetRenderKegel(int refine,float hoehe,float radius);
    void resetRenderZylinder(int refine,float hoehe,float radius);
    void renderObjects();
    void resetObject();
    void reset();
    int getChanged();
    glm::mat4x4 rotationX(int winkelx);
    glm::mat4x4 rotationY(int winkely);
    glm::mat4x4 rotationZ(int winkelz);
    glm::mat4x4 transform(glm::vec3 k);
    void registerSceneGraph(CgBaseRenderer* r,SceneEntity* e);
    void drawSceneGraph(CgBaseRenderer* r,SceneEntity* e);

    glm::vec3 verschiebung;
    glm::mat4x4 translatetoVectot(glm::vec3 k);
    glm::mat4x4 allgemineRotation(int x, int y, int z);
    void resetRenderKugel(int refine, float hoehe, float radius);
    glm::mat4x4 transform(glm::vec3 k, int winkely, int winkelz, int wunschwinkel);
    glm::mat4x4 transform(glm::vec3 k, float winkely, float winkelz, float wunschwinkel, float skala);
    void tab1constructor();
    void tab2constructor();
    void tab3constructor();
    void tab4constructor();
    void tab5constructor();
    void resetAll();
private:
    int tab;
    glm::vec3 w;
    glm::vec3 v;
    glm::vec3 u;
    glm::vec3 eye;

    float countW;
    float countA;
    float countS;
    float countD;
    float countQ;
    float countE;


    Kamera* cam;
    glm::mat4 old;
    std::vector <Dreiecke*> objecte;
    CgBaseRenderer* m_renderer;
    Dreiecke* dreiecke;
    RotationsKoerper* poly;
    std::vector<CgBaseTriangleMesh*> m_triangle;
    glm::mat4 m_current_transformation;
    glm::mat4 m_proj_matrix;
    MyPolyline* rotaAchse;
    Wuerfel* wuerfel;
    float s;
    float x;
    float y;
    float z;
    int changed;

    Kugel * kugel;
    std::vector<glm::vec3> dreickevertices;
    Koordinatensystem* koordinatensystem;
    std::vector<unsigned int> dreieckecords;
    Scenegraph* sc;

    void renew();
};

#endif // CGSCENECONTROL_H
