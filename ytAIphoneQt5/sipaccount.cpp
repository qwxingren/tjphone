#include "sipaccount.h"

bool  IsAccept=false;

sipaccount::sipaccount(QDialog *parent)
	: QDialog(parent),
	mydb(parent)
{
	this->setWindowModality(Qt::ApplicationModal);
	ui.setupUi(this);
	IsAccept=false;
	sip_account_data sip_account;
	sip_account.port=5060;
	mydb.get_sipconfig(sip_account);
	ui.lineEdit->setText(sip_account.number);
	ui.lineEdit_2->setText(sip_account.proxy);
	ui.lineEdit_3->setText(QString::number(sip_account.port));
	ui.lineEdit_4->setText(sip_account.domain);
	ui.lineEdit_5->setText(sip_account.secret);
}

sipaccount::~sipaccount()
{

}

bool sipaccount::get_sip_account(sip_account_data &sip_account)
{
	if(IsAccept){
		sip_account_data sip_config;
		sip_config.domain = ui.lineEdit_4->text();
		sip_config.number = ui.lineEdit->text();
		sip_config.port = ui.lineEdit_3->text().toUInt();
		sip_config.proxy = ui.lineEdit_2->text();
		sip_config.secret = ui.lineEdit_5->text();
		mydb.save_sipconfig(sip_config);
		return mydb.get_sipconfig(sip_account);
	}else{
		return false;
	}
}

void sipaccount::accept()
{
	IsAccept=true;
	this->done(0);
}

void sipaccount::reject()
{
	IsAccept=false;
	this->done(1);
}