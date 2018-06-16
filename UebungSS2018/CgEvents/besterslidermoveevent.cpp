#include "besterslidermoveevent.h"



allgemeinesEvent::allgemeinesEvent(enum Cg::EventType type, TraegerKlasse *traegerKlasse):type(type),traegerKlasse(traegerKlasse)
{

}

TraegerKlasse *allgemeinesEvent::getTraegerKlasse() const
{
    return traegerKlasse;
}

void allgemeinesEvent::setTraegerKlasse(TraegerKlasse *value)
{
    traegerKlasse = value;
}

Cg::EventType allgemeinesEvent::getType()
{
    return type;
}

CgBaseEvent *allgemeinesEvent::clone()
{
    return new allgemeinesEvent(type,traegerKlasse);
}

