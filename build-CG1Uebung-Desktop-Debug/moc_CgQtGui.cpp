/****************************************************************************
** Meta object code from reading C++ file 'CgQtGui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../basis/CgQtViewer/CgQtGui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CgQtGui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CgQtGui_t {
    QByteArrayData data[20];
    char stringdata0[252];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CgQtGui_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CgQtGui_t qt_meta_stringdata_CgQtGui = {
    {
QT_MOC_LITERAL(0, 0, 7), // "CgQtGui"
QT_MOC_LITERAL(1, 8, 20), // "changeRotationObject"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 21), // "changeTranslateObject"
QT_MOC_LITERAL(4, 52, 17), // "changeRotaKoerper"
QT_MOC_LITERAL(5, 70, 11), // "changeColor"
QT_MOC_LITERAL(6, 82, 25), // "zeige_normale_taste_page2"
QT_MOC_LITERAL(7, 108, 11), // "changeKegel"
QT_MOC_LITERAL(8, 120, 14), // "changeZylinder"
QT_MOC_LITERAL(9, 135, 10), // "mouseEvent"
QT_MOC_LITERAL(10, 146, 12), // "QMouseEvent*"
QT_MOC_LITERAL(11, 159, 5), // "event"
QT_MOC_LITERAL(12, 165, 15), // "viewportChanged"
QT_MOC_LITERAL(13, 181, 9), // "tabChange"
QT_MOC_LITERAL(14, 191, 1), // "x"
QT_MOC_LITERAL(15, 193, 7), // "selectX"
QT_MOC_LITERAL(16, 201, 7), // "selectY"
QT_MOC_LITERAL(17, 209, 7), // "selectZ"
QT_MOC_LITERAL(18, 217, 13), // "matrizenCheck"
QT_MOC_LITERAL(19, 231, 20) // "changeRotationPlanet"

    },
    "CgQtGui\0changeRotationObject\0\0"
    "changeTranslateObject\0changeRotaKoerper\0"
    "changeColor\0zeige_normale_taste_page2\0"
    "changeKegel\0changeZylinder\0mouseEvent\0"
    "QMouseEvent*\0event\0viewportChanged\0"
    "tabChange\0x\0selectX\0selectY\0selectZ\0"
    "matrizenCheck\0changeRotationPlanet"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CgQtGui[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x08 /* Private */,
       3,    0,   90,    2, 0x08 /* Private */,
       4,    0,   91,    2, 0x08 /* Private */,
       5,    0,   92,    2, 0x08 /* Private */,
       6,    0,   93,    2, 0x08 /* Private */,
       7,    0,   94,    2, 0x08 /* Private */,
       8,    0,   95,    2, 0x08 /* Private */,
       9,    1,   96,    2, 0x08 /* Private */,
      12,    2,   99,    2, 0x08 /* Private */,
      13,    1,  104,    2, 0x08 /* Private */,
      15,    0,  107,    2, 0x08 /* Private */,
      16,    0,  108,    2, 0x08 /* Private */,
      17,    0,  109,    2, 0x08 /* Private */,
      18,    0,  110,    2, 0x08 /* Private */,
      19,    0,  111,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CgQtGui::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CgQtGui *_t = static_cast<CgQtGui *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changeRotationObject(); break;
        case 1: _t->changeTranslateObject(); break;
        case 2: _t->changeRotaKoerper(); break;
        case 3: _t->changeColor(); break;
        case 4: _t->zeige_normale_taste_page2(); break;
        case 5: _t->changeKegel(); break;
        case 6: _t->changeZylinder(); break;
        case 7: _t->mouseEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 8: _t->viewportChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->tabChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->selectX(); break;
        case 11: _t->selectY(); break;
        case 12: _t->selectZ(); break;
        case 13: _t->matrizenCheck(); break;
        case 14: _t->changeRotationPlanet(); break;
        default: ;
        }
    }
}

const QMetaObject CgQtGui::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CgQtGui.data,
      qt_meta_data_CgQtGui,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CgQtGui::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CgQtGui::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CgQtGui.stringdata0))
        return static_cast<void*>(const_cast< CgQtGui*>(this));
    if (!strcmp(_clname, "CgObservable"))
        return static_cast< CgObservable*>(const_cast< CgQtGui*>(this));
    return QWidget::qt_metacast(_clname);
}

int CgQtGui::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
