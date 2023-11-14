/****************************************************************************
** Meta object code from reading C++ file 'sip_account.h'
**
** Created: Fri Apr 26 11:47:03 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../linphone-3.5.2/qt/sip_account.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sip_account.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SIP_Account[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x08,
      37,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SIP_Account[] = {
    "SIP_Account\0\0on_buttonBox_accepted()\0"
    "on_buttonBox_rejected()\0"
};

void SIP_Account::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SIP_Account *_t = static_cast<SIP_Account *>(_o);
        switch (_id) {
        case 0: _t->on_buttonBox_accepted(); break;
        case 1: _t->on_buttonBox_rejected(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData SIP_Account::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SIP_Account::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SIP_Account,
      qt_meta_data_SIP_Account, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SIP_Account::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SIP_Account::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SIP_Account::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SIP_Account))
        return static_cast<void*>(const_cast< SIP_Account*>(this));
    return QDialog::qt_metacast(_clname);
}

int SIP_Account::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
