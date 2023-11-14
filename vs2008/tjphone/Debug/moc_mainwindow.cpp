/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Fri Apr 26 11:47:05 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../linphone-3.5.2/qt/mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      35,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      34,   11,   11,   11, 0x0a,
      67,   59,   11,   11, 0x0a,
      93,   11,   11,   11, 0x0a,
     114,   11,   11,   11, 0x0a,
     143,   11,   11,   11, 0x08,
     170,   11,   11,   11, 0x08,
     203,   11,   11,   11, 0x08,
     236,   11,   11,   11, 0x08,
     264,   11,   11,   11, 0x08,
     299,   11,   11,   11, 0x08,
     339,   11,   11,   11, 0x08,
     373,   11,   11,   11, 0x08,
     404,   11,   11,   11, 0x08,
     435,   11,   11,   11, 0x08,
     452,   11,   11,   11, 0x08,
     469,   11,   11,   11, 0x08,
     486,   11,   11,   11, 0x08,
     503,   11,   11,   11, 0x08,
     520,   11,   11,   11, 0x08,
     537,   11,   11,   11, 0x08,
     554,   11,   11,   11, 0x08,
     571,   11,   11,   11, 0x08,
     588,   11,   11,   11, 0x08,
     605,   11,   11,   11, 0x08,
     629,   11,   11,   11, 0x08,
     650,   11,   11,   11, 0x08,
     667,   11,   11,   11, 0x08,
     684,   11,   11,   11, 0x08,
     701,   11,   11,   11, 0x08,
     718,   11,   11,   11, 0x08,
     740,  734,   11,   11, 0x08,
     790,  785,   11,   11, 0x08,
     841,  829,   11,   11, 0x08,
     876,  829,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0linphone_qt_iterate()\0"
    "linphone_qt_check_logs()\0_action\0"
    "set_my_presence(QAction*)\0"
    "show_presence_menu()\0on_toolButton_call_clicked()\0"
    "on_action_Quit_triggered()\0"
    "on_actionAudio_vedio_triggered()\0"
    "on_action_audio_only_triggered()\0"
    "on_action_About_triggered()\0"
    "on_action_Call_history_triggered()\0"
    "on_action_Show_debug_window_triggered()\0"
    "on_action_Preferences_triggered()\0"
    "on_action_Homepage_triggered()\0"
    "on_toolButton_Hangup_clicked()\0"
    "dtmf_pressed_0()\0dtmf_pressed_1()\0"
    "dtmf_pressed_2()\0dtmf_pressed_3()\0"
    "dtmf_pressed_4()\0dtmf_pressed_5()\0"
    "dtmf_pressed_6()\0dtmf_pressed_7()\0"
    "dtmf_pressed_8()\0dtmf_pressed_9()\0"
    "dtmf_pressed_asterisk()\0dtmf_pressed_pound()\0"
    "dtmf_pressed_A()\0dtmf_pressed_B()\0"
    "dtmf_pressed_C()\0dtmf_pressed_D()\0"
    "dtmf_released()\0index\0"
    "on_comboBox_account_currentIndexChanged(int)\0"
    "arg1\0on_actionEnable_selfview_toggled(bool)\0"
    "item,column\0tree_Clicked(QTreeWidgetItem*,int)\0"
    "tree_DoubleClicked(QTreeWidgetItem*,int)\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->linphone_qt_iterate(); break;
        case 1: _t->linphone_qt_check_logs(); break;
        case 2: _t->set_my_presence((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 3: _t->show_presence_menu(); break;
        case 4: _t->on_toolButton_call_clicked(); break;
        case 5: _t->on_action_Quit_triggered(); break;
        case 6: _t->on_actionAudio_vedio_triggered(); break;
        case 7: _t->on_action_audio_only_triggered(); break;
        case 8: _t->on_action_About_triggered(); break;
        case 9: _t->on_action_Call_history_triggered(); break;
        case 10: _t->on_action_Show_debug_window_triggered(); break;
        case 11: _t->on_action_Preferences_triggered(); break;
        case 12: _t->on_action_Homepage_triggered(); break;
        case 13: _t->on_toolButton_Hangup_clicked(); break;
        case 14: _t->dtmf_pressed_0(); break;
        case 15: _t->dtmf_pressed_1(); break;
        case 16: _t->dtmf_pressed_2(); break;
        case 17: _t->dtmf_pressed_3(); break;
        case 18: _t->dtmf_pressed_4(); break;
        case 19: _t->dtmf_pressed_5(); break;
        case 20: _t->dtmf_pressed_6(); break;
        case 21: _t->dtmf_pressed_7(); break;
        case 22: _t->dtmf_pressed_8(); break;
        case 23: _t->dtmf_pressed_9(); break;
        case 24: _t->dtmf_pressed_asterisk(); break;
        case 25: _t->dtmf_pressed_pound(); break;
        case 26: _t->dtmf_pressed_A(); break;
        case 27: _t->dtmf_pressed_B(); break;
        case 28: _t->dtmf_pressed_C(); break;
        case 29: _t->dtmf_pressed_D(); break;
        case 30: _t->dtmf_released(); break;
        case 31: _t->on_comboBox_account_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 32: _t->on_actionEnable_selfview_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 33: _t->tree_Clicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 34: _t->tree_DoubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 35)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 35;
    }
    return _id;
}
static const uint qt_meta_data_MyThread[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_MyThread[] = {
    "MyThread\0"
};

void MyThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData MyThread::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MyThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_MyThread,
      qt_meta_data_MyThread, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MyThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MyThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MyThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyThread))
        return static_cast<void*>(const_cast< MyThread*>(this));
    return QThread::qt_metacast(_clname);
}

int MyThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
