#ifndef BUTTONEVENT_H
#define BUTTONEVENT_H
#include <CgBase/CgBaseEvent.h>
class ButtonEvent:public CgBaseEvent

{

private:
    enum Cg::ObjectType type;
public:
    ButtonEvent();
    ButtonEvent(enum Cg::ObjectType x);
    // CgBaseEvent interface
    enum Cg::ObjectType getType();
    CgBaseEvent *clone();
};

#endif // BUTTONEVENT_H

