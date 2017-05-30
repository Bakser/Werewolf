/****************************************************************************
** Meta object code from reading C++ file 'newroom.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../newClient/newroom.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'newroom.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_newroom_t {
    QByteArrayData data[12];
    char stringdata0[202];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_newroom_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_newroom_t qt_meta_stringdata_newroom = {
    {
QT_MOC_LITERAL(0, 0, 7), // "newroom"
QT_MOC_LITERAL(1, 8, 7), // "onclose"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(4, 39, 25), // "on_spinBox_3_valueChanged"
QT_MOC_LITERAL(5, 65, 4), // "arg1"
QT_MOC_LITERAL(6, 70, 23), // "on_spinBox_valueChanged"
QT_MOC_LITERAL(7, 94, 19), // "on_checkBox_clicked"
QT_MOC_LITERAL(8, 114, 21), // "on_checkBox_2_clicked"
QT_MOC_LITERAL(9, 136, 21), // "on_checkBox_4_clicked"
QT_MOC_LITERAL(10, 158, 21), // "on_checkBox_3_clicked"
QT_MOC_LITERAL(11, 180, 21) // "on_checkBox_5_clicked"

    },
    "newroom\0onclose\0\0on_pushButton_clicked\0"
    "on_spinBox_3_valueChanged\0arg1\0"
    "on_spinBox_valueChanged\0on_checkBox_clicked\0"
    "on_checkBox_2_clicked\0on_checkBox_4_clicked\0"
    "on_checkBox_3_clicked\0on_checkBox_5_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_newroom[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   60,    2, 0x08 /* Private */,
       4,    1,   61,    2, 0x08 /* Private */,
       6,    1,   64,    2, 0x08 /* Private */,
       7,    0,   67,    2, 0x08 /* Private */,
       8,    0,   68,    2, 0x08 /* Private */,
       9,    0,   69,    2, 0x08 /* Private */,
      10,    0,   70,    2, 0x08 /* Private */,
      11,    0,   71,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void newroom::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        newroom *_t = static_cast<newroom *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onclose(); break;
        case 1: _t->on_pushButton_clicked(); break;
        case 2: _t->on_spinBox_3_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_spinBox_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_checkBox_clicked(); break;
        case 5: _t->on_checkBox_2_clicked(); break;
        case 6: _t->on_checkBox_4_clicked(); break;
        case 7: _t->on_checkBox_3_clicked(); break;
        case 8: _t->on_checkBox_5_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (newroom::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&newroom::onclose)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject newroom::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_newroom.data,
      qt_meta_data_newroom,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *newroom::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *newroom::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_newroom.stringdata0))
        return static_cast<void*>(const_cast< newroom*>(this));
    return QDialog::qt_metacast(_clname);
}

int newroom::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void newroom::onclose()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
