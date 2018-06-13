#ifndef CGSCENECONTROL_H
#define CGSCENECONTROL_H

#include "CgBase/CgObserver.h"
#include "CgBase/CgBaseSceneControl.h"
#include <glm/glm.hpp>
#include <CgBase/CgBaseTriangleMesh.h>
#include "CgClass/rotationskoerper.h"
#include "CgClass/koordinatensystem.h"
#include "CgClass/kugel.h"
#include "CgClass/scenegraph.h"
#include "CgClass/kamera.h"
#include "CgClass/traegerklasse.h"
#include "CgClass/pfeil.h"
class CgBaseEvent;
class CgBaseRenderer;
class CgExampleTriangle;
class CgBaseTriangleMesh;
class Wuerfel;
class Zylinder;
class Kegel;

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
    glm::mat4x4 overallRotation(int x, int y, int z);
    void resetRenderKugel(int refine, float hoehe, float radius);
    glm::mat4x4 transform(glm::vec3 k, int winkely, int winkelz, int wunschwinkel);
    glm::mat4x4 transform(glm::vec3 k, float winkely, float winkelz, float wunschwinkel);
    void page1();
    void page2();
    void page3();
    void page4();
    void page5();
    void resetAll();
    void calculateNewTransformation(glm::vec3 verschiebung);
    void renderRotationsBody();

    void createScene();

    void createStandartMatrix();

    void initRotationBody();

    void renderWurfel();

    void changeColorCube(CgBaseEvent *e);

    void changeKegel(CgBaseEvent *e);

    void changeZylinder(CgBaseEvent *e);

    void changeRefineRota(CgBaseEvent *e);

    void handleKeyEvents(CgBaseEvent *e);

    void handleKeyY();

    void handleKeyX();

    void handleKeyZ();

    void handleKeyMinus();

    void handleKeyPlus();

    void handleKeyD();

    void handleKeyA();

    void handleKeyW();

    void handleKeyS();

    void handleKeyU();

    void handleKeyI();

    void changeRota(CgBaseEvent *e);

    void pushpop(CgBaseTriangleMesh* x);
    
    void windowresize(CgBaseEvent *e);

    void loadObject(CgBaseEvent *e);

    void renderCoords();
    
    void renderTriangle();
    
    void renderDreiecke();

    void openPage(CgBaseEvent *e);

    void scale();

    float getCountW() const;
    void setCountW(float value);

    float getCountA() const;
    void setCountA(float value);

    float getCountS() const;
    void setCountS(float value);

    float getCountD() const;
    void setCountD(float value);

    float getCountQ() const;
    void setCountQ(float value);

    float getCountE() const;
    void setCountE(float value);

    glm::vec3 getW() const;
    void setW(const glm::vec3 &value);

    glm::vec3 getV() const;
    void setV(const glm::vec3 &value);

    glm::vec3 getU() const;
    void setU(const glm::vec3 &value);

    glm::vec3 getEye() const;
    void setEye(const glm::vec3 &value);

    Kamera *getCam() const;
    void setCam(Kamera *value);

    glm::mat4 getOld() const;
    void setOld(const glm::mat4 &value);

    std::vector<Dreiecke *> getObjecte() const;
    void setObjecte(const std::vector<Dreiecke *> &value);

    CgBaseRenderer *getRenderer() const;

    Dreiecke *getDreiecke() const;
    void setDreiecke(Dreiecke *value);

    RotationsKoerper *getRotationbody() const;
    void setRotationbody(RotationsKoerper *value);

    std::vector<CgBaseTriangleMesh *> getTriangle() const;
    void setTriangle(const std::vector<CgBaseTriangleMesh *> &triangle);

    glm::mat4 getProj_matrix() const;
    void setProj_matrix(const glm::mat4 &proj_matrix);

    glm::mat4 getCurrent_transformation() const;
    void setCurrent_transformation(const glm::mat4 &current_transformation);

    MyPolyline *getRotaAchse() const;
    void setRotaAchse(MyPolyline *value);

    Wuerfel *getWuerfel() const;
    void setWuerfel(Wuerfel *value);

    Kugel *getKugel() const;
    void setKugel(Kugel *value);

    std::vector<glm::vec3> getDreickevertices() const;
    void setDreickevertices(const std::vector<glm::vec3> &value);

    Koordinatensystem *getKoordinatensystem() const;
    void setKoordinatensystem(Koordinatensystem *value);

    std::vector<unsigned int> getDreieckecords() const;
    void setDreieckecords(const std::vector<unsigned int> &value);

    float getS() const;
    void setS(float value);

    float getX() const;
    void setX(float value);

    float getY() const;
    void setY(float value);

    float getZ() const;
    void setZ(float value);

    void setChanged(int value);

    void checkKey(CgBaseEvent *e);

    Scenegraph *getSc() const;
    void setSc(Scenegraph *value);

    void changePage(CgBaseEvent *e);

    void renderZylinder();

    void renderKegel();

    void initZylinder();

    void initKegel();

    void materialChange(CgBaseEvent *e);
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
    bool shownormals;
    Pfeil* pfeil;
    Kamera* cam;
    glm::mat4 old;
    std::vector <Dreiecke*> objecte;
    CgBaseRenderer* m_renderer;
    Dreiecke* dreiecke;
    RotationsKoerper* rotationbody;
    //std::vector<CgBaseTriangleMesh*> zylinderOderKegel;
    Kegel* kegel;
    Zylinder* zylinder;
    glm::mat4 m_current_transformation;
    glm::mat4 m_proj_matrix;
    MyPolyline* rotaAchse;
    Wuerfel* wuerfel;
    float s;
    float x;
    float y;
    float z;
    int page;
    int changed;
    TraegerKlasse* traeger;
    Kugel * kugel;
    std::vector<glm::vec3> dreickevertices;
    Koordinatensystem* koordinatensystem;
    std::vector<unsigned int> dreieckecords;
    Scenegraph* sc;

    void renew();
};

#endif // CGSCENECONTROL_H
