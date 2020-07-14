/****************************************************************************
** Meta object code from reading C++ file 'komport.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "komport.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'komport.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Komport_t {
    QByteArrayData data[17];
    char stringdata0[164];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Komport_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Komport_t qt_meta_stringdata_Komport = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Komport"
QT_MOC_LITERAL(1, 8, 5), // "about"
QT_MOC_LITERAL(2, 14, 0), // ""
QT_MOC_LITERAL(3, 15, 12), // "editSettings"
QT_MOC_LITERAL(4, 28, 6), // "doCopy"
QT_MOC_LITERAL(5, 35, 7), // "doPaste"
QT_MOC_LITERAL(6, 43, 25), // "openBackgroundColorDialog"
QT_MOC_LITERAL(7, 69, 25), // "openForegroundColorDialog"
QT_MOC_LITERAL(8, 95, 12), // "settingsHelp"
QT_MOC_LITERAL(9, 108, 7), // "rxLedOn"
QT_MOC_LITERAL(10, 116, 8), // "rxLedOff"
QT_MOC_LITERAL(11, 125, 7), // "txLedOn"
QT_MOC_LITERAL(12, 133, 8), // "txLedOff"
QT_MOC_LITERAL(13, 142, 8), // "clearLog"
QT_MOC_LITERAL(14, 151, 3), // "log"
QT_MOC_LITERAL(15, 155, 3), // "msg"
QT_MOC_LITERAL(16, 159, 4) // "show"

    },
    "Komport\0about\0\0editSettings\0doCopy\0"
    "doPaste\0openBackgroundColorDialog\0"
    "openForegroundColorDialog\0settingsHelp\0"
    "rxLedOn\0rxLedOff\0txLedOn\0txLedOff\0"
    "clearLog\0log\0msg\0show"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Komport[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    0,   85,    2, 0x08 /* Private */,
       4,    0,   86,    2, 0x08 /* Private */,
       5,    0,   87,    2, 0x08 /* Private */,
       6,    0,   88,    2, 0x08 /* Private */,
       7,    0,   89,    2, 0x08 /* Private */,
       8,    0,   90,    2, 0x08 /* Private */,
       9,    0,   91,    2, 0x08 /* Private */,
      10,    0,   92,    2, 0x08 /* Private */,
      11,    0,   93,    2, 0x08 /* Private */,
      12,    0,   94,    2, 0x08 /* Private */,
      13,    0,   95,    2, 0x08 /* Private */,
      14,    2,   96,    2, 0x08 /* Private */,
      14,    1,  101,    2, 0x28 /* Private | MethodCloned */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   15,   16,
    QMetaType::Void, QMetaType::QString,   15,

       0        // eod
};

void Komport::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Komport *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->about(); break;
        case 1: _t->editSettings(); break;
        case 2: _t->doCopy(); break;
        case 3: _t->doPaste(); break;
        case 4: _t->openBackgroundColorDialog(); break;
        case 5: _t->openForegroundColorDialog(); break;
        case 6: _t->settingsHelp(); break;
        case 7: _t->rxLedOn(); break;
        case 8: _t->rxLedOff(); break;
        case 9: _t->txLedOn(); break;
        case 10: _t->txLedOff(); break;
        case 11: _t->clearLog(); break;
        case 12: _t->log((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 13: _t->log((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Komport::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_Komport.data,
    qt_meta_data_Komport,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Komport::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Komport::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Komport.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Komport::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
