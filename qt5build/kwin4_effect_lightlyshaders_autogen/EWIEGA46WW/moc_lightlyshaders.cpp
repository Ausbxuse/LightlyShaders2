/****************************************************************************
** Meta object code from reading C++ file 'lightlyshaders.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../lightlyshaders.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lightlyshaders.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_KWin__LightlyShadersEffect_t {
    QByteArrayData data[10];
    char stringdata0[124];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KWin__LightlyShadersEffect_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KWin__LightlyShadersEffect_t qt_meta_stringdata_KWin__LightlyShadersEffect = {
    {
QT_MOC_LITERAL(0, 0, 26), // "KWin::LightlyShadersEffect"
QT_MOC_LITERAL(1, 27, 11), // "windowAdded"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 13), // "EffectWindow*"
QT_MOC_LITERAL(4, 54, 6), // "window"
QT_MOC_LITERAL(5, 61, 12), // "windowClosed"
QT_MOC_LITERAL(6, 74, 27), // "windowMaximizedStateChanged"
QT_MOC_LITERAL(7, 102, 1), // "w"
QT_MOC_LITERAL(8, 104, 10), // "horizontal"
QT_MOC_LITERAL(9, 115, 8) // "vertical"

    },
    "KWin::LightlyShadersEffect\0windowAdded\0"
    "\0EffectWindow*\0window\0windowClosed\0"
    "windowMaximizedStateChanged\0w\0horizontal\0"
    "vertical"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KWin__LightlyShadersEffect[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x09 /* Protected */,
       5,    1,   32,    2, 0x09 /* Protected */,
       6,    3,   35,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool, QMetaType::Bool,    7,    8,    9,

       0        // eod
};

void KWin::LightlyShadersEffect::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LightlyShadersEffect *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->windowAdded((*reinterpret_cast< EffectWindow*(*)>(_a[1]))); break;
        case 1: _t->windowClosed((*reinterpret_cast< EffectWindow*(*)>(_a[1]))); break;
        case 2: _t->windowMaximizedStateChanged((*reinterpret_cast< EffectWindow*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< EffectWindow* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< EffectWindow* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< EffectWindow* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject KWin::LightlyShadersEffect::staticMetaObject = { {
    QMetaObject::SuperData::link<KWin::Effect::staticMetaObject>(),
    qt_meta_stringdata_KWin__LightlyShadersEffect.data,
    qt_meta_data_KWin__LightlyShadersEffect,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *KWin::LightlyShadersEffect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KWin::LightlyShadersEffect::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_KWin__LightlyShadersEffect.stringdata0))
        return static_cast<void*>(this);
    return KWin::Effect::qt_metacast(_clname);
}

int KWin::LightlyShadersEffect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = KWin::Effect::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
