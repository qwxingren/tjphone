/****************************************************************************
** Meta object code from reading C++ file 'preference.h'
**
** Created: Fri Apr 26 11:47:04 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../linphone-3.5.2/qt/preference.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'preference.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Preference[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      36,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      53,   46,   11,   11, 0x08,
     104,   98,   11,   11, 0x08,
     151,  140,   11,   11, 0x08,
     193,  185,   11,   11, 0x08,
     232,  227,   11,   11, 0x08,
     265,  227,   11,   11, 0x08,
     303,  227,   11,   11, 0x08,
     347,  227,   11,   11, 0x08,
     391,  185,   11,   11, 0x08,
     427,  185,   11,   11, 0x08,
     472,  227,   11,   11, 0x08,
     517,  185,   11,   11, 0x08,
     555,  227,   11,   11, 0x08,
     600,  227,   11,   11, 0x08,
     657,  227,   11,   11, 0x08,
     710,  227,   11,   11, 0x08,
     766,   11,   11,   11, 0x08,
     802,   11,   11,   11, 0x08,
     836,   11,   11,   11, 0x08,
     875,  227,   11,   11, 0x08,
     924,  227,   11,   11, 0x08,
     976,  227,   11,   11, 0x08,
    1021,  227,   11,   11, 0x08,
    1063,  227,   11,   11, 0x08,
    1108,   11,   11,   11, 0x08,
    1143,   11,   11,   11, 0x08,
    1180,   11,   11,   11, 0x08,
    1213,   11,   11,   11, 0x08,
    1248,   11,   11,   11, 0x08,
    1285,   11,   11,   11, 0x08,
    1323,  227,   11,   11, 0x08,
    1362,  227,   11,   11, 0x08,
    1403,  227,   11,   11, 0x08,
    1449,   98,   11,   11, 0x08,
    1497,   98,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Preference[] = {
    "Preference\0\0on_pushButton_add_proxy_clicked()\0"
    "button\0on_buttonBox_Apply_clicked(QAbstractButton*)\0"
    "index\0on_comboBox_codec_view_changed(int)\0"
    "checkstate\0on_checkBox_ui_level_changed(int)\0"
    "checked\0on_checkBox_mtu_set_toggled(bool)\0"
    "arg1\0on_spinBox_mtu_valueChanged(int)\0"
    "on_spinBox_sip_port_valueChanged(int)\0"
    "on_spinBox_audio_rtp_port_valueChanged(int)\0"
    "on_spinBox_video_rtp_port_valueChanged(int)\0"
    "on_radioButton_no_nat_toggled(bool)\0"
    "on_radioButton_use_nat_address_toggled(bool)\0"
    "on_lineEdit_nat_address_textChanged(QString)\0"
    "on_radioButton_use_stun_toggled(bool)\0"
    "on_lineEdit_stun_server_textChanged(QString)\0"
    "on_comboBox_playback_device_currentIndexChanged(QString)\0"
    "on_comboBox_ring_device_currentIndexChanged(QString)\0"
    "on_comboBox_capture_device_currentIndexChanged(QString)\0"
    "on_pushButton_choose_file_clicked()\0"
    "on_toolButton_play_ring_clicked()\0"
    "on_checkBox_echo_cancelation_clicked()\0"
    "on_comboBox_webcams_currentIndexChanged(QString)\0"
    "on_comboBox_video_size_currentIndexChanged(QString)\0"
    "on_lineEdit_displayname_textChanged(QString)\0"
    "on_lineEdit_username_textChanged(QString)\0"
    "on_lineEdit_sip_address_textChanged(QString)\0"
    "on_pushButton_edit_proxy_clicked()\0"
    "on_pushButton_remove_proxy_clicked()\0"
    "on_pushButton_up_codec_clicked()\0"
    "on_pushButton_down_codec_clicked()\0"
    "on_pushButton_enable_codec_clicked()\0"
    "on_pushButton_disable_codec_clicked()\0"
    "on_spinBox_upload_bw_valueChanged(int)\0"
    "on_spinBox_download_bw_valueChanged(int)\0"
    "on_comboBox_lang_currentIndexChanged(QString)\0"
    "on_comboBox_video_size_currentIndexChanged(int)\0"
    "on_comboBox_proto_currentIndexChanged(int)\0"
};

void Preference::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Preference *_t = static_cast<Preference *>(_o);
        switch (_id) {
        case 0: _t->on_pushButton_add_proxy_clicked(); break;
        case 1: _t->on_buttonBox_Apply_clicked((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 2: _t->on_comboBox_codec_view_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_checkBox_ui_level_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_checkBox_mtu_set_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_spinBox_mtu_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_spinBox_sip_port_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_spinBox_audio_rtp_port_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_spinBox_video_rtp_port_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_radioButton_no_nat_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->on_radioButton_use_nat_address_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->on_lineEdit_nat_address_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->on_radioButton_use_stun_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->on_lineEdit_stun_server_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 14: _t->on_comboBox_playback_device_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 15: _t->on_comboBox_ring_device_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 16: _t->on_comboBox_capture_device_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 17: _t->on_pushButton_choose_file_clicked(); break;
        case 18: _t->on_toolButton_play_ring_clicked(); break;
        case 19: _t->on_checkBox_echo_cancelation_clicked(); break;
        case 20: _t->on_comboBox_webcams_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 21: _t->on_comboBox_video_size_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 22: _t->on_lineEdit_displayname_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 23: _t->on_lineEdit_username_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 24: _t->on_lineEdit_sip_address_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 25: _t->on_pushButton_edit_proxy_clicked(); break;
        case 26: _t->on_pushButton_remove_proxy_clicked(); break;
        case 27: _t->on_pushButton_up_codec_clicked(); break;
        case 28: _t->on_pushButton_down_codec_clicked(); break;
        case 29: _t->on_pushButton_enable_codec_clicked(); break;
        case 30: _t->on_pushButton_disable_codec_clicked(); break;
        case 31: _t->on_spinBox_upload_bw_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 32: _t->on_spinBox_download_bw_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 33: _t->on_comboBox_lang_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 34: _t->on_comboBox_video_size_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 35: _t->on_comboBox_proto_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Preference::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Preference::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Preference,
      qt_meta_data_Preference, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Preference::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Preference::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Preference::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Preference))
        return static_cast<void*>(const_cast< Preference*>(this));
    return QDialog::qt_metacast(_clname);
}

int Preference::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 36)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 36;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
