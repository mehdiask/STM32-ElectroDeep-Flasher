/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Widget_t {
    QByteArrayData data[16];
    char stringdata0[309];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Widget_t qt_meta_stringdata_Widget = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Widget"
QT_MOC_LITERAL(1, 7, 29), // "on_pushButton_Connect_clicked"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 32), // "on_pushButton_Disconnect_clicked"
QT_MOC_LITERAL(4, 71, 29), // "on_pushButton_Refresh_clicked"
QT_MOC_LITERAL(5, 101, 27), // "on_pushButton_Clear_clicked"
QT_MOC_LITERAL(6, 129, 30), // "on_pushButton_flashRun_clicked"
QT_MOC_LITERAL(7, 160, 28), // "on_pushButton_Browse_clicked"
QT_MOC_LITERAL(8, 189, 17), // "onProgressChanged"
QT_MOC_LITERAL(9, 207, 10), // "percentage"
QT_MOC_LITERAL(10, 218, 17), // "onMessageReceived"
QT_MOC_LITERAL(11, 236, 7), // "message"
QT_MOC_LITERAL(12, 244, 20), // "onOperationCompleted"
QT_MOC_LITERAL(13, 265, 7), // "success"
QT_MOC_LITERAL(14, 273, 25), // "onConnectionStatusChanged"
QT_MOC_LITERAL(15, 299, 9) // "connected"

    },
    "Widget\0on_pushButton_Connect_clicked\0"
    "\0on_pushButton_Disconnect_clicked\0"
    "on_pushButton_Refresh_clicked\0"
    "on_pushButton_Clear_clicked\0"
    "on_pushButton_flashRun_clicked\0"
    "on_pushButton_Browse_clicked\0"
    "onProgressChanged\0percentage\0"
    "onMessageReceived\0message\0"
    "onOperationCompleted\0success\0"
    "onConnectionStatusChanged\0connected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Widget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    0,   69,    2, 0x08 /* Private */,
       8,    1,   70,    2, 0x08 /* Private */,
      10,    1,   73,    2, 0x08 /* Private */,
      12,    2,   76,    2, 0x08 /* Private */,
      14,    1,   81,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,   13,   11,
    QMetaType::Void, QMetaType::Bool,   15,

       0        // eod
};

void Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_Connect_clicked(); break;
        case 1: _t->on_pushButton_Disconnect_clicked(); break;
        case 2: _t->on_pushButton_Refresh_clicked(); break;
        case 3: _t->on_pushButton_Clear_clicked(); break;
        case 4: _t->on_pushButton_flashRun_clicked(); break;
        case 5: _t->on_pushButton_Browse_clicked(); break;
        case 6: _t->onProgressChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->onMessageReceived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->onOperationCompleted((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 9: _t->onConnectionStatusChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Widget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_Widget.data,
    qt_meta_data_Widget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Widget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
