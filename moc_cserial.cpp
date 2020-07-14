/****************************************************************************
** Meta object code from reading C++ file 'cserial.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "cserial.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cserial.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CSerial_t {
    QByteArrayData data[22];
    char stringdata0[175];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CSerial_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CSerial_t qt_meta_stringdata_CSerial = {
    {
QT_MOC_LITERAL(0, 0, 7), // "CSerial"
QT_MOC_LITERAL(1, 8, 13), // "statusMessage"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 6), // "sender"
QT_MOC_LITERAL(4, 30, 5), // "level"
QT_MOC_LITERAL(5, 36, 3), // "msg"
QT_MOC_LITERAL(6, 40, 9), // "readyRead"
QT_MOC_LITERAL(7, 50, 2), // "rx"
QT_MOC_LITERAL(8, 53, 1), // "c"
QT_MOC_LITERAL(9, 55, 7), // "beginRx"
QT_MOC_LITERAL(10, 63, 5), // "endRx"
QT_MOC_LITERAL(11, 69, 7), // "beginTx"
QT_MOC_LITERAL(12, 77, 5), // "endTx"
QT_MOC_LITERAL(13, 83, 12), // "setEmitChars"
QT_MOC_LITERAL(14, 96, 1), // "b"
QT_MOC_LITERAL(15, 98, 13), // "sendAsciiChar"
QT_MOC_LITERAL(16, 112, 15), // "sendAsciiString"
QT_MOC_LITERAL(17, 128, 11), // "const char*"
QT_MOC_LITERAL(18, 140, 1), // "s"
QT_MOC_LITERAL(19, 142, 13), // "readActivated"
QT_MOC_LITERAL(20, 156, 6), // "handle"
QT_MOC_LITERAL(21, 163, 11) // "readTimeout"

    },
    "CSerial\0statusMessage\0\0sender\0level\0"
    "msg\0readyRead\0rx\0c\0beginRx\0endRx\0"
    "beginTx\0endTx\0setEmitChars\0b\0sendAsciiChar\0"
    "sendAsciiString\0const char*\0s\0"
    "readActivated\0handle\0readTimeout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CSerial[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   74,    2, 0x06 /* Public */,
       6,    0,   81,    2, 0x06 /* Public */,
       7,    1,   82,    2, 0x06 /* Public */,
       9,    0,   85,    2, 0x06 /* Public */,
      10,    0,   86,    2, 0x06 /* Public */,
      11,    0,   87,    2, 0x06 /* Public */,
      12,    0,   88,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    1,   89,    2, 0x0a /* Public */,
      15,    1,   92,    2, 0x0a /* Public */,
      16,    1,   95,    2, 0x0a /* Public */,
      19,    1,   98,    2, 0x08 /* Private */,
      21,    0,  101,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::VoidStar, QMetaType::Int, QMetaType::QString,    3,    4,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UChar,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void, QMetaType::Char,    8,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, QMetaType::Int,   20,
    QMetaType::Void,

       0        // eod
};

void CSerial::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CSerial *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->statusMessage((*reinterpret_cast< void*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 1: _t->readyRead(); break;
        case 2: _t->rx((*reinterpret_cast< unsigned char(*)>(_a[1]))); break;
        case 3: _t->beginRx(); break;
        case 4: _t->endRx(); break;
        case 5: _t->beginTx(); break;
        case 6: _t->endTx(); break;
        case 7: _t->setEmitChars((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->sendAsciiChar((*reinterpret_cast< const char(*)>(_a[1]))); break;
        case 9: _t->sendAsciiString((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 10: _t->readActivated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->readTimeout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CSerial::*)(void * , int , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CSerial::statusMessage)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CSerial::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CSerial::readyRead)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CSerial::*)(unsigned char );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CSerial::rx)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (CSerial::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CSerial::beginRx)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (CSerial::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CSerial::endRx)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (CSerial::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CSerial::beginTx)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (CSerial::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CSerial::endTx)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CSerial::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CSerial.data,
    qt_meta_data_CSerial,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CSerial::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CSerial::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CSerial.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CSerial::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void CSerial::statusMessage(void * _t1, int _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CSerial::readyRead()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void CSerial::rx(unsigned char _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CSerial::beginRx()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void CSerial::endRx()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void CSerial::beginTx()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void CSerial::endTx()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
