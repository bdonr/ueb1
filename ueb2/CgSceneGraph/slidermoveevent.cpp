#include "slidermoveevent.h"

SliderMoveEvent::SliderMoveEvent()
{

}
SliderMoveEvent::SliderMoveEvent(enum Cg::EventType type, int wert):type(type),wert(wert){

}

Cg::EventType SliderMoveEvent::getType(){
    return type;
}

CgBaseEvent* SliderMoveEvent::clone(){
    return new SliderMoveEvent(this->type,this->wert);
}

int SliderMoveEvent::getWert(){
    return this->wert;
}
