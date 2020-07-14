/****************************************************************************
** Meta object code from reading C++ file 'cemulationANSI.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "cemulationANSI.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cemulationANSI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CEmulationANSI_t {
    QByteArrayData data[21];
    char stringdata0[208];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CEmulationANSI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CEmulationANSI_t qt_meta_stringdata_CEmulationANSI = {
    {
QT_MOC_LITERAL(0, 0, 14), // "CEmulationANSI"
QT_MOC_LITERAL(1, 15, 14), // "codeNotHandled"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 9), // "cursorOff"
QT_MOC_LITERAL(4, 41, 8), // "cursorOn"
QT_MOC_LITERAL(5, 50, 13), // "keyPressEvent"
QT_MOC_LITERAL(6, 64, 10), // "QKeyEvent*"
QT_MOC_LITERAL(7, 75, 1), // "e"
QT_MOC_LITERAL(8, 77, 11), // "receiveChar"
QT_MOC_LITERAL(9, 89, 2), // "ch"
QT_MOC_LITERAL(10, 92, 16), // "doCodeNotHandled"
QT_MOC_LITERAL(11, 109, 24), // "setApplicationCursorKeys"
QT_MOC_LITERAL(12, 134, 1), // "b"
QT_MOC_LITERAL(13, 136, 13), // "setOriginMode"
QT_MOC_LITERAL(14, 150, 12), // "setTopMargin"
QT_MOC_LITERAL(15, 163, 3), // "top"
QT_MOC_LITERAL(16, 167, 15), // "setBottomMargin"
QT_MOC_LITERAL(17, 183, 6), // "bottom"
QT_MOC_LITERAL(18, 190, 7), // "setGrid"
QT_MOC_LITERAL(19, 198, 4), // "cols"
QT_MOC_LITERAL(20, 203, 4) // "rows"

    },
    "CEmulationANSI\0codeNotHandled\0\0cursorOff\0"
    "cursorOn\0keyPressEvent\0QKeyEvent*\0e\0"
    "receiveChar\0ch\0doCodeNotHandled\0"
    "setApplicationCursorKeys\0b\0setOriginMode\0"
    "setTopMargin\0top\0setBottomMargin\0"
    "bottom\0setGrid\0cols\0rows"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CEmulationANSI[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    0,   70,    2, 0x06 /* Public */,
       4,    0,   71,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   72,    2, 0x0a /* Public */,
       8,    1,   75,    2, 0x0a /* Public */,
      10,    0,   78,    2, 0x08 /* Private */,
      11,    1,   79,    2, 0x09 /* Protected */,
      13,    1,   82,    2, 0x09 /* Protected */,
      14,    1,   85,    2, 0x09 /* Protected */,
      16,    1,   88,    2, 0x09 /* Protected */,
      18,    2,   91,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::UChar,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   19,   20,

       0        // eod
};

void CEmulationANSI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CEmulationANSI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->codeNotHandled(); break;
        case 1: _t->cursorOff(); break;
        case 2: _t->cursorOn(); break;
        case 3: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 4: _t->receiveChar((*reinterpret_cast< unsigned char(*)>(_a[1]))); break;
        case 5: _t->doCodeNotHandled(); break;
        case 6: _t->setApplicationCursorKeys((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->setOriginMode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->setTopMargin((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->setBottomMargin((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->setGrid((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CEmulationANSI::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CEmulationANSI::codeNotHandled)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CEmulationANSI::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CEmulationANSI::cursorOff)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CEmulationANSI::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CEmulationANSI::cursorOn)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CEmulationANSI::staticMetaObject = { {
    QMetaObject::SuperData::link<CEmulation::staticMetaObject>(),
    qt_meta_stringdata_CEmulationANSI.data,
    qt_meta_data_CEmulationANSI,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CEmulationANSI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CEmulationANSI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CEmulationANSI.stringdata0))
        return static_cast<void*>(this);
    return CEmulation::qt_metacast(_clname);
}

int CEmulationANSI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CEmulation::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void CEmulationANSI::codeNotHandled()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CEmulationANSI::cursorOff()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void CEmulationANSI::cursorOn()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
