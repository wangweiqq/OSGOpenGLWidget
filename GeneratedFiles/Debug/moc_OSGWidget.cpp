/****************************************************************************
** Meta object code from reading C++ file 'OSGWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../OSGWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'OSGWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_OSGWidget_t {
    QByteArrayData data[15];
    char stringdata0[149];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OSGWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OSGWidget_t qt_meta_stringdata_OSGWidget = {
    {
QT_MOC_LITERAL(0, 0, 9), // "OSGWidget"
QT_MOC_LITERAL(1, 10, 10), // "onCylinder"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 6), // "onQuad"
QT_MOC_LITERAL(4, 29, 7), // "onCloud"
QT_MOC_LITERAL(5, 37, 7), // "onShape"
QT_MOC_LITERAL(6, 45, 8), // "onGlider"
QT_MOC_LITERAL(7, 54, 7), // "onClear"
QT_MOC_LITERAL(8, 62, 15), // "onRecHeightRamp"
QT_MOC_LITERAL(9, 78, 4), // "axis"
QT_MOC_LITERAL(10, 83, 10), // "beginColor"
QT_MOC_LITERAL(11, 94, 8), // "endColor"
QT_MOC_LITERAL(12, 103, 15), // "onSelCloudPoint"
QT_MOC_LITERAL(13, 119, 22), // "OSGWidget::MeauseCloud"
QT_MOC_LITERAL(14, 142, 6) // "meause"

    },
    "OSGWidget\0onCylinder\0\0onQuad\0onCloud\0"
    "onShape\0onGlider\0onClear\0onRecHeightRamp\0"
    "axis\0beginColor\0endColor\0onSelCloudPoint\0"
    "OSGWidget::MeauseCloud\0meause"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OSGWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x0a /* Public */,
       3,    0,   55,    2, 0x0a /* Public */,
       4,    0,   56,    2, 0x0a /* Public */,
       5,    0,   57,    2, 0x0a /* Public */,
       6,    0,   58,    2, 0x0a /* Public */,
       7,    0,   59,    2, 0x0a /* Public */,
       8,    3,   60,    2, 0x0a /* Public */,
      12,    1,   67,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QColor, QMetaType::QColor,    9,   10,   11,
    QMetaType::Void, 0x80000000 | 13,   14,

       0        // eod
};

void OSGWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<OSGWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onCylinder(); break;
        case 1: _t->onQuad(); break;
        case 2: _t->onCloud(); break;
        case 3: _t->onShape(); break;
        case 4: _t->onGlider(); break;
        case 5: _t->onClear(); break;
        case 6: _t->onRecHeightRamp((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QColor(*)>(_a[2])),(*reinterpret_cast< QColor(*)>(_a[3]))); break;
        case 7: _t->onSelCloudPoint((*reinterpret_cast< OSGWidget::MeauseCloud(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject OSGWidget::staticMetaObject = { {
    &QOpenGLWidget::staticMetaObject,
    qt_meta_stringdata_OSGWidget.data,
    qt_meta_data_OSGWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *OSGWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OSGWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_OSGWidget.stringdata0))
        return static_cast<void*>(this);
    return QOpenGLWidget::qt_metacast(_clname);
}

int OSGWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
