/********************************************************************************
** Form generated from reading UI file 'password.ui'
**
** Created: Fri Apr 26 11:47:09 2013
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PASSWORD_H
#define UI_PASSWORD_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_password
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_userid;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_password;
    QDialogButtonBox *buttonBox;
    QLabel *label_Message;

    void setupUi(QDialog *password)
    {
        if (password->objectName().isEmpty())
            password->setObjectName(QString::fromUtf8("password"));
        password->setWindowModality(Qt::ApplicationModal);
        password->resize(400, 300);
        gridLayout = new QGridLayout(password);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(password);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEdit_userid = new QLineEdit(password);
        lineEdit_userid->setObjectName(QString::fromUtf8("lineEdit_userid"));

        horizontalLayout->addWidget(lineEdit_userid);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(password);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        lineEdit_password = new QLineEdit(password);
        lineEdit_password->setObjectName(QString::fromUtf8("lineEdit_password"));

        horizontalLayout_2->addWidget(lineEdit_password);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        buttonBox = new QDialogButtonBox(password);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 3, 0, 1, 1);

        label_Message = new QLabel(password);
        label_Message->setObjectName(QString::fromUtf8("label_Message"));

        gridLayout->addWidget(label_Message, 0, 0, 1, 1);


        retranslateUi(password);
        QObject::connect(buttonBox, SIGNAL(accepted()), password, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), password, SLOT(reject()));

        QMetaObject::connectSlotsByName(password);
    } // setupUi

    void retranslateUi(QDialog *password)
    {
        password->setWindowTitle(QApplication::translate("password", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("password", "UserID", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("password", "Password", 0, QApplication::UnicodeUTF8));
        label_Message->setText(QApplication::translate("password", "Message", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class password: public Ui_password {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PASSWORD_H
