#ifndef OBJECTOPENEVENT_H
#define OBJECTOPENEVENT_H
#include "../CgBase/CgBaseEvent.h"

class ObjectOpenEvent: public CgBaseEvent

{
public:
    ObjectOpenEvent(int x);

    // CgBaseEvent interface
public:
    Cg::EventType getType();
    int getWahl();
    CgBaseEvent *clone();
private:
    int wahl;
    enum Cg::EventType type;
};

#endif // OBJECTOPENEVENT_H
