#include "slidermoveevent.h"

SliderMoveEvent::SliderMoveEvent()
{

}
SliderMoveEvent::SliderMoveEvent(enum Cg::EventType type, int refine,float hoehe,float radius):type(type),refine(refine),hoehe(hoehe),radius(radius){

}

Cg::EventType SliderMoveEvent::getType(){
    return type;
}

CgBaseEvent* SliderMoveEvent::clone(){
    return new SliderMoveEvent(this->type,refine,hoehe,radius);
}
int SliderMoveEvent::getRefine(){
    return refine;
}

float SliderMoveEvent::getRadius(){
    return radius;
}

float SliderMoveEvent::getHoehe(){
    return hoehe;
}
