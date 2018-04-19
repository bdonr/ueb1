#include "buttonevent.h"

ButtonEvent::ButtonEvent():type(Cg::addBothButton)
{

}

ButtonEvent::ButtonEvent(enum Cg::addBothButton x){
    this->type=x;
}

// CgBaseEvent interface
Cg::ObjectType ButtonEvent::getType(){

}

CgBaseEvent *ButtonEvent::clone(){
    return new ButtonEvent(this->type);
}

