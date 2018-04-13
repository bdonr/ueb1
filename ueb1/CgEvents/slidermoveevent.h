#ifndef SLIDERMOVEEVENT_H
#define SLIDERMOVEEVENT_H
#include "../CgBase/CgBaseEvent.h"
#include <glm/glm.hpp>W

class SliderMoveEvent :public CgBaseEvent

{
public:

    SliderMoveEvent(enum Cg::EventType type, glm::vec3 x);
    ~SliderMoveEvent(){};
    SliderMoveEvent();

    Cg::EventType getType();
    CgBaseEvent* clone();
    glm::vec3 getFarbe();
private:

    enum Cg::EventType type;
    glm::vec3 farbe;


};


#endif // SLIDERMOVEEVENT_H
