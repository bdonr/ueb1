#ifndef MESHFACTORY_H
#define MESHFACTORY_H
#include <CgBase/CgBaseTriangleMesh.h>
#include <CgBase/CgBasePolyline.h>
#include "CgClass/Mypolyline.h"
#include "CgClass/rotationskoerper.h"
#include "CgClass/dreiecke.h"
#include "CgClass/kugel.h"
#include "CgClass/wuerfel.h"
class RotationsKoerper;
class Kugel;
class Wuerfel;
class Kegel;
class Zylinder;
class MeshFactory
{

private: int id;
    static int all_id;
public:
    MeshFactory();
    static Wuerfel* createWuerfel(glm::vec3 colors);
    static Zylinder* createZylinder(int refine,float hoehe,float radius,bool berechnenormale);
    static Kegel* createKegel(int refine,float hoehe,float radius,bool berechnenormale);
    static MyPolyline* createMyPolyline(glm::vec3 color,std::vector<glm::vec3> x);

    static RotationsKoerper* createRotationKoerper(int refine,int hoehe);
    static Dreiecke * createDreiecke(std::vector<glm::vec3>x,std::vector<unsigned int>k);
    static Kugel *createKugel(float radius, float hoehe, int refine);
    static RotationsKoerper *createRotationKoerper(int refine, int hoehe, bool showline, bool shownormals);
};
#endif // MESHFACTORY_H
