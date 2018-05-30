#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H
#include <CgBase/CgBaseEvent.h>
#include <CgSceneGraph/CgSceneControl.h>
#include <CgEvents/CgKeyEvent.h>
class EventHandler
{

private: CgBaseEvent *e;
    CgSceneControl* sc;

public:
    EventHandler(CgBaseEvent *e,CgSceneControl sc);
    void changeColorCube(CgBaseEvent *e);

    void changeKegel(CgBaseEvent *e);

    void changeZylinder(CgBaseEvent *e);

    void changeKugel(CgBaseEvent *e);

    void changeRefineRota(CgBaseEvent *e);

    void handleKeyEvents(CgKeyEvent *e);

    void handleKeyY(CgKeyEvent *e);

    void handleKeyX(CgKeyEvent *e);

    void handleKeyZ(CgKeyEvent *e);

    void handleKeyMinus(CgKeyEvent *e);

    void handleKeyPlus(CgKeyEvent *e);

    void handleKeyD(CgKeyEvent *e);

    void handleKeyA(CgKeyEvent *e);

    void handleKeyW(CgKeyEvent *e);

    void handleKeyS(CgKeyEvent *e);

    void handleKeyU(CgKeyEvent *e);

    void handleKeyI(CgKeyEvent *e);

    void changeROta(CgBaseEvent *e);

    checkKey();

};

#endif // EVENTHANDLER_H
