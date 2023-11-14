#ifndef SIPACCOUNT_H
#define SIPACCOUNT_H

#include <QDialog>
#include "ui_sipaccount.h"
#include "db.h"

class sipaccount : public QDialog
{
	Q_OBJECT

public:
	sipaccount(QDialog *parent = 0);
	~sipaccount();
	bool get_sip_account(sip_account_data &sip_account);

private slots:
	void accept();
	void reject();
private:
	db mydb;
	Ui::SipAccount ui;
};

#endif // SIPACCOUNT_H
