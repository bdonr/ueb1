/****************************************************************************
** Meta object code from reading C++ file 'CgQtGui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ueb2/CgQtViewer/CgQtGui.h"
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
    QByteArrayData data[13];
    char stringdata0[150];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CgQtGui_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CgQtGui_t qt_meta_stringdata_CgQtGui = {
    {
QT_MOC_LITERAL(0, 0, 7), // "CgQtGui"
QT_MOC_LITERAL(1, 8, 17), // "changeRotaKoerper"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 11), // "changeColor"
QT_MOC_LITERAL(4, 39, 25), // "zeige_normale_taste_page2"
QT_MOC_LITERAL(5, 65, 11), // "changeKegel"
QT_MOC_LITERAL(6, 77, 14), // "changeZylinder"
QT_MOC_LITERAL(7, 92, 10), // "mouseEvent"
QT_MOC_LITERAL(8, 103, 12), // "QMouseEvent*"
QT_MOC_LITERAL(9, 116, 5), // "event"
QT_MOC_LITERAL(10, 122, 15), // "viewportChanged"
QT_MOC_LITERAL(11, 138, 9), // "tabChange"
QT_MOC_LITERAL(12, 148, 1) // "x"

    },
    "CgQtGui\0changeRotaKoerper\0\0changeColor\0"
    "zeige_normale_taste_page2\0changeKegel\0"
    "changeZylinder\0mouseEvent\0QMouseEvent*\0"
    "event\0viewportChanged\0tabChange\0x"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CgQtGui[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    1,   59,    2, 0x08 /* Private */,
      10,    2,   62,    2, 0x08 /* Private */,
      11,    1,   67,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int,   12,

       0        // eod
};

void CgQtGui::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CgQtGui *_t = static_cast<CgQtGui *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changeRotaKoerper(); break;
        case 1: _t->changeColor(); break;
        case 2: _t->zeige_normale_taste_page2(); break;
        case 3: _t->changeKegel(); break;
        case 4: _t->changeZylinder(); break;
        case 5: _t->mouseEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 6: _t->viewportChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->tabChange((*reinterpret_cast< int(*)>(_a[1]))); break;
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
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
