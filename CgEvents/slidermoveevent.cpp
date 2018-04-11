#include "slidermoveevent.h"

SliderMoveEvent::SliderMoveEvent(Cg::EventType type, glm::vec3 x){
    this->type = type;
    this->farbe =x;
}
SliderMoveEvent::SliderMoveEvent():type(Cg::Arschgeburt),farbe(glm::vec3(0,0,0)){

}

Cg::EventType SliderMoveEvent::getType(){
    return type;
}

glm::vec3 SliderMoveEvent::getFarbe(){
    return farbe;
}


CgBaseEvent* SliderMoveEvent::clone()
{
    return new SliderMoveEvent(this->type,this->farbe);
}

