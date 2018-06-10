#include "objectopenevent.h"

ObjectOpenEvent::ObjectOpenEvent(int x):wahl(x),type(Cg::CgChangeWahl)
{

}
Cg::EventType ObjectOpenEvent::getType(){
    return this->type;
}
CgBaseEvent* ObjectOpenEvent::clone(){
    return new ObjectOpenEvent(this->wahl);

}
int ObjectOpenEvent::getWahl(){
    return wahl;
}

