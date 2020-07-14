/****************************************************************************
** Meta object code from reading C++ file 'ccellarray.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "ccellarray.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ccellarray.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CCellArray_t {
    QByteArrayData data[29];
    char stringdata0[224];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CCellArray_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CCellArray_t qt_meta_stringdata_CCellArray = {
    {
QT_MOC_LITERAL(0, 0, 10), // "CCellArray"
QT_MOC_LITERAL(1, 11, 9), // "setScreen"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 8), // "CScreen*"
QT_MOC_LITERAL(4, 31, 6), // "screen"
QT_MOC_LITERAL(5, 38, 7), // "setRect"
QT_MOC_LITERAL(6, 46, 1), // "r"
QT_MOC_LITERAL(7, 48, 7), // "setGrid"
QT_MOC_LITERAL(8, 56, 4), // "cols"
QT_MOC_LITERAL(9, 61, 4), // "rows"
QT_MOC_LITERAL(10, 66, 7), // "setCols"
QT_MOC_LITERAL(11, 74, 7), // "setRows"
QT_MOC_LITERAL(12, 82, 4), // "draw"
QT_MOC_LITERAL(13, 87, 9), // "QPainter&"
QT_MOC_LITERAL(14, 97, 7), // "painter"
QT_MOC_LITERAL(15, 105, 4), // "rect"
QT_MOC_LITERAL(16, 110, 10), // "scrollGrid"
QT_MOC_LITERAL(17, 121, 22), // "CCellArray::ScrollMode"
QT_MOC_LITERAL(18, 144, 4), // "mode"
QT_MOC_LITERAL(19, 149, 1), // "x"
QT_MOC_LITERAL(20, 151, 1), // "y"
QT_MOC_LITERAL(21, 153, 5), // "width"
QT_MOC_LITERAL(22, 159, 6), // "height"
QT_MOC_LITERAL(23, 166, 4), // "sync"
QT_MOC_LITERAL(24, 171, 14), // "appendScrolled"
QT_MOC_LITERAL(25, 186, 5), // "CCell"
QT_MOC_LITERAL(26, 192, 4), // "cell"
QT_MOC_LITERAL(27, 197, 13), // "resetScrolled"
QT_MOC_LITERAL(28, 211, 12) // "trimScrolled"

    },
    "CCellArray\0setScreen\0\0CScreen*\0screen\0"
    "setRect\0r\0setGrid\0cols\0rows\0setCols\0"
    "setRows\0draw\0QPainter&\0painter\0rect\0"
    "scrollGrid\0CCellArray::ScrollMode\0"
    "mode\0x\0y\0width\0height\0sync\0appendScrolled\0"
    "CCell\0cell\0resetScrolled\0trimScrolled"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CCellArray[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x0a /* Public */,
       5,    1,   77,    2, 0x0a /* Public */,
       7,    2,   80,    2, 0x0a /* Public */,
      10,    1,   85,    2, 0x0a /* Public */,
      11,    1,   88,    2, 0x0a /* Public */,
      12,    2,   91,    2, 0x0a /* Public */,
      12,    1,   96,    2, 0x0a /* Public */,
      16,    5,   99,    2, 0x0a /* Public */,
      23,    0,  110,    2, 0x0a /* Public */,
      24,    1,  111,    2, 0x09 /* Protected */,
      27,    0,  114,    2, 0x09 /* Protected */,
      28,    0,  115,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QRect,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    8,    9,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, 0x80000000 | 13, QMetaType::QRect,   14,   15,
    QMetaType::Void, QMetaType::QRect,   15,
    QMetaType::Void, 0x80000000 | 17, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   18,   19,   20,   21,   22,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 25,   26,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CCellArray::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CCellArray *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setScreen((*reinterpret_cast< CScreen*(*)>(_a[1]))); break;
        case 1: _t->setRect((*reinterpret_cast< QRect(*)>(_a[1]))); break;
        case 2: _t->setGrid((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->setCols((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->setRows((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->draw((*reinterpret_cast< QPainter(*)>(_a[1])),(*reinterpret_cast< const QRect(*)>(_a[2]))); break;
        case 6: _t->draw((*reinterpret_cast< const QRect(*)>(_a[1]))); break;
        case 7: _t->scrollGrid((*reinterpret_cast< CCellArray::ScrollMode(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 8: _t->sync(); break;
        case 9: _t->appendScrolled((*reinterpret_cast< CCell(*)>(_a[1]))); break;
        case 10: _t->resetScrolled(); break;
        case 11: _t->trimScrolled(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CCellArray::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CCellArray.data,
    qt_meta_data_CCellArray,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CCellArray::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CCellArray::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CCellArray.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CCellArray::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
