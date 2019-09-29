/****************************************************************************
** Meta object code from reading C++ file 'QtOpenGLWidgetOSG3.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QtOpenGLWidgetOSG3.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QtOpenGLWidgetOSG3.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QtOpenGLWidgetOSG3_t {
    QByteArrayData data[20];
    char stringdata0[272];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QtOpenGLWidgetOSG3_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QtOpenGLWidgetOSG3_t qt_meta_stringdata_QtOpenGLWidgetOSG3 = {
    {
QT_MOC_LITERAL(0, 0, 18), // "QtOpenGLWidgetOSG3"
QT_MOC_LITERAL(1, 19, 14), // "sendHeightRamp"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 4), // "axis"
QT_MOC_LITERAL(4, 40, 10), // "beginColor"
QT_MOC_LITERAL(5, 51, 8), // "endColor"
QT_MOC_LITERAL(6, 60, 13), // "selCloudPoint"
QT_MOC_LITERAL(7, 74, 22), // "OSGWidget::MeauseCloud"
QT_MOC_LITERAL(8, 97, 6), // "meause"
QT_MOC_LITERAL(9, 104, 18), // "onChangedHightRamp"
QT_MOC_LITERAL(10, 123, 15), // "onSelBeginColor"
QT_MOC_LITERAL(11, 139, 13), // "onSelEndColor"
QT_MOC_LITERAL(12, 153, 16), // "onShowHeightRamp"
QT_MOC_LITERAL(13, 170, 16), // "onHideHeightRamp"
QT_MOC_LITERAL(14, 187, 16), // "onSendHeightRamp"
QT_MOC_LITERAL(15, 204, 15), // "onRecHeightRamp"
QT_MOC_LITERAL(16, 220, 10), // "onSelPoint"
QT_MOC_LITERAL(17, 231, 7), // "checked"
QT_MOC_LITERAL(18, 239, 15), // "onResetSelPoint"
QT_MOC_LITERAL(19, 255, 16) // "onCancelSelPoint"

    },
    "QtOpenGLWidgetOSG3\0sendHeightRamp\0\0"
    "axis\0beginColor\0endColor\0selCloudPoint\0"
    "OSGWidget::MeauseCloud\0meause\0"
    "onChangedHightRamp\0onSelBeginColor\0"
    "onSelEndColor\0onShowHeightRamp\0"
    "onHideHeightRamp\0onSendHeightRamp\0"
    "onRecHeightRamp\0onSelPoint\0checked\0"
    "onResetSelPoint\0onCancelSelPoint"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtOpenGLWidgetOSG3[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   79,    2, 0x06 /* Public */,
       6,    1,   86,    2, 0x06 /* Public */,
       6,    0,   89,    2, 0x26 /* Public | MethodCloned */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   90,    2, 0x0a /* Public */,
      10,    0,   91,    2, 0x0a /* Public */,
      11,    0,   92,    2, 0x0a /* Public */,
      12,    0,   93,    2, 0x0a /* Public */,
      13,    0,   94,    2, 0x0a /* Public */,
      14,    0,   95,    2, 0x0a /* Public */,
      15,    3,   96,    2, 0x0a /* Public */,
      16,    1,  103,    2, 0x0a /* Public */,
      18,    0,  106,    2, 0x0a /* Public */,
      19,    0,  107,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QColor, QMetaType::QColor,    3,    4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QColor, QMetaType::QColor,    2,    2,    2,
    QMetaType::Void, QMetaType::Bool,   17,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QtOpenGLWidgetOSG3::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QtOpenGLWidgetOSG3 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendHeightRamp((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QColor(*)>(_a[2])),(*reinterpret_cast< QColor(*)>(_a[3]))); break;
        case 1: _t->selCloudPoint((*reinterpret_cast< OSGWidget::MeauseCloud(*)>(_a[1]))); break;
        case 2: _t->selCloudPoint(); break;
        case 3: _t->onChangedHightRamp(); break;
        case 4: _t->onSelBeginColor(); break;
        case 5: _t->onSelEndColor(); break;
        case 6: _t->onShowHeightRamp(); break;
        case 7: _t->onHideHeightRamp(); break;
        case 8: _t->onSendHeightRamp(); break;
        case 9: _t->onRecHeightRamp((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QColor(*)>(_a[2])),(*reinterpret_cast< QColor(*)>(_a[3]))); break;
        case 10: _t->onSelPoint((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->onResetSelPoint(); break;
        case 12: _t->onCancelSelPoint(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QtOpenGLWidgetOSG3::*)(int , QColor , QColor );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtOpenGLWidgetOSG3::sendHeightRamp)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QtOpenGLWidgetOSG3::*)(OSGWidget::MeauseCloud );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtOpenGLWidgetOSG3::selCloudPoint)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QtOpenGLWidgetOSG3::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_QtOpenGLWidgetOSG3.data,
    qt_meta_data_QtOpenGLWidgetOSG3,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QtOpenGLWidgetOSG3::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtOpenGLWidgetOSG3::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QtOpenGLWidgetOSG3.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int QtOpenGLWidgetOSG3::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void QtOpenGLWidgetOSG3::sendHeightRamp(int _t1, QColor _t2, QColor _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QtOpenGLWidgetOSG3::selCloudPoint(OSGWidget::MeauseCloud _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
