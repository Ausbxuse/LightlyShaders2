/****************************************************************************
** Meta object code from reading C++ file 'dbus.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../dbus.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dbus.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_KWin__EffectAdaptor_t {
    QByteArrayData data[7];
    char stringdata0[84];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KWin__EffectAdaptor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KWin__EffectAdaptor_t qt_meta_stringdata_KWin__EffectAdaptor = {
    {
QT_MOC_LITERAL(0, 0, 19), // "KWin::EffectAdaptor"
QT_MOC_LITERAL(1, 20, 15), // "D-Bus Interface"
QT_MOC_LITERAL(2, 36, 12), // "org.kde.kwin"
QT_MOC_LITERAL(3, 49, 12), // "setRoundness"
QT_MOC_LITERAL(4, 62, 9), // "Q_NOREPLY"
QT_MOC_LITERAL(5, 72, 1), // "r"
QT_MOC_LITERAL(6, 74, 9) // "configure"

    },
    "KWin::EffectAdaptor\0D-Bus Interface\0"
    "org.kde.kwin\0setRoundness\0Q_NOREPLY\0"
    "r\0configure"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KWin__EffectAdaptor[] = {

 // content:
       8,       // revision
       0,       // classname
       1,   14, // classinfo
       2,   16, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // classinfo: key, value
       1,    2,

 // slots: name, argc, parameters, tag, flags
       3,    1,   26,    4, 0x0a /* Public */,
       6,    0,   29,    4, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,

       0        // eod
};

void KWin::EffectAdaptor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EffectAdaptor *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->setRoundness((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->configure(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject KWin::EffectAdaptor::staticMetaObject = { {
    QMetaObject::SuperData::link<QDBusAbstractAdaptor::staticMetaObject>(),
    qt_meta_stringdata_KWin__EffectAdaptor.data,
    qt_meta_data_KWin__EffectAdaptor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *KWin::EffectAdaptor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KWin::EffectAdaptor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_KWin__EffectAdaptor.stringdata0))
        return static_cast<void*>(this);
    return QDBusAbstractAdaptor::qt_metacast(_clname);
}

int KWin::EffectAdaptor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDBusAbstractAdaptor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
