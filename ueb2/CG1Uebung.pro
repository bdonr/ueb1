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
    CgSceneGraph/meshfactory.cpp \
    CgSceneGraph/Zylinder.cpp \
    CgSceneGraph/kegel.cpp \
    CgSceneGraph/Mypolyline.cpp \
    CgSceneGraph/slidermoveevent.cpp \
    CgSceneGraph/rotationskoerper.cpp \
    CgUtils/ObjLoader.cpp \
    CgSceneGraph/dreiecke.cpp \
    CgSceneGraph/koordinatensystem.cpp \
    CgEvents/objectopenevent.cpp \
    CgSceneGraph/kugel.cpp \
    CgSceneGraph/besterslidermoveevent.cpp \
    CgSceneGraph/traegerklasse.cpp \
    CgSceneGraph/scenegraph.cpp \
    CgSceneGraph/sceneentity.cpp \
    CgSceneGraph/appearance.cpp \
    CgSceneGraph/kamera.cpp \
    CgSceneGraph/wuerfel.cpp


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
    CgSceneGraph/meshfactory.h \
    CgSceneGraph/Zylinder.h \
    CgSceneGraph/kegel.h \
    CgSceneGraph/Mypolyline.h \
    CgSceneGraph/slidermoveevent.h \
    CgSceneGraph/rotationskoerper.h \
CgUtils/ObjLoader.h \
    CgSceneGraph/dreiecke.h \
    CgSceneGraph/koordinatensystem.h \
    CgEvents/objectopenevent.h \
    CgSceneGraph/kugel.h \
    CgSceneGraph/besterslidermoveevent.h \
    CgSceneGraph/traegerklasse.h \
    CgSceneGraph/scenegraph.h \
    CgSceneGraph/sceneentity.h \
    CgSceneGraph/appearance.h \
    CgSceneGraph/kamera.h \
    CgSceneGraph/wuerfel.h
