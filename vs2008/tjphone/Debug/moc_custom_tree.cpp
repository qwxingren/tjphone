/****************************************************************************
** Meta object code from reading C++ file 'custom_tree.h'
**
** Created: Fri Apr 26 11:47:06 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../linphone-3.5.2/qt/custom_tree.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'custom_tree.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_custom_tree[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x08,
      19,   12,   12,   12, 0x08,
      35,   12,   12,   12, 0x08,
      53,   12,   12,   12, 0x08,
      71,   12,   12,   12, 0x08,
      87,   12,   12,   12, 0x08,
     103,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_custom_tree[] = {
    "custom_tree\0\0add()\0edit_selected()\0"
    "remove_selected()\0wait_for_friend()\0"
    "chat_selected()\0call_selected()\0"
    "update_all()\0"
};

void custom_tree::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        custom_tree *_t = static_cast<custom_tree *>(_o);
        switch (_id) {
        case 0: _t->add(); break;
        case 1: _t->edit_selected(); break;
        case 2: _t->remove_selected(); break;
        case 3: _t->wait_for_friend(); break;
        case 4: _t->chat_selected(); break;
        case 5: _t->call_selected(); break;
        case 6: _t->update_all(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData custom_tree::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject custom_tree::staticMetaObject = {
    { &QTreeWidget::staticMetaObject, qt_meta_stringdata_custom_tree,
      qt_meta_data_custom_tree, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &custom_tree::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *custom_tree::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *custom_tree::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_custom_tree))
        return static_cast<void*>(const_cast< custom_tree*>(this));
    return QTreeWidget::qt_metacast(_clname);
}

int custom_tree::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
