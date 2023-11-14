/****************************************************************************
** Meta object code from reading C++ file 'friend_list.h'
**
** Created: Fri Apr 26 11:47:05 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../linphone-3.5.2/qt/friend_list.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'friend_list.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_friend_list[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,
      33,   23,   12,   12, 0x05,
      54,   48,   12,   12, 0x05,
      78,   12,   12,   12, 0x05,
     116,   92,   12,   12, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_friend_list[] = {
    "friend_list\0\0changed()\0nick_name\0"
    "added(QString)\0nicks\0removed(QList<QString>)\0"
    "removed_all()\0old_nick_name,nick_name\0"
    "changed(QString,QString)\0"
};

void friend_list::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        friend_list *_t = static_cast<friend_list *>(_o);
        switch (_id) {
        case 0: _t->changed(); break;
        case 1: _t->added((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->removed((*reinterpret_cast< const QList<QString>(*)>(_a[1]))); break;
        case 3: _t->removed_all(); break;
        case 4: _t->changed((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData friend_list::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject friend_list::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_friend_list,
      qt_meta_data_friend_list, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &friend_list::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *friend_list::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *friend_list::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_friend_list))
        return static_cast<void*>(const_cast< friend_list*>(this));
    return QObject::qt_metacast(_clname);
}

int friend_list::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void friend_list::changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void friend_list::added(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void friend_list::removed(const QList<QString> & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void friend_list::removed_all()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void friend_list::changed(const QString & _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
