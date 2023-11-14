#ifndef DEVICE_H
#define DEVICE_H

#include <QDialog>
#include <QtWebSockets>
#include <QTimer>


#include "ui_device.h"

class Device : public QDialog
{
	Q_OBJECT

public:
	Device(QWidget *parent = 0);
	~Device();

private:
	Ui::Device ui;
	QWebSocket *client;
	bool connectstatus;
	QTimer *m_timer;
	
	

private slots:
	void accept();
	void reject();
	void WSTest();
	void WSSend();
	void onDisConnected();
	void heartbit();

};

#endif // DEVICE_H
