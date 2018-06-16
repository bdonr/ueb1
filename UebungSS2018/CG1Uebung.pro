QT       += core gui opengl widgets

TEMPLATE = app

TARGET = uebung1

SOURCES += main.cpp \
    CgQtViewer/CGQtGLRenderWidget.cpp \
    CgQtViewer/CgQtGui.cpp \
    CgBase/CgObservable.cpp \
    CgEvents/CgMouseEvent.cpp \
    CgQtViewer/CgQtMainApplication.cpp \
    CgSceneGraph/CgSceneControl.cpp \
    CgEvents/CgKeyEvent.cpp \
    CgQtViewer/CgQtGlBufferObject.cpp \
    CgQtViewer/CgTrackball.cpp \
    CgEvents/CgWindowResizeEvent.cpp \
    CgClass/meshfactory.cpp \
    CgClass/Zylinder.cpp \
    CgClass/kegel.cpp \
    CgClass/Mypolyline.cpp \
    CgEvents/slidermoveevent.cpp \
    CgClass/rotationskoerper.cpp \
    CgUtils/ObjLoader.cpp \
    CgClass/koordinatensystem.cpp \
    CgEvents/objectopenevent.cpp \
    CgClass/kugel.cpp \
    CgEvents/besterslidermoveevent.cpp \
    CgClass/traegerklasse.cpp \
    CgClass/scenegraph.cpp \
    CgClass/sceneentity.cpp \
    CgClass/appearance.cpp \
    CgClass/kamera.cpp \
    CgClass/wuerfel.cpp \
    CgClass/dreiecke.cpp \
    CgClass/mats.cpp \
    CgClass/pfeil.cpp \
    CgClass/virtCam.cpp \
    CgSceneGraph/CgCamera.cpp


HEADERS += \
    CgBase/CgBaseRenderWindow.h \
    CgQtViewer/CgQtGLRenderWidget.h \
    CgQtViewer/CgQtGui.h \
    CgBase/CgObserver.h \
    CgBase/CgObservable.h \
    CgBase/CgBaseEvent.h \
    CgBase/CgEnums.h \
    CgEvents/CgMouseEvent.h \
    CgQtViewer/CgQtMainApplication.h \
    CgSceneGraph/CgSceneControl.h \
    CgEvents/CgKeyEvent.h \
    CgBase/CgBaseRenderer.h \
    CgBase/CgBaseRenderableObject.h \
    CgBase/CgBasePointCloud.h \
    CgBase/CgBaseTriangleMesh.h \
    CgBase/CgBasePolygonMesh.h \
    CgBase/CgBasePolyline.h \
    CgBase/CgBaseSceneControl.h \
    CgQtViewer/CgQtGlBufferObject.h \
    CgQtViewer/CgTrackball.h \
    CgEvents/CgWindowResizeEvent.h \
    CgClass/meshfactory.h \
    CgClass/Zylinder.h \
    CgClass/kegel.h \
    CgClass/Mypolyline.h \
    CgClass/mats.h \
    CgEvents/slidermoveevent.h \
    CgClass/rotationskoerper.h \
CgUtils/ObjLoader.h \
    CgClass/dreiecke.h \
    CgClass/koordinatensystem.h \
    CgEvents/objectopenevent.h \
    CgClass/kugel.h \
    CgEvents/besterslidermoveevent.h \
    CgClass/traegerklasse.h \
    CgClass/scenegraph.h \
    CgClass/sceneentity.h \
    CgClass/appearance.h \
    CgClass/kamera.h \
    CgClass/wuerfel.h \
CgClass/pfeil.h \
    CgClass/virtCam.h \
    CgSceneGraph/CgCamera.h
