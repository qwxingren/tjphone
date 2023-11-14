#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif
#include "device.h"
#include <QMessageBox>

Device::Device(QWidget *parent)
	: QDialog(parent)
{
	QTextCodec *codec=QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);
	this->setWindowModality(Qt::ApplicationModal);
	ui.setupUi(this);
	connectstatus=false;
	client=NULL;
	m_timer=new QTimer(this);
	//connect(this,SIGNAL(close()),this,SLOT(reject()));	
}

Device::~Device()
{

}

void Device::accept()
{
	if(client){
		client->close();
	}
	this->done(0);
}

void Device::reject()
{
	if(client){
		client->close();
	}
	this->done(1);
}

void Device::WSSend()
{
	if(client && connectstatus){
		client->sendTextMessage(ui.listWidget_cmd->currentItem()->text());  
	}else{
		QMessageBox::information(this,QString::fromUtf8("警告"),QString::fromUtf8("WebSocket未连接"));
	}
}


void Device::WSTest()
{
	if(client==NULL){
		client=new QWebSocket;
		client->setParent(this);
        qDebug()<<"create websocket!";
		connect(client,&QWebSocket::textMessageReceived,[this](const QString &msg){
        ui.textBrowser->append(msg);});
    
		connect(client,&QWebSocket::connected,[this](){
       
			connectstatus=true;
			m_timer->start(ui.spinBox->value() * 1000);

	        ui.pushButton->setText(QString::fromUtf8("断开"));
        
			ui.textBrowser->append(QString("Client IP:%1  Port:%2")
                               .arg(client->localAddress().toString())
                               .arg(client->localPort()));
	        qDebug()<<"connected";
			client->sendTextMessage(QString("HeartBeatData"));
	   });
        connect(client,SIGNAL(disconnected()),this,SLOT(onDisConnected()),Qt::AutoConnection);
        connect(m_timer,SIGNAL(timeout()),this, SLOT(heartbit()),Qt::AutoConnection);
        client->open(QUrl(ui.lineEdit_Addr->text()));
	}
	
}

void Device::onDisConnected()
{
	qDebug()<<"DataReceive websocket is disconnected!!!";
    connectstatus = false;
	QMessageBox::information(this,QString::fromUtf8("警告"),QString::fromUtf8("WebSocket未连接"));
    m_timer->stop();/*-<当连接失败时，触发重连计时器，设置计数周期为3秒 */
}


void Device::heartbit()
{
	client->sendTextMessage(QString("HeartBeatData"));  
}