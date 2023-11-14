#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStandardItemModel>
#include <QTableWidgetItem>
#include <QTextCodec>
#include <QTimer>
#include <QMessageBox>

#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include <linphonecore.h>
#include "linphonec.h"

#include "sipaccount.h"
#include "device.h"
#include "incomingcall.h"


#define USEWS

QUrl WSUrl("ws://127.0.0.1:8555/api");
//QUrl WSUrl("ws://192.168.1.39:8555/api");

class _SIM_Info{
public:
	QString Name;				//显示的名字
	QString Status;				//sim卡状态
	QString phoneNumber;		//sim卡手机号码
	int HaveCalledNumberOfDay;	//今日呼叫数量
	int HaveCalledNumberOfHour;	//本小时呼叫数量
	bool cardStatus;			//true,可以发起呼叫
};


 enum CallSatus {
        Idle=0,
        Outgoing,
        Ringback,
		Outconnected,
		Hangup,
		Incoming
};

class _Device {
public:
	QString deviceName;			//设备编号，通过ws发送 GetConnectedState 获取
	int curCard;				//当前正在使用的sim卡,SIMCads_Info的数组下标
	QString curCalloutNumber;	//正在外呼的号码
	bool    deviceStatus;		//true, 可以呼叫，启动sip
	QString soundCard;			//usb声卡名称
	bool    CallStatus;			//true 有呼叫、false，无呼叫
	_SIM_Info SIMCads_Info[5];	//
	QString invoke_command;		//当前发出的指令，应答处理之后，需要清空
	int SimCardsCount;
	bool curCardReady;			//sim卡是否已注册在蜂窝网并准备就绪
	unsigned short doChange;				//true, 执行了切卡操作，且未完成。初始化置为false，完成切卡置为falses
};

_Device device;


QString cardstatus2str(bool status){
	if(status){
		return QString::fromUtf8("正常");
	}else{
		return QString::fromUtf8("未知");
	}
}

void MainWindow::showCards()
{
	QTableView *resultView=ui->tableView;
    QStandardItemModel *model=new QStandardItemModel();

    model->setHorizontalHeaderLabels(QStringList() <<  QString::fromUtf8("卡编号")<<  QString::fromUtf8("状态")<< QString::fromUtf8("号码")<< QString::fromUtf8("本轮呼叫数量")<< QString::fromUtf8("今日呼叫总量"));

    QList<QStringList> rows = QList<QStringList>();
	
	for(int i=0;i<5;i++){

		rows<< (QStringList() << QString::fromUtf8("%1号卡").arg(i+1) << cardstatus2str(device.SIMCads_Info[i].cardStatus) << "" << QString("%1").arg(device.SIMCads_Info[i].HaveCalledNumberOfHour) << QString("%1").arg(device.SIMCads_Info[i].HaveCalledNumberOfDay));
        
	}

    foreach (QStringList row, rows) {
        QList<QStandardItem *> items;
        foreach (QString text, row)
            items.append(new QStandardItem(text));
        model->appendRow(items);
    }

    resultView->setModel(model);
    resultView->verticalHeader()->hide();
    resultView->horizontalHeader()->setStretchLastSection(true);
    resultView->show();

}
void MainWindow::HangUp()
{

		QString cmd=QString("{\"command\":\"HungUp\"}");
		w->WSSend(cmd);
		QString status=QString::fromUtf8("呼叫结束");
		set_call_status(device.curCard, status);
		/*
		判断当前卡的呼叫数量，是否需要切卡
		//切卡先注销，然后切卡注销，发送注册请求，有效期为0
		*/

		if(device.SIMCads_Info[device.curCard].HaveCalledNumberOfHour>=ui->spinBox->value())
		//if(device.SIMCads_Info[device.curCard].HaveCalledNumberOfHour>=1)
		{
			if(ui->comboBox->currentIndex()==(ui->comboBox->count()-1))
			{
				ui->comboBox->setCurrentIndex(0);
			}else{
				ui->comboBox->setCurrentIndex(ui->comboBox->currentIndex()+1);
			}
			
		}
}


void MainWindow::AnswerIncomingCall(const QString &number){
	QString status=QString::fromUtf8("呼叫 ") + number;
	device.curCalloutNumber=number;
	set_call_status(device.curCard, status);
	QString cmd=QString("{\"command\":\"Answer_Multi\",\"arguments\":{\"devicename\":\"%1\"}}").arg(device.deviceName);
	w->WSSend(cmd);	

#if 1

	QString acmd = QString::fromUtf8("{\"command\":\"closechanneltoheadset_Multi\",\"arguments\":{\"devicename\":\"%1\"}}").arg(device.deviceName);
	WSSend(acmd);
	acmd = QString::fromUtf8("{\"command\":\"closeheadsettochannel_Multi\",\"arguments\":{\"devicename\":\"%1\"}}").arg(device.deviceName);
	WSSend(acmd);
	acmd = QString::fromUtf8("{\"command\":\"OpenOnewayRecord_Multi\",\"arguments\":{\"devicename\":\"%1\"}}").arg(device.deviceName);
	WSSend(acmd);
#endif

	//device.SIMCads_Info[device.curCard].HaveCalledNumberOfHour++;
	//device.SIMCads_Info[device.curCard].HaveCalledNumberOfDay++;
	//ui->label_6->setText(QString::fromUtf8("%1").arg(device.SIMCads_Info[device.curCard].HaveCalledNumberOfHour));
	//update_called_count(device.curCard);	
}

void MainWindow::CallOut(const QString &number){
	QString status=QString::fromUtf8("呼叫 ") + number;
	device.curCalloutNumber=number;
	set_call_status(device.curCard, status);
	QString cmd=QString("{\"command\":\"Dial\",\"arguments\":{\"phone\":\"%1\"}}").arg(number);
	w->WSSend(cmd);	
	device.SIMCads_Info[device.curCard].HaveCalledNumberOfHour++;
	device.SIMCads_Info[device.curCard].HaveCalledNumberOfDay++;
	ui->label_6->setText(QString::fromUtf8("%1").arg(device.SIMCads_Info[device.curCard].HaveCalledNumberOfHour));
	update_called_count(device.curCard);
}

void MainWindow::update_called_count(int cardindex)
{
	QStandardItemModel *model = (QStandardItemModel *)ui->tableView->model();
	if(model){
		//本轮呼叫数量更新
		QModelIndex mindex=model->index(cardindex,3);
		model->setData(mindex, QVariant::fromValue(device.SIMCads_Info[device.curCard].HaveCalledNumberOfHour));
		mindex=model->index(cardindex,4);
		model->setData(mindex, QVariant::fromValue(device.SIMCads_Info[device.curCard].HaveCalledNumberOfDay));
	}
}

/*
切卡，增加一个状态，切卡状态下，读卡失败允许尝试3次，间隔3秒。
*/
void MainWindow::ChangCard()
{
	ui->comboBox->setDisabled(true);
	int cardindex = ui->comboBox->itemData(ui->comboBox->currentIndex()).toInt();
	device.curCard=cardindex;
	QString cmd=QString("{\"command\":\"CBSwitch_Multi\",\"arguments\":{\"devicename\":\"%1\",\"content\":\"%2\"}}").arg(device.deviceName).arg(cardindex);
	device.invoke_command=QString("CBSwitch_Multi");
	WSSend(cmd);
	ui->label_2->setText(QString::fromUtf8("设备已连接,正在切换SIM卡"));
	device.SIMCads_Info[device.curCard].HaveCalledNumberOfHour=0;
	device.curCardReady=false;
	device.doChange=3;
	
}

void MainWindow::updateValidCards()
{
	ui->comboBox->clear();
	for(int i=0;i<5;i++){
		if(device.SIMCads_Info[i].cardStatus){
			QString text = QString::fromUtf8("%1号卡").arg(i+1);
			ui->comboBox->addItem(text,i);
		}
	}
}


void MainWindow::append_log(const QString &log)
{
	if(_logDlg){
		_logDlg->append_log(log);
	}
}



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

	_logDlg=NULL;
	timer_iterate=NULL;
	SIPstatus=false;
	showWScloseInfo=true;
	HeartBeat_status=false;
	wsfirstrun=true;

	sip_identity.clear();
    QTextCodec *codec=QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);

    ui->setupUi(this);
	ui->commandLinkButton->setDisabled(true);
	SIPRegStatus=false;
    
	
	this->setWindowTitle(QString::fromUtf8("梯加科技 V2.0.1"));

	WSclient=NULL;
	WSconnectstatus=false;


	device.CallStatus=Idle;
	device.curCard=-1;
	device.deviceStatus=false;
	device.doChange=0;
	device.SimCardsCount=0;


#ifdef USEWS
	initCmd.append(QStringList()<<"GetConnectedState_Multi"<<"{\"command\":\"GetConnectedState_Multi\"}");

	//OnGetTalkState();
	//initCmd.insert("GetTalkState_Multi","{\"command\":\"GetTalkState_Multi\",\"arguments\":{\"devicename\":\"000000\"}}");

	//OnGetVolume();
	//initCmd.insert("GetDeviceAudio_Multi","{\"command\":\"GetDeviceAudio_Multi\",\"arguments\":{\"devicename\":\"000000\"}}");

	//OnGetCCID(); 获取CCID及运营商信息
	initCmd.append(QStringList()<<"GetCCID_Multi"<<"{\"command\":\"GetCCID_Multi\",\"arguments\":{\"devicename\":\"000000\"}}");

	//OnGetCBCurrState(); 获取卡槽状态
	initCmd.append(QStringList()<<"GetCBCurrState_Multi"<<"{\"command\":\"GetCBCurrState_Multi\",\"arguments\":{\"devicename\":\"000000\"}}");

	//OnGetCBCurrSIM(); 获取当前使用SIM卡索引 0-4
	initCmd.append(QStringList()<<"GetCBCurrSim_Multi"<<"{\"command\":\"GetCBCurrSim_Multi\",\"arguments\":{\"devicename\":\"000000\"}}");

	//OnGetDeviceProductInfo(); 获取设备型号信息
	//initCmd.insert("GetDeviceInfo_Multi","{\"command\":\"GetDeviceInfo_Multi\",\"arguments\":{\"devicename\":\"000000\"}}");

	//OnGetConfig(); 读取配置
	//initCmd.insert("GetConfig","{\"command\":\"GetConfig\"}");

	//OnGetErrorUploadCount(); 获取推送失败记录
	//initCmd.append(QStringList()<<"GetUpdloadErrorLog"<<"{\"command\":\"GetUpdloadErrorLog\"}");

	//OnTalkPlayAudio()  通话中开始播放默认音频
	
#if 1

	initCmd.append(QStringList()<<"closeheadsettochannel_Multi"<<"{\"command\":\"closeheadsettochannel_Multi\",\"arguments\":{\"devicename\":\"000000\"}}");

	initCmd.append(QStringList()<<"closechanneltoheadset_Multi"<<"{\"command\":\"closechanneltoheadset_Multi\",\"arguments\":{\"devicename\":\"000000\"}}");

	initCmd.append(QStringList()<<"OpenOnewayRecord_Multi"<<"{\"command\":\"OpenOnewayRecord_Multi\",\"arguments\":{\"devicename\":\"000000\"}}");

	initCmd.append(QStringList()<<"openusbaududiotousbrecord_Multi"<<"{\"command\":\"openusbaududiotousbrecord_Multi\",\"arguments\":{\"devicename\":\"000000\"}}");

	initCmd.append(QStringList()<<"closeheadsettousbrecord_Multi"<<"{\"command\":\"closeheadsettousbrecord_Multi\",\"arguments\":{\"devicename\":\"000000\"}}");
#endif

#endif

	connect(ui->commandLinkButton,SIGNAL(clicked()),this,SLOT(sip_register()));
	connect(ui->pushButtonSIP,SIGNAL(clicked()),this,SLOT(SIPAccount()));
	connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangCard()));
	

#ifdef USEWS
	m_timer=new QTimer(this);
	WSConnect();
#else

	showWScloseInfo=false;
	device.deviceStatus=true;					
	this->SIPAccount();
#endif
}

MainWindow::~MainWindow()
{
	/*如果还在通话中，先挂断电话*/
	

	if(SIPstatus){
		if(timer_iterate){
			timer_iterate->stop();
			delete timer_iterate;
			timer_iterate=NULL;
		}

		linphonec_main_loop_exit();
		linphonec_finish(EXIT_SUCCESS);
		SIPstatus=false;
		ui->commandLinkButton->setDisabled(true);
	}
	if(WSclient){
		WSclient->close();
	}

	if(_logDlg)
	{
		delete _logDlg;
		_logDlg=NULL;
	}

    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event){
    on_actionquit_triggered();
    QMainWindow::closeEvent(event);
}

void MainWindow::on_actionyantong_triggered()
{
	ShellExecuteA(0,"open","https://github.com/qwxingren/tjphone",NULL,NULL,1);
}

void MainWindow::on_actionquit_triggered()
{
	if(_logDlg)
	{
		delete _logDlg;
		_logDlg=NULL;
	}
	voip_uninit();
	if(WSclient)
		WSclient->close();
	this->close();
}

void MainWindow::on_actiongaojie_triggered()
{
	/*
	//WebSocket调试
	Device m_ws;
	m_ws.exec();
	*/

	//显示日志
	if(_logDlg==NULL)
	{
		_logDlg = new ShowLog(this);
		_logDlg->show();
		//linphone_gtk_log_push(lev,fmt,args);
	}else{
		_logDlg->show();
	}
}

void MainWindow::on_actionTestcall_triggered()
{
	/*
	if(device.deviceStatus && this->SIPstatus){
		CallOut("13795418069");
	}
	*/
	//set_call_status(0, QString::fromUtf8("收到来电 %1").arg("13795418069"));
	if (linphone_core_invite2(linphonec,"13795418069")==NULL) {
		linphone_core_terminate_call(linphonec, NULL);
	}
	
}


void MainWindow::sip_register()
{
	if(!SIPstatus) return;
	LinphoneProxyConfig *cfg=NULL;
    linphone_core_get_default_proxy(linphonec,&cfg);
    if (cfg)
    {
    	if(!linphone_proxy_config_is_registered(cfg)) {
			linphone_proxy_config_enable_register(cfg,TRUE);
			linphone_proxy_config_done(cfg);
		}
	}
}


void MainWindow::SIPAccount()
{
		//线路模式
		//首先初始化话机,初始化成功之后，切换到此模式
		if(voip_init()){
			ui->label_9->setText(QString::fromUtf8("线路账号: ") + sip_identity);
			ui->label_9->show();
			ui->commandLinkButton->setText(QString::fromUtf8("未注册，请点击这里"));
			ui->commandLinkButton->show();
			sip_register();
		}
}

void MainWindow::linphone_qt_iterate()

{
	static bool in_iterate=FALSE;	
	/*avoid reentrancy*/

	if (in_iterate) return;

	in_iterate=TRUE;
	linphone_core_iterate(linphonec);
	in_iterate=FALSE;
}

bool MainWindow::voip_init()
{
	static bool haverun=false;
	sipaccount account;
	QString domain;
	QString proxy;
	QString identity;
	QString secret;
	account.exec();
	sip_account_data sip_account;
	if(!account.get_sip_account(sip_account)){
		return false;
	}
	proxy = "sip:" + sip_account.proxy + ":" + QString::number(sip_account.port);
	domain = sip_account.domain;
	identity = "sip:"+sip_account.number + "@" + sip_account.proxy + ":" + QString::number(sip_account.port);
	secret = sip_account.secret;
	
	sip_identity=identity;
	
	//linphone_core_enable_logs_with_cb(linphone_gtk_log_handler);
	
	if(0 == linphonec_main((char *)proxy.toLocal8Bit().data(),(char *)domain.toLocal8Bit().data(), (char *)secret.toLocal8Bit().data(), (char *)identity.toLocal8Bit().data(), NULL)){
	//if(0 == linphonec_main("sip:47.103.19.208:5099","47.103.19.208:5099", "888123456", "sip:6666222244@47.103.19.208:5099", "sip:47.103.19.208:5099")){
		SIPstatus=true;
		ui->commandLinkButton->setEnabled(true);
		timer_iterate = new QTimer(this);
		connect(timer_iterate,SIGNAL(timeout()),this,SLOT(linphone_qt_iterate()));
		timer_iterate->start(30);

		/*枚举声卡*/
		const char **dev;
		if(!haverun){
			haverun=true;
		dev=linphone_core_get_sound_devices(linphonec);
#ifdef USEWS
		
		for(int i=0; dev[i]!=NULL; ++i){
			QString text = QString::fromUtf8("声卡设备 %1: %2").arg(i).arg(dev[i]);
			append_log(text);
			
			if((text.contains(QString::fromUtf8("麦克风")) && text.contains("USB PnP")) || (text.contains(QString::fromUtf8("麦克风")) && text.contains(QString::fromUtf8("EV")))){
				//设置usb 麦克风
				linphone_core_set_capture_device(linphonec,dev[i]);
				ui->comboBox_sndMic->addItem( QString::fromUtf8("%1").arg(dev[i]));
				append_log(QString::fromUtf8("麦克风使用设备：%1").arg(dev[i]));
			}
			if((text.contains(QString::fromUtf8("扬声器")) && text.contains("USB PnP")) || (text.contains(QString::fromUtf8("扬声器")) && text.contains(QString::fromUtf8("EV")))){
				//设置usb喇叭
				ui->comboBox_sndPlay->addItem( QString::fromUtf8("%1").arg(dev[i]));
				linphone_core_set_playback_device(linphonec,dev[i]);
				append_log(QString::fromUtf8("放音使用设备：%1").arg(dev[i]));
			}
		}
#else
		for(int i=0; dev[i]!=NULL; ++i){
			if(linphone_core_sound_device_can_capture(linphonec,dev[i]))
			{//麦克风
				ui->comboBox_sndMic->addItem( QString::fromUtf8("%1").arg(dev[i]));
				linphone_core_set_capture_device(linphonec,dev[i]);
			}
			if(linphone_core_sound_device_can_playback(linphonec,dev[i])) 
			{//扬声器
				ui->comboBox_sndPlay->addItem( QString::fromUtf8("%1").arg(dev[i]));
				linphone_core_set_playback_device(linphonec,dev[i]);
			}
		}
#endif
		}
		return true;
	}else{
		sip_identity.clear();
		return false;
	}
}


void MainWindow::voip_uninit()
{
	sip_identity.clear();
	if(SIPstatus){
		if(timer_iterate){
			timer_iterate->stop();
			delete timer_iterate;
			timer_iterate=NULL;
		}
		linphonec_main_loop_exit();
		linphonec_finish(EXIT_SUCCESS);
		SIPstatus=false;
		ui->commandLinkButton->setDisabled(true);
	}
}


void MainWindow::set_call_status(int card, QString &status)
{
	QStandardItemModel *model = (QStandardItemModel *)ui->tableView->model();
	if(model){
		QModelIndex mindex=model->index(card,1);
		model->setData(mindex, QVariant::fromValue(status));
	}
}


void MainWindow::registration_state_changed(QString &status)
{
	ui->commandLinkButton->setText(status);
}


void registration_state_changed(struct _LinphoneCore *lc, LinphoneProxyConfig *cfg,
		LinphoneRegistrationState cstate, const char *message)
{
	QString status;
	switch (cstate){
		case LinphoneRegistrationOk:
			w->SIPRegStatus=true;
			status=QString::fromUtf8("注册成功");
		break;
		case LinphoneRegistrationProgress:
			w->SIPRegStatus=false;
			status=QString::fromUtf8("注册中...");
		break;
		case LinphoneRegistrationCleared:
			w->SIPRegStatus=false;
			status=QString::fromUtf8("未注册");
		break;
		case LinphoneRegistrationFailed:
			w->SIPRegStatus=false;
			status=QString::fromUtf8("注册失败");
		break;
		default:
		break;
	}
	w->registration_state_changed(status);
	return;
}



void MainWindow::WSSend(const QString &cmd)
{
	qint64 len=0;
	if(WSclient && WSconnectstatus){
		len =  WSclient->sendTextMessage(cmd);
		if(cmd.length() == len){
			append_log(cmd);
		}else{
			QMessageBox::information(this,QString::fromUtf8("WebSocket 命令发送失败"), cmd);
			append_log(QString::fromUtf8("WebSocket 命令发送失败:") + cmd);
		}
	}else{
		qDebug()<<"websocket is disconnected!";
		if(showWScloseInfo){
			QMessageBox::information(this,QString::fromUtf8("警告"),QString::fromUtf8("WebSocket未连接"));
		}
	}
}

void MainWindow::MSrecieved(const QString &msg)
{
	append_log(msg);
	readJson(msg);
}

void MainWindow::WSConnect()
{
	if(WSclient==NULL){
		WSclient=new QWebSocket;
		WSclient->setParent(this);
        qDebug()<<"create websocket!";
		connect(WSclient,&QWebSocket::textMessageReceived,[this](const QString &msg){
        this->MSrecieved(msg);});
    
		connect(WSclient,&QWebSocket::connected,[this](){
       
			WSconnectstatus=true;
			wsfirstrun=false;
			showWScloseInfo=false;
			m_timer->start(30 * 1000);
        
			append_log(QString("Client IP:%1  Port:%2")
                               .arg(WSclient->localAddress().toString())
                               .arg(WSclient->localPort()));
			
	        qDebug()<<"connected";
			WSSend(QString("HeartBeatData"));
			HeartBeat_status=false;
	   });
        connect(WSclient,SIGNAL(disconnected()),this,SLOT(onDisConnected()),Qt::AutoConnection);
        connect(m_timer,SIGNAL(timeout()),this, SLOT(heartbit()),Qt::AutoConnection);
        WSclient->open(WSUrl);
	}
	
}

void MainWindow::onDisConnected()
{
	qDebug()<<"DataReceive websocket is disconnected!!!";

	append_log(QString::fromUtf8("WebSocket连接断开:")+WSclient->closeReason());
    WSconnectstatus = false;

	if(wsfirstrun){//初始化连接失败
		QMessageBox::information(this,QString::fromUtf8("警告"),QString::fromUtf8("未能连接到设备，请检查设备,程序将退出！"));
		m_timer->stop();/*-<当连接失败时，触发重连计时器，设置计数周期为3秒 */
		this->on_actionquit_triggered();
	}else{
		device.CallStatus = Hangup;
		callDialog->hangup_sip();
		set_call_status(device.curCard, QString::fromUtf8("空闲"));
		WSclient->close();
		WSclient->open(WSUrl);
	}
}


void MainWindow::heartbit()
{
	//if(HeartBeat_status){
		WSSend(QString("HeartBeatData")); 
		HeartBeat_status=false;
	//}else{
		//QMessageBox::information(this,QString::fromUtf8("警告"),QString::fromUtf8("30秒未收到websocket心跳包应答，请退出程序重新运行"));
	//}
}



void MainWindow::readJson(const QString &json)
{
	QJsonParseError jsonerror;
	QJsonDocument doc = QJsonDocument::fromJson(json.toLatin1(), &jsonerror);
	int type=-1;
	QString typeStr;
	QString cmd;
	bool state=false;
	//QMessageBox::information(this,QString::fromUtf8("应答"),json);
	if (!doc.isNull() && jsonerror.error == QJsonParseError::NoError)
	{
		if(doc.isObject())
		{
			QJsonObject object = doc.object();
			QStringList list = object.keys();
			if(object.contains("type")){
				typeStr = object.value("type").toString();
				if(typeStr.contains("SMSPush")) type =9; 
				if(typeStr.contains("CommandResponse")) type =0;
				if(typeStr.contains("RealTimeState")) type =1;
				if(typeStr.contains("CallRecord")) type =2;
				if(typeStr.contains("AutoRecord")) type =3;
			}
			
			switch(type){

			case 0://命令的应答

				cmd = object.value("data").toObject().value("invoke_command").toString();
				state = object.value("data").toObject().value("state").toBool();
				if(cmd.contains("GetConnectedState_Multi") && state){
					device.deviceName = object.value("dynamicdata").toObject().value("devicelist").toString();
					ui->label_2->setText(QString::fromUtf8("设备已连接"));
					device.invoke_command.clear();
					qDebug()<< "device:" << object.value("dynamicdata").toObject().value("devicelist").toString();
				}
				if(cmd.contains("Dial")){
					device.invoke_command.clear();
					if(!state){
						QMessageBox::information(this,QString::fromUtf8("设备外呼失败"), object.value("message").toString());
						this->HangUp();
						QMessageBox::information(this,QString::fromUtf8("设备外呼失败"), QString::fromUtf8("程序将退出，请在确认设备正常后启动本程序"));
						this->on_actionquit_triggered();
					}
				}
				if(cmd.contains("HungUp")){
					device.invoke_command.clear();
				}
				if(cmd.contains("GetCBCurrState_Multi") && state){
					QString cards= object.value("dynamicdata").toString();
					QStringList cardsstrlist = cards.split(",");
					for(int i=0;i<5;i++){
						device.SIMCads_Info[i].Name=QString::fromUtf8("SIM卡%1").arg(i+1);
						if(cardsstrlist.at(i).contains("1")){
							device.SIMCads_Info[i].cardStatus = true;
							device.SimCardsCount++;
						}else{
							device.SIMCads_Info[i].cardStatus = false;
						}
					}

					device.invoke_command.clear();

					showCards();
					disconnect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangCard()));
					updateValidCards();
					connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangCard()));


					if(device.SimCardsCount>0){
						//QMessageBox::information(this,QString::fromUtf8("警告"),QString::fromUtf8("发现%1张SIM卡").arg(device.SimCardsCount));
						//更新可以指定工作的卡，默认使用第一张可用的卡呼叫

						device.deviceStatus=true;
						ui->label_2->setText(QString::fromUtf8("设备已连接,SIM卡就绪"));
						this->SIPAccount();
					}else{
						if(device.doChange>0){
							device.doChange--;
							QString acmd = QString::fromUtf8("{\"command\":\"GetCBCurrSim_Multi\",\"arguments\":{\"devicename\":\"%1\"}}").arg(device.deviceName);
							WSSend(acmd);
						}else{
							QMessageBox::information(this,QString::fromUtf8("警告"),QString::fromUtf8("没有发现SIM卡！请检查话机设备，程序将退出"));
							showWScloseInfo=false;
							this->on_actionquit_triggered();
						}
					}
					qDebug() << "SIM Cards Count: " << device.SimCardsCount;
				}
				//当前使用的卡
				if(cmd.contains("GetCBCurrSim_Multi")  && state ){
					if(device.doChange>0){
							device.doChange=0;		
					}
					int cardindxe= object.value("dynamicdata").toObject().value("simid").toInt();
					device.curCard = cardindxe;
					disconnect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangCard()));
					updateValidCards();
					for(int i=0; i<ui->comboBox->count();i++){
						if(cardindxe == ui->comboBox->itemData(i)){
							ui->comboBox->setCurrentIndex(i);	
						}
					}
					connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangCard()));					
				}

				//切卡成功
				if(cmd.contains("CBSwitch_Multi")  && state ){
					ui->comboBox->setEnabled(true);
					device.curCardReady=true;
					device.doChange=0;
					ui->label_2->setText(QString::fromUtf8("设备已连接,SIM卡就绪"));
					ui->label_6->setText(QString::fromUtf8("%1").arg(0));
					update_called_count(device.curCard);
				}

				if(!initCmd.isEmpty()){
					QString sendcmd=initCmd.first()[1];
					if(!device.deviceName.isEmpty()){
						device.invoke_command=initCmd.first()[0];
						initCmd.removeFirst();
						sendcmd = sendcmd.replace("000000", device.deviceName);
						WSSend(sendcmd);
						qDebug() << "WS send: " << device.invoke_command;
					}else {
						device.invoke_command=QString("GetConnectedState_Multi");
						WSSend("{\"command\":\"GetConnectedState_Multi\"}");
					}
				}
				break;
			case 1:
				qDebug() << object.value("devicename").toString();
				if(object.contains("dynamicdata")){
					//处理呼叫、振铃、接通、挂断等事件
					QString realtimestate;
					append_log(object.value("dynamicdata").toObject().value("realtimestate").toString());
					if(object.value("dynamicdata").toObject().contains("realtimestate")){
						QString realtimestate = object.value("dynamicdata").toObject().value("realtimestate").toString();
						QString typeInOut = object.value("dynamicdata").toObject().value("type").toString();
						
						append_log(QString::fromUtf8("realtimestate:%1").arg(realtimestate));

						if(realtimestate.contains("idle")){
							device.CallStatus = Idle;
							set_call_status(device.curCard, QString::fromUtf8("空闲"));
						}

						if(typeInOut.contains("out")){	
							if(realtimestate.contains("hangup")){
								device.CallStatus = Hangup;
								callDialog->hangup_sip();
								set_call_status(device.curCard, QString::fromUtf8("空闲"));
							}
							if(realtimestate.contains("outgoing")){
								device.CallStatus = Outgoing;

#if 1

								QString acmd = QString::fromUtf8("{\"command\":\"closechanneltoheadset_Multi\",\"arguments\":{\"devicename\":\"%1\"}}").arg(device.deviceName);
								WSSend(acmd);
								acmd = QString::fromUtf8("{\"command\":\"closeheadsettochannel_Multi\",\"arguments\":{\"devicename\":\"%1\"}}").arg(device.deviceName);
								WSSend(acmd);
								acmd = QString::fromUtf8("{\"command\":\"OpenOnewayRecord_Multi\",\"arguments\":{\"devicename\":\"%1\"}}").arg(device.deviceName);
								WSSend(acmd);
#endif

								set_call_status(device.curCard, QString::fromUtf8("正在呼叫%1").arg(device.curCalloutNumber));
								
							}
							if(realtimestate.contains("ringback")){
								device.CallStatus = Ringback;
								set_call_status(device.curCard, QString::fromUtf8("呼叫%1,振铃中").arg(device.curCalloutNumber));
								//QString acmd = QString::fromUtf8("{\"command\":\"closeheadsettochannel_Multi\",\"arguments\":{\"devicename\":\"%1\"}}").arg(device.deviceName);
								//WSSend(acmd);
								
								//closechanneltoheadset_Multi 
								//closeheadsettochannel_Multi
								//acmd = QString::fromUtf8("{\"command\":\"PlayStartRecord_Multi\",\"arguments\":{\"devicename\":\"%1\",\"content\":\"\"}}").arg(device.deviceName);
								//WSSend(acmd);
								
								//acmd = QString::fromUtf8("{\"command\":\"closechanneltoheadset_Multi\",\"arguments\":{\"devicename\":\"%1\"}}").arg(device.deviceName);
								//WSSend(acmd);
							}
							if(realtimestate.contains("outconnected")){
								device.CallStatus = Outconnected;
								set_call_status(device.curCard, QString::fromUtf8("呼叫%1,通话中").arg(device.curCalloutNumber));
								callDialog->answer_sip();
																
								
								//acmd = QString::fromUtf8("{\"command\":\"OpenOnewayRecord_Multi\",\"arguments\":{\"devicename\":\"%1\"}}").arg(device.deviceName);
								//WSSend(acmd);
								
								/*
								initCmd.append(QStringList()<<"closechanneltoheadset_Multi"<<"{\"command\":\"closechanneltoheadset_Multi\",\"arguments\":{\"devicename\":\"000000\"}}");

								initCmd.append(QStringList()<<"OpenOnewayRecord_Multi"<<"{\"command\":\"OpenOnewayRecord_Multi\",\"arguments\":{\"devicename\":\"000000\"}}");

								initCmd.append(QStringList()<<"openusbaududiotousbrecord_Multi"<<"{\"command\":\"openusbaududiotousbrecord_Multi\",\"arguments\":{\"devicename\":\"000000\"}}");

								initCmd.append(QStringList()<<"closeheadsettousbrecord_Multi"<<"{\"command\":\"closeheadsettousbrecord_Multi\",\"arguments\":{\"devicename\":\"000000\"}}");

								*/
							}
						}else{/*呼入的电话处理，接通、挂断*/
							
							if(realtimestate.contains("incoming")){
								device.CallStatus = Incoming;
								device.curCalloutNumber = object.value("dynamicdata").toObject().value("number").toString();
#if 1

								QString acmd = QString::fromUtf8("{\"command\":\"closechanneltoheadset_Multi\",\"arguments\":{\"devicename\":\"%1\"}}").arg(device.deviceName);
								WSSend(acmd);
								acmd = QString::fromUtf8("{\"command\":\"closeheadsettochannel_Multi\",\"arguments\":{\"devicename\":\"%1\"}}").arg(device.deviceName);
								WSSend(acmd);
								acmd = QString::fromUtf8("{\"command\":\"OpenOnewayRecord_Multi\",\"arguments\":{\"devicename\":\"%1\"}}").arg(device.deviceName);
								WSSend(acmd);
#endif
								/*读取主叫号码，设置为sip的from，发起sip呼叫
								待处理：sip接通后，给设备发送接通指令
								*/
								set_call_status(device.curCard, QString::fromUtf8("收到来电 %1").arg(device.curCalloutNumber));
								if (linphone_core_invite2(linphonec,device.curCalloutNumber.toUtf8())==NULL) {
										linphone_core_terminate_call(linphonec, NULL);
								}
								
							}
							if(realtimestate.contains("hangup")){
								device.CallStatus = Hangup;
								callDialog->hangup_sip();
								set_call_status(device.curCard, QString::fromUtf8("空闲"));
							}
						}
					}
				}
				break;
			case 2:
				break;
			case 3:
				break;
			case 9:
				//心跳包
				//qDebug() << "WS HeartBeatCheck " << object.value("type").toString();
				HeartBeat_status=true;

				if(!initCmd.isEmpty()){
					QString sendcmd=initCmd.first()[1];
					if(!device.deviceName.isEmpty()){
						device.invoke_command=initCmd.first()[0];
						initCmd.removeFirst();
						sendcmd = sendcmd.replace("000000", device.deviceName);
						WSSend(sendcmd);
						qDebug() << "WS send: " << device.invoke_command;
					}else{
						device.invoke_command=QString("GetConnectedState_Multi");
						WSSend("{\"command\":\"GetConnectedState_Multi\"}");
					}
				}
				break;
			default:
				break;
			}
		}
	}
}

