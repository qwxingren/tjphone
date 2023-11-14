/********************************************************************************
** Form generated from reading UI file 'callviewframe.ui'
**
** Created: Fri Apr 26 11:47:10 2013
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALLVIEWFRAME_H
#define UI_CALLVIEWFRAME_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGraphicsView>
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

class Ui_CallViewFrame
{
public:
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_duration;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_duration;
    QProgressBar *progressBar_quality_indicator;
    QGraphicsView *graphicsView_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_mute;
    QProgressBar *progressBar_mic;
    QPushButton *pushButton_speaker;
    QProgressBar *progressBar_speaker;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_callee;
    QLabel *label_codec;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_answer;
    QPushButton *pushButton_decline;
    QPushButton *pushButton_pause;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QFrame *CallViewFrame)
    {
        if (CallViewFrame->objectName().isEmpty())
            CallViewFrame->setObjectName(QString::fromUtf8("CallViewFrame"));
        CallViewFrame->resize(481, 252);
        CallViewFrame->setFrameShape(QFrame::StyledPanel);
        CallViewFrame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(CallViewFrame);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox_duration = new QGroupBox(CallViewFrame);
        groupBox_duration->setObjectName(QString::fromUtf8("groupBox_duration"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_duration->sizePolicy().hasHeightForWidth());
        groupBox_duration->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(groupBox_duration);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_duration = new QLabel(groupBox_duration);
        label_duration->setObjectName(QString::fromUtf8("label_duration"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_duration->sizePolicy().hasHeightForWidth());
        label_duration->setSizePolicy(sizePolicy1);
        label_duration->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(label_duration);

        progressBar_quality_indicator = new QProgressBar(groupBox_duration);
        progressBar_quality_indicator->setObjectName(QString::fromUtf8("progressBar_quality_indicator"));
        progressBar_quality_indicator->setValue(24);
        progressBar_quality_indicator->setTextVisible(true);

        horizontalLayout_4->addWidget(progressBar_quality_indicator);

        graphicsView_2 = new QGraphicsView(groupBox_duration);
        graphicsView_2->setObjectName(QString::fromUtf8("graphicsView_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(graphicsView_2->sizePolicy().hasHeightForWidth());
        graphicsView_2->setSizePolicy(sizePolicy2);

        horizontalLayout_4->addWidget(graphicsView_2);


        gridLayout->addLayout(horizontalLayout_4, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetMaximumSize);
        pushButton_mute = new QPushButton(groupBox_duration);
        pushButton_mute->setObjectName(QString::fromUtf8("pushButton_mute"));

        horizontalLayout_2->addWidget(pushButton_mute);

        progressBar_mic = new QProgressBar(groupBox_duration);
        progressBar_mic->setObjectName(QString::fromUtf8("progressBar_mic"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(progressBar_mic->sizePolicy().hasHeightForWidth());
        progressBar_mic->setSizePolicy(sizePolicy3);
        progressBar_mic->setValue(24);
        progressBar_mic->setTextVisible(false);

        horizontalLayout_2->addWidget(progressBar_mic);

        pushButton_speaker = new QPushButton(groupBox_duration);
        pushButton_speaker->setObjectName(QString::fromUtf8("pushButton_speaker"));
        pushButton_speaker->setEnabled(false);

        horizontalLayout_2->addWidget(pushButton_speaker);

        progressBar_speaker = new QProgressBar(groupBox_duration);
        progressBar_speaker->setObjectName(QString::fromUtf8("progressBar_speaker"));
        progressBar_speaker->setEnabled(true);
        sizePolicy3.setHeightForWidth(progressBar_speaker->sizePolicy().hasHeightForWidth());
        progressBar_speaker->setSizePolicy(sizePolicy3);
        progressBar_speaker->setAutoFillBackground(false);
        progressBar_speaker->setValue(24);
        progressBar_speaker->setTextVisible(false);
        progressBar_speaker->setOrientation(Qt::Horizontal);
        progressBar_speaker->setInvertedAppearance(false);

        horizontalLayout_2->addWidget(progressBar_speaker);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_callee = new QLabel(groupBox_duration);
        label_callee->setObjectName(QString::fromUtf8("label_callee"));

        horizontalLayout_3->addWidget(label_callee);

        label_codec = new QLabel(groupBox_duration);
        label_codec->setObjectName(QString::fromUtf8("label_codec"));

        horizontalLayout_3->addWidget(label_codec);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);


        verticalLayout_2->addWidget(groupBox_duration);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_answer = new QPushButton(CallViewFrame);
        pushButton_answer->setObjectName(QString::fromUtf8("pushButton_answer"));
        pushButton_answer->setLayoutDirection(Qt::LeftToRight);
        pushButton_answer->setAutoFillBackground(false);
        pushButton_answer->setAutoDefault(true);

        horizontalLayout->addWidget(pushButton_answer);

        pushButton_decline = new QPushButton(CallViewFrame);
        pushButton_decline->setObjectName(QString::fromUtf8("pushButton_decline"));
        pushButton_decline->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout->addWidget(pushButton_decline);

        pushButton_pause = new QPushButton(CallViewFrame);
        pushButton_pause->setObjectName(QString::fromUtf8("pushButton_pause"));

        horizontalLayout->addWidget(pushButton_pause);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout);


        gridLayout_2->addLayout(verticalLayout_2, 0, 0, 1, 1);


        retranslateUi(CallViewFrame);

        QMetaObject::connectSlotsByName(CallViewFrame);
    } // setupUi

    void retranslateUi(QFrame *CallViewFrame)
    {
        CallViewFrame->setWindowTitle(QApplication::translate("CallViewFrame", "Frame", 0, QApplication::UnicodeUTF8));
        groupBox_duration->setTitle(QApplication::translate("CallViewFrame", "duration", 0, QApplication::UnicodeUTF8));
        label_duration->setText(QApplication::translate("CallViewFrame", "00:00:00", 0, QApplication::UnicodeUTF8));
        pushButton_mute->setText(QApplication::translate("CallViewFrame", "Mute", 0, QApplication::UnicodeUTF8));
        progressBar_mic->setFormat(QString());
        pushButton_speaker->setText(QString());
        progressBar_speaker->setFormat(QString());
        label_callee->setText(QApplication::translate("CallViewFrame", "sip:", 0, QApplication::UnicodeUTF8));
        label_codec->setText(QApplication::translate("CallViewFrame", "G729", 0, QApplication::UnicodeUTF8));
        pushButton_answer->setText(QApplication::translate("CallViewFrame", "Answer", 0, QApplication::UnicodeUTF8));
        pushButton_decline->setText(QApplication::translate("CallViewFrame", "Decline", 0, QApplication::UnicodeUTF8));
        pushButton_pause->setText(QApplication::translate("CallViewFrame", "Pause", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CallViewFrame: public Ui_CallViewFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALLVIEWFRAME_H
