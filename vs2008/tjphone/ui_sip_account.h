/********************************************************************************
** Form generated from reading UI file 'sip_account.ui'
**
** Created: Fri Apr 26 11:47:09 2013
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIP_ACCOUNT_H
#define UI_SIP_ACCOUNT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SIP_Account
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QLineEdit *lineEdit_account;
    QLabel *label_2;
    QLineEdit *lineEdit_proxy;
    QLabel *label_3;
    QLineEdit *lineEdit_route;
    QLabel *label_5;
    QLineEdit *lineEdit_passwd;
    QLabel *label_4;
    QSpinBox *spinBox_Regtime;
    QCheckBox *checkBox_register;
    QCheckBox *checkBox_publish;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SIP_Account)
    {
        if (SIP_Account->objectName().isEmpty())
            SIP_Account->setObjectName(QString::fromUtf8("SIP_Account"));
        SIP_Account->resize(423, 274);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        SIP_Account->setFont(font);
        gridLayout = new QGridLayout(SIP_Account);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox = new QGroupBox(SIP_Account);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        label->setFont(font1);

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        lineEdit_account = new QLineEdit(groupBox);
        lineEdit_account->setObjectName(QString::fromUtf8("lineEdit_account"));
        lineEdit_account->setFont(font1);

        gridLayout_2->addWidget(lineEdit_account, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font1);

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        lineEdit_proxy = new QLineEdit(groupBox);
        lineEdit_proxy->setObjectName(QString::fromUtf8("lineEdit_proxy"));
        lineEdit_proxy->setFont(font1);

        gridLayout_2->addWidget(lineEdit_proxy, 1, 1, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font1);

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        lineEdit_route = new QLineEdit(groupBox);
        lineEdit_route->setObjectName(QString::fromUtf8("lineEdit_route"));
        lineEdit_route->setFont(font1);

        gridLayout_2->addWidget(lineEdit_route, 2, 1, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font1);

        gridLayout_2->addWidget(label_5, 3, 0, 1, 1);

        lineEdit_passwd = new QLineEdit(groupBox);
        lineEdit_passwd->setObjectName(QString::fromUtf8("lineEdit_passwd"));
        lineEdit_passwd->setFont(font1);

        gridLayout_2->addWidget(lineEdit_passwd, 3, 1, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font1);

        gridLayout_2->addWidget(label_4, 4, 0, 1, 1);

        spinBox_Regtime = new QSpinBox(groupBox);
        spinBox_Regtime->setObjectName(QString::fromUtf8("spinBox_Regtime"));
        spinBox_Regtime->setFont(font1);

        gridLayout_2->addWidget(spinBox_Regtime, 4, 1, 1, 1);

        checkBox_register = new QCheckBox(groupBox);
        checkBox_register->setObjectName(QString::fromUtf8("checkBox_register"));
        checkBox_register->setFont(font1);

        gridLayout_2->addWidget(checkBox_register, 5, 0, 1, 1);

        checkBox_publish = new QCheckBox(groupBox);
        checkBox_publish->setObjectName(QString::fromUtf8("checkBox_publish"));
        checkBox_publish->setFont(font1);

        gridLayout_2->addWidget(checkBox_publish, 6, 0, 1, 2);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(SIP_Account);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setFont(font1);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(SIP_Account);

        QMetaObject::connectSlotsByName(SIP_Account);
    } // setupUi

    void retranslateUi(QDialog *SIP_Account)
    {
        SIP_Account->setWindowTitle(QApplication::translate("SIP_Account", "Configure a SIP account", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("SIP_Account", "Configure a SIP Account", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SIP_Account", "Your SIP identity:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SIP_Account", "SIP Proxy address:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("SIP_Account", "Route (optional):", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("SIP_Account", "Password:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("SIP_Account", "Registration duration (sec):", 0, QApplication::UnicodeUTF8));
        checkBox_register->setText(QApplication::translate("SIP_Account", "Register at startup", 0, QApplication::UnicodeUTF8));
        checkBox_publish->setText(QApplication::translate("SIP_Account", "Publish presence information", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SIP_Account: public Ui_SIP_Account {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIP_ACCOUNT_H
