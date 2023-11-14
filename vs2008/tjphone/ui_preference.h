/********************************************************************************
** Form generated from reading UI file 'preference.ui'
**
** Created: Fri Apr 26 11:47:09 2013
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREFERENCE_H
#define UI_PREFERENCE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QTableView>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Preference
{
public:
    QGridLayout *gridLayout;
    QDialogButtonBox *buttonBox_Apply;
    QTabWidget *tabPreference;
    QWidget *tabNetWork;
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox_ports;
    QGridLayout *gridLayout_3;
    QSpinBox *spinBox_sip_port;
    QLabel *label_3;
    QSpinBox *spinBox_audio_rtp_port;
    QLabel *label_4;
    QSpinBox *spinBox_video_rtp_port;
    QComboBox *comboBox_proto;
    QGroupBox *groupBox_transport;
    QGridLayout *gridLayout_5;
    QCheckBox *checkBox_mtu_set;
    QSpinBox *spinBox_mtu;
    QCheckBox *checkBox_dtmf_sipinfo;
    QCheckBox *checkBox_ipv6;
    QGroupBox *groupBox_nat;
    QGridLayout *gridLayout_2;
    QRadioButton *radioButton_no_nat;
    QRadioButton *radioButton_use_nat_address;
    QLabel *label_5;
    QRadioButton *radioButton_use_stun;
    QLabel *label_6;
    QLineEdit *lineEdit_stun_server;
    QLineEdit *lineEdit_nat_address;
    QWidget *tabMultimedia;
    QGridLayout *gridLayout_6;
    QGroupBox *groupBox_audio;
    QGridLayout *gridLayout_7;
    QLabel *label_7;
    QComboBox *comboBox_playback_device;
    QLabel *label_8;
    QComboBox *comboBox_ring_device;
    QLabel *label_9;
    QComboBox *comboBox_capture_device;
    QLabel *label_10;
    QLineEdit *lineEdit_ring_file;
    QToolButton *toolButton_play_ring;
    QPushButton *pushButton_choose_file;
    QCheckBox *checkBox_echo_cancelation;
    QGroupBox *groupBox_video;
    QGridLayout *gridLayout_8;
    QLabel *label_11;
    QComboBox *comboBox_webcams;
    QLabel *label_12;
    QComboBox *comboBox_video_size;
    QWidget *tabSIP;
    QGridLayout *gridLayout_12;
    QGroupBox *groupBox_identity;
    QGridLayout *gridLayout_9;
    QLabel *label_13;
    QLineEdit *lineEdit_displayname;
    QLabel *label_14;
    QLineEdit *lineEdit_username;
    QLabel *label_15;
    QLineEdit *lineEdit_sip_address;
    QGroupBox *groupBox_proxy;
    QGridLayout *gridLayout_10;
    QListView *listView_proxy_list;
    QPushButton *pushButton_add_proxy;
    QPushButton *pushButton_edit_proxy;
    QPushButton *pushButton_remove_proxy;
    QGroupBox *groupBox_8;
    QGridLayout *gridLayout_11;
    QPushButton *pushButton_2;
    QWidget *tabCodecs;
    QGridLayout *gridLayout_13;
    QGroupBox *groupBox_BW;
    QGridLayout *gridLayout_15;
    QLabel *label_16;
    QSpinBox *spinBox_upload_bw;
    QLabel *label_17;
    QSpinBox *spinBox_download_bw;
    QGroupBox *groupBox_codec;
    QGridLayout *gridLayout_14;
    QComboBox *comboBox_codec_view;
    QTableView *tableView_codec;
    QPushButton *pushButton_up_codec;
    QPushButton *pushButton_down_codec;
    QPushButton *pushButton_enable_codec;
    QPushButton *pushButton_disable_codec;
    QWidget *tabInterface;
    QFormLayout *formLayout;
    QGroupBox *groupBox_11;
    QGridLayout *gridLayout_16;
    QComboBox *comboBox_lang;
    QGroupBox *groupBox_12;
    QGridLayout *gridLayout_17;
    QCheckBox *checkBox_ui_level;

    void setupUi(QDialog *Preference)
    {
        if (Preference->objectName().isEmpty())
            Preference->setObjectName(QString::fromUtf8("Preference"));
        Preference->resize(579, 465);
        gridLayout = new QGridLayout(Preference);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        buttonBox_Apply = new QDialogButtonBox(Preference);
        buttonBox_Apply->setObjectName(QString::fromUtf8("buttonBox_Apply"));
        buttonBox_Apply->setOrientation(Qt::Horizontal);
        buttonBox_Apply->setStandardButtons(QDialogButtonBox::Apply);

        gridLayout->addWidget(buttonBox_Apply, 3, 0, 1, 1);

        tabPreference = new QTabWidget(Preference);
        tabPreference->setObjectName(QString::fromUtf8("tabPreference"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabPreference->sizePolicy().hasHeightForWidth());
        tabPreference->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font.setBold(false);
        font.setWeight(50);
        tabPreference->setFont(font);
        tabPreference->setLayoutDirection(Qt::LeftToRight);
        tabNetWork = new QWidget();
        tabNetWork->setObjectName(QString::fromUtf8("tabNetWork"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabNetWork->sizePolicy().hasHeightForWidth());
        tabNetWork->setSizePolicy(sizePolicy1);
        gridLayout_4 = new QGridLayout(tabNetWork);
        gridLayout_4->setSpacing(0);
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        groupBox_ports = new QGroupBox(tabNetWork);
        groupBox_ports->setObjectName(QString::fromUtf8("groupBox_ports"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox_ports->sizePolicy().hasHeightForWidth());
        groupBox_ports->setSizePolicy(sizePolicy2);
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        groupBox_ports->setFont(font1);
        gridLayout_3 = new QGridLayout(groupBox_ports);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        spinBox_sip_port = new QSpinBox(groupBox_ports);
        spinBox_sip_port->setObjectName(QString::fromUtf8("spinBox_sip_port"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(spinBox_sip_port->sizePolicy().hasHeightForWidth());
        spinBox_sip_port->setSizePolicy(sizePolicy3);
        QFont font2;
        font2.setBold(false);
        font2.setWeight(50);
        spinBox_sip_port->setFont(font2);
        spinBox_sip_port->setAutoFillBackground(true);
        spinBox_sip_port->setFrame(true);
        spinBox_sip_port->setMaximum(65536);

        gridLayout_3->addWidget(spinBox_sip_port, 1, 1, 1, 1);

        label_3 = new QLabel(groupBox_ports);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font2);
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_3, 2, 0, 1, 1);

        spinBox_audio_rtp_port = new QSpinBox(groupBox_ports);
        spinBox_audio_rtp_port->setObjectName(QString::fromUtf8("spinBox_audio_rtp_port"));
        spinBox_audio_rtp_port->setFont(font2);
        spinBox_audio_rtp_port->setMaximum(65536);

        gridLayout_3->addWidget(spinBox_audio_rtp_port, 2, 1, 1, 1);

        label_4 = new QLabel(groupBox_ports);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font2);
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_4, 3, 0, 1, 1);

        spinBox_video_rtp_port = new QSpinBox(groupBox_ports);
        spinBox_video_rtp_port->setObjectName(QString::fromUtf8("spinBox_video_rtp_port"));
        spinBox_video_rtp_port->setFont(font2);
        spinBox_video_rtp_port->setMaximum(65536);

        gridLayout_3->addWidget(spinBox_video_rtp_port, 3, 1, 1, 1);

        comboBox_proto = new QComboBox(groupBox_ports);
        comboBox_proto->setObjectName(QString::fromUtf8("comboBox_proto"));
        comboBox_proto->setLayoutDirection(Qt::LeftToRight);
        comboBox_proto->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);

        gridLayout_3->addWidget(comboBox_proto, 1, 0, 1, 1);


        gridLayout_4->addWidget(groupBox_ports, 1, 0, 1, 1);

        groupBox_transport = new QGroupBox(tabNetWork);
        groupBox_transport->setObjectName(QString::fromUtf8("groupBox_transport"));
        sizePolicy2.setHeightForWidth(groupBox_transport->sizePolicy().hasHeightForWidth());
        groupBox_transport->setSizePolicy(sizePolicy2);
        groupBox_transport->setFont(font1);
        gridLayout_5 = new QGridLayout(groupBox_transport);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        checkBox_mtu_set = new QCheckBox(groupBox_transport);
        checkBox_mtu_set->setObjectName(QString::fromUtf8("checkBox_mtu_set"));
        checkBox_mtu_set->setFont(font2);

        gridLayout_5->addWidget(checkBox_mtu_set, 0, 0, 1, 1);

        spinBox_mtu = new QSpinBox(groupBox_transport);
        spinBox_mtu->setObjectName(QString::fromUtf8("spinBox_mtu"));
        spinBox_mtu->setFont(font2);
        spinBox_mtu->setMaximum(65536);

        gridLayout_5->addWidget(spinBox_mtu, 0, 1, 1, 1);

        checkBox_dtmf_sipinfo = new QCheckBox(groupBox_transport);
        checkBox_dtmf_sipinfo->setObjectName(QString::fromUtf8("checkBox_dtmf_sipinfo"));
        checkBox_dtmf_sipinfo->setFont(font2);

        gridLayout_5->addWidget(checkBox_dtmf_sipinfo, 1, 0, 1, 1);

        checkBox_ipv6 = new QCheckBox(groupBox_transport);
        checkBox_ipv6->setObjectName(QString::fromUtf8("checkBox_ipv6"));
        checkBox_ipv6->setFont(font2);

        gridLayout_5->addWidget(checkBox_ipv6, 2, 0, 1, 1);


        gridLayout_4->addWidget(groupBox_transport, 0, 0, 1, 1);

        groupBox_nat = new QGroupBox(tabNetWork);
        groupBox_nat->setObjectName(QString::fromUtf8("groupBox_nat"));
        sizePolicy2.setHeightForWidth(groupBox_nat->sizePolicy().hasHeightForWidth());
        groupBox_nat->setSizePolicy(sizePolicy2);
        groupBox_nat->setFont(font1);
        gridLayout_2 = new QGridLayout(groupBox_nat);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        radioButton_no_nat = new QRadioButton(groupBox_nat);
        radioButton_no_nat->setObjectName(QString::fromUtf8("radioButton_no_nat"));
        radioButton_no_nat->setFont(font2);

        gridLayout_2->addWidget(radioButton_no_nat, 0, 0, 1, 3);

        radioButton_use_nat_address = new QRadioButton(groupBox_nat);
        radioButton_use_nat_address->setObjectName(QString::fromUtf8("radioButton_use_nat_address"));
        radioButton_use_nat_address->setFont(font2);

        gridLayout_2->addWidget(radioButton_use_nat_address, 1, 0, 1, 3);

        label_5 = new QLabel(groupBox_nat);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font2);

        gridLayout_2->addWidget(label_5, 2, 0, 1, 1);

        radioButton_use_stun = new QRadioButton(groupBox_nat);
        radioButton_use_stun->setObjectName(QString::fromUtf8("radioButton_use_stun"));
        radioButton_use_stun->setFont(font2);

        gridLayout_2->addWidget(radioButton_use_stun, 3, 0, 1, 3);

        label_6 = new QLabel(groupBox_nat);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font2);

        gridLayout_2->addWidget(label_6, 4, 0, 1, 1);

        lineEdit_stun_server = new QLineEdit(groupBox_nat);
        lineEdit_stun_server->setObjectName(QString::fromUtf8("lineEdit_stun_server"));
        lineEdit_stun_server->setFont(font2);

        gridLayout_2->addWidget(lineEdit_stun_server, 4, 1, 1, 1);

        lineEdit_nat_address = new QLineEdit(groupBox_nat);
        lineEdit_nat_address->setObjectName(QString::fromUtf8("lineEdit_nat_address"));
        lineEdit_nat_address->setFont(font2);

        gridLayout_2->addWidget(lineEdit_nat_address, 2, 1, 1, 1);


        gridLayout_4->addWidget(groupBox_nat, 2, 0, 1, 1);

        tabPreference->addTab(tabNetWork, QString());
        tabMultimedia = new QWidget();
        tabMultimedia->setObjectName(QString::fromUtf8("tabMultimedia"));
        sizePolicy1.setHeightForWidth(tabMultimedia->sizePolicy().hasHeightForWidth());
        tabMultimedia->setSizePolicy(sizePolicy1);
        gridLayout_6 = new QGridLayout(tabMultimedia);
        gridLayout_6->setSpacing(0);
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        groupBox_audio = new QGroupBox(tabMultimedia);
        groupBox_audio->setObjectName(QString::fromUtf8("groupBox_audio"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(groupBox_audio->sizePolicy().hasHeightForWidth());
        groupBox_audio->setSizePolicy(sizePolicy4);
        groupBox_audio->setFont(font1);
        gridLayout_7 = new QGridLayout(groupBox_audio);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        label_7 = new QLabel(groupBox_audio);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font2);
        label_7->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_7, 0, 0, 1, 1);

        comboBox_playback_device = new QComboBox(groupBox_audio);
        comboBox_playback_device->setObjectName(QString::fromUtf8("comboBox_playback_device"));
        comboBox_playback_device->setFont(font2);

        gridLayout_7->addWidget(comboBox_playback_device, 0, 1, 1, 4);

        label_8 = new QLabel(groupBox_audio);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font2);
        label_8->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_8, 1, 0, 1, 1);

        comboBox_ring_device = new QComboBox(groupBox_audio);
        comboBox_ring_device->setObjectName(QString::fromUtf8("comboBox_ring_device"));
        comboBox_ring_device->setFont(font2);

        gridLayout_7->addWidget(comboBox_ring_device, 1, 1, 1, 4);

        label_9 = new QLabel(groupBox_audio);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setFont(font2);
        label_9->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_9, 2, 0, 1, 1);

        comboBox_capture_device = new QComboBox(groupBox_audio);
        comboBox_capture_device->setObjectName(QString::fromUtf8("comboBox_capture_device"));
        comboBox_capture_device->setFont(font2);

        gridLayout_7->addWidget(comboBox_capture_device, 2, 1, 1, 4);

        label_10 = new QLabel(groupBox_audio);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setFont(font2);
        label_10->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_10, 3, 0, 1, 1);

        lineEdit_ring_file = new QLineEdit(groupBox_audio);
        lineEdit_ring_file->setObjectName(QString::fromUtf8("lineEdit_ring_file"));
        lineEdit_ring_file->setFont(font2);

        gridLayout_7->addWidget(lineEdit_ring_file, 3, 1, 1, 1);

        toolButton_play_ring = new QToolButton(groupBox_audio);
        toolButton_play_ring->setObjectName(QString::fromUtf8("toolButton_play_ring"));
        toolButton_play_ring->setFont(font2);

        gridLayout_7->addWidget(toolButton_play_ring, 3, 3, 1, 1);

        pushButton_choose_file = new QPushButton(groupBox_audio);
        pushButton_choose_file->setObjectName(QString::fromUtf8("pushButton_choose_file"));
        pushButton_choose_file->setFont(font2);

        gridLayout_7->addWidget(pushButton_choose_file, 3, 2, 1, 1);

        checkBox_echo_cancelation = new QCheckBox(groupBox_audio);
        checkBox_echo_cancelation->setObjectName(QString::fromUtf8("checkBox_echo_cancelation"));
        checkBox_echo_cancelation->setEnabled(true);
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(checkBox_echo_cancelation->sizePolicy().hasHeightForWidth());
        checkBox_echo_cancelation->setSizePolicy(sizePolicy5);
        checkBox_echo_cancelation->setFont(font2);
        checkBox_echo_cancelation->setMouseTracking(false);
        checkBox_echo_cancelation->setCheckable(true);
        checkBox_echo_cancelation->setChecked(false);
        checkBox_echo_cancelation->setTristate(false);

        gridLayout_7->addWidget(checkBox_echo_cancelation, 4, 1, 1, 1);


        gridLayout_6->addWidget(groupBox_audio, 0, 0, 1, 1);

        groupBox_video = new QGroupBox(tabMultimedia);
        groupBox_video->setObjectName(QString::fromUtf8("groupBox_video"));
        sizePolicy4.setHeightForWidth(groupBox_video->sizePolicy().hasHeightForWidth());
        groupBox_video->setSizePolicy(sizePolicy4);
        groupBox_video->setFont(font1);
        gridLayout_8 = new QGridLayout(groupBox_video);
        gridLayout_8->setSpacing(0);
        gridLayout_8->setContentsMargins(0, 0, 0, 0);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        label_11 = new QLabel(groupBox_video);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setFont(font2);
        label_11->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(label_11, 0, 0, 1, 1);

        comboBox_webcams = new QComboBox(groupBox_video);
        comboBox_webcams->setObjectName(QString::fromUtf8("comboBox_webcams"));
        comboBox_webcams->setFont(font2);

        gridLayout_8->addWidget(comboBox_webcams, 0, 1, 1, 1);

        label_12 = new QLabel(groupBox_video);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setFont(font2);
        label_12->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(label_12, 1, 0, 1, 1);

        comboBox_video_size = new QComboBox(groupBox_video);
        comboBox_video_size->setObjectName(QString::fromUtf8("comboBox_video_size"));
        comboBox_video_size->setFont(font2);

        gridLayout_8->addWidget(comboBox_video_size, 1, 1, 1, 1);


        gridLayout_6->addWidget(groupBox_video, 1, 0, 1, 1);

        tabPreference->addTab(tabMultimedia, QString());
        tabSIP = new QWidget();
        tabSIP->setObjectName(QString::fromUtf8("tabSIP"));
        gridLayout_12 = new QGridLayout(tabSIP);
        gridLayout_12->setSpacing(0);
        gridLayout_12->setContentsMargins(0, 0, 0, 0);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        groupBox_identity = new QGroupBox(tabSIP);
        groupBox_identity->setObjectName(QString::fromUtf8("groupBox_identity"));
        QSizePolicy sizePolicy6(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(groupBox_identity->sizePolicy().hasHeightForWidth());
        groupBox_identity->setSizePolicy(sizePolicy6);
        groupBox_identity->setFont(font1);
        groupBox_identity->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        gridLayout_9 = new QGridLayout(groupBox_identity);
        gridLayout_9->setSpacing(3);
        gridLayout_9->setContentsMargins(3, 3, 3, 3);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        gridLayout_9->setSizeConstraint(QLayout::SetDefaultConstraint);
        label_13 = new QLabel(groupBox_identity);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setFont(font2);
        label_13->setAlignment(Qt::AlignCenter);

        gridLayout_9->addWidget(label_13, 0, 0, 1, 1);

        lineEdit_displayname = new QLineEdit(groupBox_identity);
        lineEdit_displayname->setObjectName(QString::fromUtf8("lineEdit_displayname"));

        gridLayout_9->addWidget(lineEdit_displayname, 0, 1, 1, 1);

        label_14 = new QLabel(groupBox_identity);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setFont(font2);
        label_14->setAlignment(Qt::AlignCenter);

        gridLayout_9->addWidget(label_14, 1, 0, 1, 1);

        lineEdit_username = new QLineEdit(groupBox_identity);
        lineEdit_username->setObjectName(QString::fromUtf8("lineEdit_username"));

        gridLayout_9->addWidget(lineEdit_username, 1, 1, 1, 1);

        label_15 = new QLabel(groupBox_identity);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setFont(font2);
        label_15->setAlignment(Qt::AlignCenter);

        gridLayout_9->addWidget(label_15, 2, 0, 1, 1);

        lineEdit_sip_address = new QLineEdit(groupBox_identity);
        lineEdit_sip_address->setObjectName(QString::fromUtf8("lineEdit_sip_address"));
        lineEdit_sip_address->setReadOnly(true);

        gridLayout_9->addWidget(lineEdit_sip_address, 2, 1, 1, 1);


        gridLayout_12->addWidget(groupBox_identity, 0, 0, 1, 1);

        groupBox_proxy = new QGroupBox(tabSIP);
        groupBox_proxy->setObjectName(QString::fromUtf8("groupBox_proxy"));
        groupBox_proxy->setFont(font1);
        gridLayout_10 = new QGridLayout(groupBox_proxy);
        gridLayout_10->setSpacing(3);
        gridLayout_10->setContentsMargins(3, 3, 3, 3);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        listView_proxy_list = new QListView(groupBox_proxy);
        listView_proxy_list->setObjectName(QString::fromUtf8("listView_proxy_list"));
        QSizePolicy sizePolicy7(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(listView_proxy_list->sizePolicy().hasHeightForWidth());
        listView_proxy_list->setSizePolicy(sizePolicy7);
        listView_proxy_list->setFont(font2);

        gridLayout_10->addWidget(listView_proxy_list, 0, 0, 3, 1);

        pushButton_add_proxy = new QPushButton(groupBox_proxy);
        pushButton_add_proxy->setObjectName(QString::fromUtf8("pushButton_add_proxy"));
        pushButton_add_proxy->setFont(font2);

        gridLayout_10->addWidget(pushButton_add_proxy, 0, 1, 1, 1);

        pushButton_edit_proxy = new QPushButton(groupBox_proxy);
        pushButton_edit_proxy->setObjectName(QString::fromUtf8("pushButton_edit_proxy"));
        pushButton_edit_proxy->setFont(font2);

        gridLayout_10->addWidget(pushButton_edit_proxy, 1, 1, 1, 1);

        pushButton_remove_proxy = new QPushButton(groupBox_proxy);
        pushButton_remove_proxy->setObjectName(QString::fromUtf8("pushButton_remove_proxy"));
        pushButton_remove_proxy->setFont(font2);

        gridLayout_10->addWidget(pushButton_remove_proxy, 2, 1, 1, 1);


        gridLayout_12->addWidget(groupBox_proxy, 1, 0, 1, 1);

        groupBox_8 = new QGroupBox(tabSIP);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        sizePolicy6.setHeightForWidth(groupBox_8->sizePolicy().hasHeightForWidth());
        groupBox_8->setSizePolicy(sizePolicy6);
        groupBox_8->setFont(font1);
        gridLayout_11 = new QGridLayout(groupBox_8);
        gridLayout_11->setSpacing(3);
        gridLayout_11->setContentsMargins(3, 3, 3, 3);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        pushButton_2 = new QPushButton(groupBox_8);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setFont(font2);

        gridLayout_11->addWidget(pushButton_2, 0, 0, 1, 1);


        gridLayout_12->addWidget(groupBox_8, 2, 0, 1, 1);

        tabPreference->addTab(tabSIP, QString());
        tabCodecs = new QWidget();
        tabCodecs->setObjectName(QString::fromUtf8("tabCodecs"));
        gridLayout_13 = new QGridLayout(tabCodecs);
        gridLayout_13->setSpacing(0);
        gridLayout_13->setContentsMargins(0, 0, 0, 0);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        groupBox_BW = new QGroupBox(tabCodecs);
        groupBox_BW->setObjectName(QString::fromUtf8("groupBox_BW"));
        sizePolicy6.setHeightForWidth(groupBox_BW->sizePolicy().hasHeightForWidth());
        groupBox_BW->setSizePolicy(sizePolicy6);
        groupBox_BW->setFont(font1);
        gridLayout_15 = new QGridLayout(groupBox_BW);
#ifndef Q_OS_MAC
        gridLayout_15->setSpacing(6);
#endif
        gridLayout_15->setContentsMargins(3, 3, 3, 3);
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
        label_16 = new QLabel(groupBox_BW);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setFont(font2);
        label_16->setAlignment(Qt::AlignCenter);

        gridLayout_15->addWidget(label_16, 0, 0, 1, 1);

        spinBox_upload_bw = new QSpinBox(groupBox_BW);
        spinBox_upload_bw->setObjectName(QString::fromUtf8("spinBox_upload_bw"));
        spinBox_upload_bw->setFont(font2);
        spinBox_upload_bw->setMaximum(65536);

        gridLayout_15->addWidget(spinBox_upload_bw, 0, 1, 1, 1);

        label_17 = new QLabel(groupBox_BW);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setFont(font2);
        label_17->setAlignment(Qt::AlignCenter);

        gridLayout_15->addWidget(label_17, 1, 0, 1, 1);

        spinBox_download_bw = new QSpinBox(groupBox_BW);
        spinBox_download_bw->setObjectName(QString::fromUtf8("spinBox_download_bw"));
        spinBox_download_bw->setFont(font2);
        spinBox_download_bw->setMaximum(65536);

        gridLayout_15->addWidget(spinBox_download_bw, 1, 1, 1, 1);


        gridLayout_13->addWidget(groupBox_BW, 2, 0, 1, 1);

        groupBox_codec = new QGroupBox(tabCodecs);
        groupBox_codec->setObjectName(QString::fromUtf8("groupBox_codec"));
        groupBox_codec->setFont(font1);
        gridLayout_14 = new QGridLayout(groupBox_codec);
        gridLayout_14->setSpacing(0);
        gridLayout_14->setContentsMargins(0, 0, 0, 0);
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
        comboBox_codec_view = new QComboBox(groupBox_codec);
        comboBox_codec_view->setObjectName(QString::fromUtf8("comboBox_codec_view"));
        QSizePolicy sizePolicy8(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(comboBox_codec_view->sizePolicy().hasHeightForWidth());
        comboBox_codec_view->setSizePolicy(sizePolicy8);
        comboBox_codec_view->setFont(font2);

        gridLayout_14->addWidget(comboBox_codec_view, 0, 0, 1, 2);

        tableView_codec = new QTableView(groupBox_codec);
        tableView_codec->setObjectName(QString::fromUtf8("tableView_codec"));
        QSizePolicy sizePolicy9(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(tableView_codec->sizePolicy().hasHeightForWidth());
        tableView_codec->setSizePolicy(sizePolicy9);
        QFont font3;
        font3.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        tableView_codec->setFont(font3);

        gridLayout_14->addWidget(tableView_codec, 1, 0, 4, 1);

        pushButton_up_codec = new QPushButton(groupBox_codec);
        pushButton_up_codec->setObjectName(QString::fromUtf8("pushButton_up_codec"));
        sizePolicy3.setHeightForWidth(pushButton_up_codec->sizePolicy().hasHeightForWidth());
        pushButton_up_codec->setSizePolicy(sizePolicy3);
        pushButton_up_codec->setFont(font2);

        gridLayout_14->addWidget(pushButton_up_codec, 1, 1, 1, 1);

        pushButton_down_codec = new QPushButton(groupBox_codec);
        pushButton_down_codec->setObjectName(QString::fromUtf8("pushButton_down_codec"));
        sizePolicy3.setHeightForWidth(pushButton_down_codec->sizePolicy().hasHeightForWidth());
        pushButton_down_codec->setSizePolicy(sizePolicy3);
        pushButton_down_codec->setFont(font2);

        gridLayout_14->addWidget(pushButton_down_codec, 2, 1, 1, 1);

        pushButton_enable_codec = new QPushButton(groupBox_codec);
        pushButton_enable_codec->setObjectName(QString::fromUtf8("pushButton_enable_codec"));
        sizePolicy3.setHeightForWidth(pushButton_enable_codec->sizePolicy().hasHeightForWidth());
        pushButton_enable_codec->setSizePolicy(sizePolicy3);
        pushButton_enable_codec->setFont(font2);

        gridLayout_14->addWidget(pushButton_enable_codec, 3, 1, 1, 1);

        pushButton_disable_codec = new QPushButton(groupBox_codec);
        pushButton_disable_codec->setObjectName(QString::fromUtf8("pushButton_disable_codec"));
        sizePolicy3.setHeightForWidth(pushButton_disable_codec->sizePolicy().hasHeightForWidth());
        pushButton_disable_codec->setSizePolicy(sizePolicy3);
        pushButton_disable_codec->setFont(font2);

        gridLayout_14->addWidget(pushButton_disable_codec, 4, 1, 1, 1);


        gridLayout_13->addWidget(groupBox_codec, 1, 0, 1, 1);

        tabPreference->addTab(tabCodecs, QString());
        tabInterface = new QWidget();
        tabInterface->setObjectName(QString::fromUtf8("tabInterface"));
        formLayout = new QFormLayout(tabInterface);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setSizeConstraint(QLayout::SetMaximumSize);
        formLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        formLayout->setLabelAlignment(Qt::AlignJustify|Qt::AlignVCenter);
        formLayout->setFormAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        groupBox_11 = new QGroupBox(tabInterface);
        groupBox_11->setObjectName(QString::fromUtf8("groupBox_11"));
        QSizePolicy sizePolicy10(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy10.setHorizontalStretch(0);
        sizePolicy10.setVerticalStretch(0);
        sizePolicy10.setHeightForWidth(groupBox_11->sizePolicy().hasHeightForWidth());
        groupBox_11->setSizePolicy(sizePolicy10);
        groupBox_11->setFont(font1);
        groupBox_11->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        gridLayout_16 = new QGridLayout(groupBox_11);
        gridLayout_16->setObjectName(QString::fromUtf8("gridLayout_16"));
        comboBox_lang = new QComboBox(groupBox_11);
        comboBox_lang->setObjectName(QString::fromUtf8("comboBox_lang"));
        comboBox_lang->setFont(font2);

        gridLayout_16->addWidget(comboBox_lang, 0, 0, 1, 1);


        formLayout->setWidget(0, QFormLayout::SpanningRole, groupBox_11);

        groupBox_12 = new QGroupBox(tabInterface);
        groupBox_12->setObjectName(QString::fromUtf8("groupBox_12"));
        sizePolicy10.setHeightForWidth(groupBox_12->sizePolicy().hasHeightForWidth());
        groupBox_12->setSizePolicy(sizePolicy10);
        groupBox_12->setFont(font1);
        groupBox_12->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        gridLayout_17 = new QGridLayout(groupBox_12);
        gridLayout_17->setObjectName(QString::fromUtf8("gridLayout_17"));
        checkBox_ui_level = new QCheckBox(groupBox_12);
        checkBox_ui_level->setObjectName(QString::fromUtf8("checkBox_ui_level"));
        checkBox_ui_level->setFont(font2);

        gridLayout_17->addWidget(checkBox_ui_level, 0, 0, 1, 1);


        formLayout->setWidget(1, QFormLayout::SpanningRole, groupBox_12);

        tabPreference->addTab(tabInterface, QString());

        gridLayout->addWidget(tabPreference, 2, 0, 1, 1);


        retranslateUi(Preference);

        tabPreference->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Preference);
    } // setupUi

    void retranslateUi(QDialog *Preference)
    {
        Preference->setWindowTitle(QApplication::translate("Preference", "Dialog", 0, QApplication::UnicodeUTF8));
        groupBox_ports->setTitle(QApplication::translate("Preference", "Ports", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Preference", "Audio RTP/UDP:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Preference", "Video RTP/UDP:", 0, QApplication::UnicodeUTF8));
        comboBox_proto->clear();
        comboBox_proto->insertItems(0, QStringList()
         << QApplication::translate("Preference", "SIP (UDP)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Preference", "SIP (TCP)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Preference", "SIP (TLS)", 0, QApplication::UnicodeUTF8)
        );
        groupBox_transport->setTitle(QApplication::translate("Preference", "Transport", 0, QApplication::UnicodeUTF8));
        checkBox_mtu_set->setText(QApplication::translate("Preference", "Set Maximum Tranmission Unit:", 0, QApplication::UnicodeUTF8));
        checkBox_dtmf_sipinfo->setText(QApplication::translate("Preference", "Send DTMFs as SIP Info", 0, QApplication::UnicodeUTF8));
        checkBox_ipv6->setText(QApplication::translate("Preference", "Use IPv6 instead of IPv4", 0, QApplication::UnicodeUTF8));
        groupBox_nat->setTitle(QApplication::translate("Preference", "Nat and Firewall", 0, QApplication::UnicodeUTF8));
        radioButton_no_nat->setText(QApplication::translate("Preference", "Direct connection to the Internet", 0, QApplication::UnicodeUTF8));
        radioButton_use_nat_address->setText(QApplication::translate("Preference", "Behind NAT/Firewall(specify gateway IP below)", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Preference", "Public IP address:", 0, QApplication::UnicodeUTF8));
        radioButton_use_stun->setText(QApplication::translate("Preference", "Behind NAT/Firewall(use STUN to resolve)", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("Preference", "STUN server:", 0, QApplication::UnicodeUTF8));
        tabPreference->setTabText(tabPreference->indexOf(tabNetWork), QApplication::translate("Preference", "Network settings", 0, QApplication::UnicodeUTF8));
        groupBox_audio->setTitle(QApplication::translate("Preference", "Audio", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("Preference", "Playback device:", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("Preference", "Ring device:", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("Preference", "Capture device:", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("Preference", "Ring sound:", 0, QApplication::UnicodeUTF8));
        lineEdit_ring_file->setText(QString());
        toolButton_play_ring->setText(QApplication::translate("Preference", "Play", 0, QApplication::UnicodeUTF8));
        pushButton_choose_file->setText(QApplication::translate("Preference", "Choose File", 0, QApplication::UnicodeUTF8));
        checkBox_echo_cancelation->setText(QApplication::translate("Preference", "Enable echo cancellation", 0, QApplication::UnicodeUTF8));
        groupBox_video->setTitle(QApplication::translate("Preference", "Video", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("Preference", "Video input device:", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("Preference", "Prefered video resolution:", 0, QApplication::UnicodeUTF8));
        tabPreference->setTabText(tabPreference->indexOf(tabMultimedia), QApplication::translate("Preference", "Multimedia settings", 0, QApplication::UnicodeUTF8));
        groupBox_identity->setTitle(QApplication::translate("Preference", "Default identity", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("Preference", "Your display name (eg: John Doe):", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("Preference", "Your username:", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("Preference", "Your resulting SIP address:", 0, QApplication::UnicodeUTF8));
        groupBox_proxy->setTitle(QApplication::translate("Preference", "Proxy accounts", 0, QApplication::UnicodeUTF8));
        pushButton_add_proxy->setText(QApplication::translate("Preference", "Add", 0, QApplication::UnicodeUTF8));
        pushButton_edit_proxy->setText(QApplication::translate("Preference", "Edit", 0, QApplication::UnicodeUTF8));
        pushButton_remove_proxy->setText(QApplication::translate("Preference", "Remove", 0, QApplication::UnicodeUTF8));
        groupBox_8->setTitle(QApplication::translate("Preference", "Privacy", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Preference", "PushButton", 0, QApplication::UnicodeUTF8));
        tabPreference->setTabText(tabPreference->indexOf(tabSIP), QApplication::translate("Preference", "Manage SIP Accounts", 0, QApplication::UnicodeUTF8));
        groupBox_BW->setTitle(QApplication::translate("Preference", "Bandwidth control", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("Preference", "Upload speed limit in Kbit/sec:", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("Preference", "Download speed limit in Kbit/sec:", 0, QApplication::UnicodeUTF8));
        groupBox_codec->setTitle(QApplication::translate("Preference", "Codecs", 0, QApplication::UnicodeUTF8));
        comboBox_codec_view->clear();
        comboBox_codec_view->insertItems(0, QStringList()
         << QApplication::translate("Preference", "Audio codecs", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Preference", "Video codecs", 0, QApplication::UnicodeUTF8)
        );
        pushButton_up_codec->setText(QApplication::translate("Preference", "Up", 0, QApplication::UnicodeUTF8));
        pushButton_down_codec->setText(QApplication::translate("Preference", "Down", 0, QApplication::UnicodeUTF8));
        pushButton_enable_codec->setText(QApplication::translate("Preference", "Enable", 0, QApplication::UnicodeUTF8));
        pushButton_disable_codec->setText(QApplication::translate("Preference", "Disable", 0, QApplication::UnicodeUTF8));
        tabPreference->setTabText(tabPreference->indexOf(tabCodecs), QApplication::translate("Preference", "Codecs", 0, QApplication::UnicodeUTF8));
        groupBox_11->setTitle(QApplication::translate("Preference", "Language", 0, QApplication::UnicodeUTF8));
        groupBox_12->setTitle(QApplication::translate("Preference", "Level", 0, QApplication::UnicodeUTF8));
        checkBox_ui_level->setText(QApplication::translate("Preference", "Show advanced settings", 0, QApplication::UnicodeUTF8));
        tabPreference->setTabText(tabPreference->indexOf(tabInterface), QApplication::translate("Preference", "User interface", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Preference: public Ui_Preference {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREFERENCE_H
