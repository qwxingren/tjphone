/****************************************************************************
** Meta object code from reading C++ file 'callviewframe.h'
**
** Created: Fri Apr 26 11:47:07 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../linphone-3.5.2/qt/callviewframe.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'callviewframe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CallViewFrame[] = {

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
      15,   14,   14,   14, 0x0a,
      49,   41,   14,   14, 0x0a,
      73,   14,   14,   14, 0x0a,
     101,   14,   14,   14, 0x08,
     132,   14,   14,   14, 0x08,
     164,   14,   14,   14, 0x08,
     193,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CallViewFrame[] = {
    "CallViewFrame\0\0transfer_button_clicked()\0"
    "_action\0transfer_call(QAction*)\0"
    "conference_button_clicked()\0"
    "on_pushButton_answer_clicked()\0"
    "on_pushButton_decline_clicked()\0"
    "on_pushButton_mute_clicked()\0"
    "on_pushButton_pause_clicked()\0"
};

void CallViewFrame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CallViewFrame *_t = static_cast<CallViewFrame *>(_o);
        switch (_id) {
        case 0: _t->transfer_button_clicked(); break;
        case 1: _t->transfer_call((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 2: _t->conference_button_clicked(); break;
        case 3: _t->on_pushButton_answer_clicked(); break;
        case 4: _t->on_pushButton_decline_clicked(); break;
        case 5: _t->on_pushButton_mute_clicked(); break;
        case 6: _t->on_pushButton_pause_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CallViewFrame::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CallViewFrame::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_CallViewFrame,
      qt_meta_data_CallViewFrame, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CallViewFrame::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CallViewFrame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CallViewFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CallViewFrame))
        return static_cast<void*>(const_cast< CallViewFrame*>(this));
    return QFrame::qt_metacast(_clname);
}

int CallViewFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
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
