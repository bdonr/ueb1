#ifndef BESTERSLIDERMOVEEVENT_H
#define BESTERSLIDERMOVEEVENT_H

#include "traegerklasse.h"
#include "CgBase/CgBaseEvent.h"
#include "CgBase/CgEnums.h"
class bestersliderMoveEvent : public CgBaseEvent
{

private: TraegerKlasse *traegerKlasse;
    enum Cg::EventType type;
public:
    bestersliderMoveEvent(enum Cg::EventType type,TraegerKlasse *traegerKlasse);
    TraegerKlasse *getTraegerKlasse() const;
    void setTraegerKlasse(TraegerKlasse *value);

    // CgBaseEvent interface

    enum Cg::EventType getType();
    CgBaseEvent *clone();
};

#endif // BESTERSLIDERMOVEEVENT_H
