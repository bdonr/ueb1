#ifndef SLIDERMOVEEVENT_H
#define SLIDERMOVEEVENT_H
#include "../CgBase/CgBaseEvent.h"
#include <glm/glm.hpp>
#include <CgBase/CgBaseTriangleMesh.h>

class SliderMoveEvent: public CgBaseEvent
{
private:
    enum Cg::EventType type;
    int refine;
     float hoehe;
    float radius;


public:

     SliderMoveEvent();
     SliderMoveEvent(enum Cg::EventType type,int x);
     SliderMoveEvent(enum Cg::EventType type, int refine,float hoehe,float radius);
    Cg::EventType getType();
    CgBaseEvent *clone();
    int getRefine();
    float getRadius();
    float getHoehe();
};

#endif // SLIDERMOVEEVENT_H
