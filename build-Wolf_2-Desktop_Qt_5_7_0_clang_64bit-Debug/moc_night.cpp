/****************************************************************************
** Meta object code from reading C++ file 'night.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../newClient/night.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'night.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_night_t {
    QByteArrayData data[13];
    char stringdata0[95];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_night_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_night_t qt_meta_stringdata_night = {
    {
QT_MOC_LITERAL(0, 0, 5), // "night"
QT_MOC_LITERAL(1, 6, 8), // "setNight"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 3), // "day"
QT_MOC_LITERAL(4, 20, 6), // "setDay"
QT_MOC_LITERAL(5, 27, 8), // "setGuard"
QT_MOC_LITERAL(6, 36, 8), // "setWitch"
QT_MOC_LITERAL(7, 45, 7), // "setFore"
QT_MOC_LITERAL(8, 53, 6), // "setCap"
QT_MOC_LITERAL(9, 60, 6), // "setDie"
QT_MOC_LITERAL(10, 67, 6), // "setWin"
QT_MOC_LITERAL(11, 74, 10), // "setCapPass"
QT_MOC_LITERAL(12, 85, 9) // "setHunter"

    },
    "night\0setNight\0\0day\0setDay\0setGuard\0"
    "setWitch\0setFore\0setCap\0setDie\0setWin\0"
    "setCapPass\0setHunter"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_night[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x0a /* Public */,
       4,    1,   67,    2, 0x0a /* Public */,
       5,    0,   70,    2, 0x0a /* Public */,
       6,    0,   71,    2, 0x0a /* Public */,
       7,    0,   72,    2, 0x0a /* Public */,
       8,    0,   73,    2, 0x0a /* Public */,
       9,    0,   74,    2, 0x0a /* Public */,
      10,    0,   75,    2, 0x0a /* Public */,
      11,    0,   76,    2, 0x0a /* Public */,
      12,    0,   77,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void night::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        night *_t = static_cast<night *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setNight((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->setDay((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setGuard(); break;
        case 3: _t->setWitch(); break;
        case 4: _t->setFore(); break;
        case 5: _t->setCap(); break;
        case 6: _t->setDie(); break;
        case 7: _t->setWin(); break;
        case 8: _t->setCapPass(); break;
        case 9: _t->setHunter(); break;
        default: ;
        }
    }
}

const QMetaObject night::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_night.data,
      qt_meta_data_night,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *night::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *night::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_night.stringdata0))
        return static_cast<void*>(const_cast< night*>(this));
    return QDialog::qt_metacast(_clname);
}

int night::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
