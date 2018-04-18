#ifndef SLIDERMOVEEVENT_H
#define SLIDERMOVEEVENT_H
#include "../CgBase/CgBaseEvent.h"
#include <glm/glm.hpp>
#include <CgBase/CgBaseTriangleMesh.h>

class SliderMoveEvent: public CgBaseEvent
{
private:
    enum Cg::EventType type;
    int wert;

public:
     SliderMoveEvent();
     SliderMoveEvent(enum Cg::EventType type, int wert);
    Cg::EventType getType();
    CgBaseEvent *clone();
    int getWert();
};

#endif // SLIDERMOVEEVENT_H
