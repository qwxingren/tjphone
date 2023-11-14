/********************************************************************************
** Form generated from reading UI file 'conferenceframe.ui'
**
** Created: Fri Apr 26 11:47:09 2013
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFERENCEFRAME_H
#define UI_CONFERENCEFRAME_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ConferenceFrame
{
public:
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_duration;
    QGridLayout *gridLayout;
    QLabel *label_me;
    QProgressBar *progressBar_me;
    QPushButton *pushButton_muteMe;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_pause;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QFrame *ConferenceFrame)
    {
        if (ConferenceFrame->objectName().isEmpty())
            ConferenceFrame->setObjectName(QString::fromUtf8("ConferenceFrame"));
        ConferenceFrame->resize(457, 228);
        ConferenceFrame->setFrameShape(QFrame::StyledPanel);
        ConferenceFrame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(ConferenceFrame);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox_duration = new QGroupBox(ConferenceFrame);
        groupBox_duration->setObjectName(QString::fromUtf8("groupBox_duration"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_duration->sizePolicy().hasHeightForWidth());
        groupBox_duration->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(groupBox_duration);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_me = new QLabel(groupBox_duration);
        label_me->setObjectName(QString::fromUtf8("label_me"));

        gridLayout->addWidget(label_me, 0, 2, 1, 1);

        progressBar_me = new QProgressBar(groupBox_duration);
        progressBar_me->setObjectName(QString::fromUtf8("progressBar_me"));
        progressBar_me->setValue(24);
        progressBar_me->setTextVisible(false);

        gridLayout->addWidget(progressBar_me, 0, 3, 1, 1);

        pushButton_muteMe = new QPushButton(groupBox_duration);
        pushButton_muteMe->setObjectName(QString::fromUtf8("pushButton_muteMe"));

        gridLayout->addWidget(pushButton_muteMe, 0, 0, 1, 2);


        verticalLayout_2->addWidget(groupBox_duration);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_pause = new QPushButton(ConferenceFrame);
        pushButton_pause->setObjectName(QString::fromUtf8("pushButton_pause"));

        horizontalLayout->addWidget(pushButton_pause);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout);


        gridLayout_2->addLayout(verticalLayout_2, 0, 0, 1, 1);


        retranslateUi(ConferenceFrame);

        QMetaObject::connectSlotsByName(ConferenceFrame);
    } // setupUi

    void retranslateUi(QFrame *ConferenceFrame)
    {
        ConferenceFrame->setWindowTitle(QApplication::translate("ConferenceFrame", "Frame", 0, QApplication::UnicodeUTF8));
        groupBox_duration->setTitle(QApplication::translate("ConferenceFrame", "duration", 0, QApplication::UnicodeUTF8));
        label_me->setText(QApplication::translate("ConferenceFrame", "Me", 0, QApplication::UnicodeUTF8));
        progressBar_me->setFormat(QString());
        pushButton_muteMe->setText(QApplication::translate("ConferenceFrame", "Mute", 0, QApplication::UnicodeUTF8));
        pushButton_pause->setText(QApplication::translate("ConferenceFrame", "Pause", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ConferenceFrame: public Ui_ConferenceFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFERENCEFRAME_H
