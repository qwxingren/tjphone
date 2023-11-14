#include "incomingcall.h"
#include "mainwindow.h"
#include "ui_incomingcall.h"

#include "linphonec.h"

#define USEWS

LinphoneCall* call=NULL;
incomingcall::incomingcall(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IncomingCall)
{
    ui->setupUi(this);
	ui->okButton->setEnabled(false);
	ui->cancelButton->setEnabled(false);
	ui->label_2->clear();
}

incomingcall::~incomingcall()
{
    delete ui;
}

void incomingcall::answer_sip()
{
	accept();
}

void incomingcall::hangup_sip()
{
	reject();
}


//接通
void incomingcall::accept()
{
	if(call){
		linphone_core_accept_call(linphone_call_get_core(call),call);
		//yt_answer_call();
#ifndef USEWS
		ui->okButton->setEnabled(false);
		ui->cancelButton->setEnabled(true);
#endif
	}
}

//挂断
void incomingcall::reject()
{
	if(call){
		linphone_core_terminate_call(linphone_call_get_core(call),call);
		//yt_terminate_call();
		call=NULL;
	}
}
void incomingcall::set_PhoneNum(QString &number)
{
	ui->label_2->setText(number);
#ifndef USEWS
	ui->okButton->setEnabled(true);
	ui->cancelButton->setEnabled(true);
#else
	ui->okButton->setEnabled(false);
	ui->cancelButton->setEnabled(false);
#endif
	
}
void incomingcall::call_End()
{
	if(call){
		call=NULL;
	}
	ui->okButton->setEnabled(false);
	ui->cancelButton->setEnabled(false);
	ui->label_2->clear();
}
void show_dialog(LinphoneCall* _call)
{	
	QString number;
	if(callDialog){
		call=_call;
		if(call){
			number=linphone_address_as_string(linphone_call_get_to(call));
			QRegExp kk("sip:(.*){0,1}@");
			if(number.indexOf(kk)>=0){
				number=kk.cap(1);			
				w->CallOut(number);
			}
			callDialog->set_PhoneNum(number);
			if(callDialog->isHidden())
				callDialog->show();
		}
	}
}

void show_dialog2(LinphoneCall* _call)
{	
	QString number;
	if(callDialog){
		call=_call;
		if(call){
			number=linphone_address_as_string(linphone_call_get_from(call));
			QRegExp kk("sip:(.*){0,1}@");
			if(number.indexOf(kk)>=0){
				number=kk.cap(1);			
			}
			callDialog->set_PhoneNum(number);
			if(callDialog->isHidden())
				callDialog->show();
		}
	}
}

void call_connected(LinphoneCall* call)
{
	QString number;
	if(call){
		number=linphone_address_as_string(linphone_call_get_from(call));
		QRegExp kk("sip:(.*){0,1}@");
		if(number.indexOf(kk)>=0){
			number=kk.cap(1);			
		}
		w->AnswerIncomingCall(number);
	}
}
void show_dialog_callend()
{
	if(w){
		w->HangUp();
	}
	if(callDialog){
		callDialog->call_End();
		if(!callDialog->isHidden())
			callDialog->hide();		
	}
}