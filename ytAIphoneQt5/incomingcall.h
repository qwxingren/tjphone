#ifndef INCOMINGCALL_H
#define INCOMINGCALL_H

#include <QDialog>

namespace Ui {
class IncomingCall;
}

class incomingcall : public QDialog
{
    Q_OBJECT

public:
    explicit incomingcall(QWidget *parent = 0);
    ~incomingcall();
	void set_PhoneNum(QString &number);
	void call_End();

	void answer_sip();
	void hangup_sip();

private slots:
    void accept();

    void reject();

private:
    Ui::IncomingCall *ui;
};

extern incomingcall *callDialog;

#endif // INCOMINGCALL_H
