/****************************************************************************
** Meta object code from reading C++ file 'CgQtGui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "CgQtViewer/CgQtGui.h"
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
    QByteArrayData data[18];
    char stringdata0[251];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CgQtGui_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CgQtGui_t qt_meta_stringdata_CgQtGui = {
    {
QT_MOC_LITERAL(0, 0, 7), // "CgQtGui"
QT_MOC_LITERAL(1, 8, 10), // "mouseEvent"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 12), // "QMouseEvent*"
QT_MOC_LITERAL(4, 33, 5), // "event"
QT_MOC_LITERAL(5, 39, 15), // "viewportChanged"
QT_MOC_LITERAL(6, 55, 16), // "clickedDonButton"
QT_MOC_LITERAL(7, 72, 10), // "changeBlue"
QT_MOC_LITERAL(8, 83, 9), // "changeRot"
QT_MOC_LITERAL(9, 93, 11), // "changeGreen"
QT_MOC_LITERAL(10, 105, 21), // "slotMySpinBox1Changed"
QT_MOC_LITERAL(11, 127, 22), // "slotMyCheckBox1Changed"
QT_MOC_LITERAL(12, 150, 20), // "slotMyButton1Pressed"
QT_MOC_LITERAL(13, 171, 17), // "realeaseDonButton"
QT_MOC_LITERAL(14, 189, 31), // "slotButtonGroupSelectionChanged"
QT_MOC_LITERAL(15, 221, 16), // "slotLoadMeshFile"
QT_MOC_LITERAL(16, 238, 10), // "sliderMove"
QT_MOC_LITERAL(17, 249, 1) // "x"

    },
    "CgQtGui\0mouseEvent\0\0QMouseEvent*\0event\0"
    "viewportChanged\0clickedDonButton\0"
    "changeBlue\0changeRot\0changeGreen\0"
    "slotMySpinBox1Changed\0slotMyCheckBox1Changed\0"
    "slotMyButton1Pressed\0realeaseDonButton\0"
    "slotButtonGroupSelectionChanged\0"
    "slotLoadMeshFile\0sliderMove\0x"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CgQtGui[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x08 /* Private */,
       5,    2,   82,    2, 0x08 /* Private */,
       6,    0,   87,    2, 0x08 /* Private */,
       7,    1,   88,    2, 0x08 /* Private */,
       8,    1,   91,    2, 0x08 /* Private */,
       9,    1,   94,    2, 0x08 /* Private */,
      10,    0,   97,    2, 0x08 /* Private */,
      11,    0,   98,    2, 0x08 /* Private */,
      12,    0,   99,    2, 0x08 /* Private */,
      13,    0,  100,    2, 0x08 /* Private */,
      14,    0,  101,    2, 0x08 /* Private */,
      15,    0,  102,    2, 0x08 /* Private */,
      16,    1,  103,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   17,

       0        // eod
};

void CgQtGui::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CgQtGui *_t = static_cast<CgQtGui *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->mouseEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 1: _t->viewportChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->clickedDonButton(); break;
        case 3: _t->changeBlue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->changeRot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->changeGreen((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->slotMySpinBox1Changed(); break;
        case 7: _t->slotMyCheckBox1Changed(); break;
        case 8: _t->slotMyButton1Pressed(); break;
        case 9: _t->realeaseDonButton(); break;
        case 10: _t->slotButtonGroupSelectionChanged(); break;
        case 11: _t->slotLoadMeshFile(); break;
        case 12: _t->sliderMove((*reinterpret_cast< int(*)>(_a[1]))); break;
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
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
