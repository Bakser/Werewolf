/****************************************************************************
** Meta object code from reading C++ file 'clientnetworkinterface.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Client/clientnetworkinterface.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clientnetworkinterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ClientNetworkInterface_t {
    QByteArrayData data[11];
    char stringdata0[138];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ClientNetworkInterface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ClientNetworkInterface_t qt_meta_stringdata_ClientNetworkInterface = {
    {
QT_MOC_LITERAL(0, 0, 22), // "ClientNetworkInterface"
QT_MOC_LITERAL(1, 23, 14), // "receiveCommand"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 7), // "message"
QT_MOC_LITERAL(4, 47, 9), // "startRead"
QT_MOC_LITERAL(5, 57, 10), // "startLogin"
QT_MOC_LITERAL(6, 68, 12), // "displayError"
QT_MOC_LITERAL(7, 81, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(8, 110, 12), // "disconnected"
QT_MOC_LITERAL(9, 123, 9), // "addString"
QT_MOC_LITERAL(10, 133, 4) // "test"

    },
    "ClientNetworkInterface\0receiveCommand\0"
    "\0message\0startRead\0startLogin\0"
    "displayError\0QAbstractSocket::SocketError\0"
    "disconnected\0addString\0test"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ClientNetworkInterface[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   52,    2, 0x0a /* Public */,
       5,    1,   53,    2, 0x0a /* Public */,
       6,    1,   56,    2, 0x0a /* Public */,
       8,    0,   59,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
       9,    1,   60,    2, 0x02 /* Public */,
      10,    0,   63,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::QString,

       0        // eod
};

void ClientNetworkInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ClientNetworkInterface *_t = static_cast<ClientNetworkInterface *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->receiveCommand((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->startRead(); break;
        case 2: _t->startLogin((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->displayError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 4: _t->disconnected(); break;
        case 5: _t->addString((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: { QString _r = _t->test();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ClientNetworkInterface::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientNetworkInterface::receiveCommand)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject ClientNetworkInterface::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ClientNetworkInterface.data,
      qt_meta_data_ClientNetworkInterface,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ClientNetworkInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ClientNetworkInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ClientNetworkInterface.stringdata0))
        return static_cast<void*>(const_cast< ClientNetworkInterface*>(this));
    return QObject::qt_metacast(_clname);
}

int ClientNetworkInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void ClientNetworkInterface::receiveCommand(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
