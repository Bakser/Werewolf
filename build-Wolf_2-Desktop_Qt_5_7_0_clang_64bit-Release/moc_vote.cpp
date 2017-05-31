/****************************************************************************
** Meta object code from reading C++ file 'vote.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../newClient/vote.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vote.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_vote_t {
    QByteArrayData data[10];
    char stringdata0[125];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_vote_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_vote_t qt_meta_stringdata_vote = {
    {
QT_MOC_LITERAL(0, 0, 4), // "vote"
QT_MOC_LITERAL(1, 5, 11), // "voteSuccess"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 7), // "yesOrNo"
QT_MOC_LITERAL(4, 26, 25), // "on_listWidget_itemClicked"
QT_MOC_LITERAL(5, 52, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(6, 69, 4), // "item"
QT_MOC_LITERAL(7, 74, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(8, 96, 14), // "on_yes_clicked"
QT_MOC_LITERAL(9, 111, 13) // "on_no_clicked"

    },
    "vote\0voteSuccess\0\0yesOrNo\0"
    "on_listWidget_itemClicked\0QListWidgetItem*\0"
    "item\0on_pushButton_clicked\0on_yes_clicked\0"
    "on_no_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_vote[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       3,    1,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   50,    2, 0x08 /* Private */,
       7,    0,   53,    2, 0x08 /* Private */,
       8,    0,   54,    2, 0x08 /* Private */,
       9,    0,   55,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void vote::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        vote *_t = static_cast<vote *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->voteSuccess((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->yesOrNo((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->on_listWidget_itemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 3: _t->on_pushButton_clicked(); break;
        case 4: _t->on_yes_clicked(); break;
        case 5: _t->on_no_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (vote::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&vote::voteSuccess)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (vote::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&vote::yesOrNo)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject vote::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_vote.data,
      qt_meta_data_vote,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *vote::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *vote::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_vote.stringdata0))
        return static_cast<void*>(const_cast< vote*>(this));
    return QDialog::qt_metacast(_clname);
}

int vote::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void vote::voteSuccess(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void vote::yesOrNo(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
