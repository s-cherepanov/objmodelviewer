/****************************************************************************
** Meta object code from reading C++ file 'glwidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../glwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'glwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GLWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   10,    9,    9, 0x05,
      38,   10,    9,    9, 0x05,
      60,   10,    9,    9, 0x05,
      86,   82,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
     113,  107,    9,    9, 0x0a,
     132,  107,    9,    9, 0x0a,
     148,  107,    9,    9, 0x0a,
     163,   10,    9,    9, 0x0a,
     181,   10,    9,    9, 0x0a,
     199,   10,    9,    9, 0x0a,
     217,   82,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GLWidget[] = {
    "GLWidget\0\0angle\0xRotationChanged(int)\0"
    "yRotationChanged(int)\0zRotationChanged(int)\0"
    "dis\0distanceChanged(int)\0value\0"
    "SetWireframe(bool)\0setSmooth(bool)\0"
    "SetStats(bool)\0setXRotation(int)\0"
    "setYRotation(int)\0setZRotation(int)\0"
    "setDistance(int)\0"
};

void GLWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GLWidget *_t = static_cast<GLWidget *>(_o);
        switch (_id) {
        case 0: _t->xRotationChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->yRotationChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->zRotationChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->distanceChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->SetWireframe((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->setSmooth((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->SetStats((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->setXRotation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->setYRotation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->setZRotation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->setDistance((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GLWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GLWidget::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_GLWidget,
      qt_meta_data_GLWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GLWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GLWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GLWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GLWidget))
        return static_cast<void*>(const_cast< GLWidget*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int GLWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void GLWidget::xRotationChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GLWidget::yRotationChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GLWidget::zRotationChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GLWidget::distanceChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
