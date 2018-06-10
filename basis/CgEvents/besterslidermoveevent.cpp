#include "besterslidermoveevent.h"



bestersliderMoveEvent::bestersliderMoveEvent(enum Cg::EventType type, TraegerKlasse *traegerKlasse):type(type),traegerKlasse(traegerKlasse)
{

}

TraegerKlasse *bestersliderMoveEvent::getTraegerKlasse() const
{
    return traegerKlasse;
}

void bestersliderMoveEvent::setTraegerKlasse(TraegerKlasse *value)
{
    traegerKlasse = value;
}

Cg::EventType bestersliderMoveEvent::getType()
{
    return type;
}

CgBaseEvent *bestersliderMoveEvent::clone()
{
    return new bestersliderMoveEvent(type,traegerKlasse);
}

