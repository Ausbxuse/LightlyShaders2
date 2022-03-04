/****************************************************************************
** Meta object code from reading C++ file 'lightlyshaders_config.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../lightlyshaders_config.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lightlyshaders_config.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LightlyShadersConfig_t {
    QByteArrayData data[5];
    char stringdata0[41];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LightlyShadersConfig_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LightlyShadersConfig_t qt_meta_stringdata_LightlyShadersConfig = {
    {
QT_MOC_LITERAL(0, 0, 20), // "LightlyShadersConfig"
QT_MOC_LITERAL(1, 21, 4), // "save"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 4), // "load"
QT_MOC_LITERAL(4, 32, 8) // "defaults"

    },
    "LightlyShadersConfig\0save\0\0load\0"
    "defaults"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LightlyShadersConfig[] = {

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
       1,    0,   29,    2, 0x0a /* Public */,
       3,    0,   30,    2, 0x0a /* Public */,
       4,    0,   31,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void LightlyShadersConfig::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LightlyShadersConfig *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->save(); break;
        case 1: _t->load(); break;
        case 2: _t->defaults(); break;
        default: ;
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject LightlyShadersConfig::staticMetaObject = { {
    QMetaObject::SuperData::link<KCModule::staticMetaObject>(),
    qt_meta_stringdata_LightlyShadersConfig.data,
    qt_meta_data_LightlyShadersConfig,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *LightlyShadersConfig::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LightlyShadersConfig::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LightlyShadersConfig.stringdata0))
        return static_cast<void*>(this);
    return KCModule::qt_metacast(_clname);
}

int LightlyShadersConfig::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = KCModule::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
