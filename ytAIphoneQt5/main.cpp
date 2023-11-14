#include "mainwindow.h"
#include "incomingcall.h"
#include <QApplication>
#include <QTimer>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QTextCodec>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif 

#include "linphonec.h"

incomingcall *callDialog=NULL;
MainWindow *w=NULL;

Qt::HANDLE g_mainThreadId = 0;

void testJson();


int main(int argc, char *argv[])
{
	int ret=0;
	QApplication *a = new QApplication(argc, argv);
	QTextCodec *codec=QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);
    
	/*
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "sqlite1");
    db.setDatabaseName(".//ytCall.db");
	if( !db.open())
    {
		QMessageBox::warning(NULL,QString::fromUtf8("言通智能呼叫"),
                                QString::fromUtf8("无法建立数据库连接"),
								   QMessageBox::Ok);
        return -1;
    }
	QSqlQuery query(db);
	QString sql = QString("select * from sqlite_master where type = 'table' and  name='automobil'");
	if(!query.exec(sql)){
		QMessageBox::warning(NULL,QString::fromUtf8("言通智能呼叫"),
                                QString::fromUtf8("sqlite数据库无法查询"),
								   QMessageBox::Ok);
        return -1;
	}
	if(!query.next()){
		bool success = query.exec("create table automobil(id int primary key,attribute varchar,"
								  "type varchar,kind varchar,nation int,carnumber int,elevaltor int,"
								  "distance int,oil int,temperature int)");
		if(!success)
		{
			QMessageBox::warning(NULL,QString::fromUtf8("言通智能呼叫"),
									QString::fromUtf8("数据库表创建失败！\n"),
									   QMessageBox::Ok);
			return -1;
		}
	}
	*/
	/*
	1. 读取配置，连接驱动的socket，失败则弹窗提示
		LinphoneCore 结构体添加 bool_t use_socket 和 int snd_socket; 元素，参考 use_files的实现，在创建stream时，使用socket，参考 audio_stream_record 的实现

	if (captcard!=NULL){
		if (stream->soundread==NULL)
			stream->soundread=ms_snd_card_create_reader(captcard);
	}else {
		stream->soundread=ms_filter_new(MS_FILE_PLAYER_ID);  //ms_filter_new(MS_SOCKET_READ_ID)
		stream->read_resampler=ms_filter_new(MS_RESAMPLE_ID); 
		if (infile!=NULL) audio_stream_play(stream,infile);   //替换为 audio_stream_play_socket(stream, socket);
	}
	if (playcard!=NULL) {
		if (stream->soundwrite==NULL)
			stream->soundwrite=ms_snd_card_create_writer(playcard);
	}else {
		stream->soundwrite=ms_filter_new(MS_FILE_REC_ID);	// ms_filter_new(MS_SOCKET_WRITE_ID)
		if (outfile!=NULL) audio_stream_record(stream,outfile); //audio_stream_record_socket(stream,socket);
	}


	2. socket连接成功后，初始化 linphonecore, 声卡设备指定为 socket设备
		void linphone_core_use_files(LinphoneCore *lc, bool_t yesno){
			lc->use_files=yesno;
		}

		void linphone_core_set_play_file(LinphoneCore *lc, const char *file){
			
		}

	3. 读取卡信息
	4. 创建sqlite表来记录数据

	linphone 启动 incomingcall 发送183 彩铃，

	是否支持183
	propose_early_media=lp_config_get_int(lc->config,"sip","incoming_calls_early_media",TRUE);

	启动 media_stream
	void linphone_call_start_media_streams(LinphoneCall *call, bool_t all_inputs_muted, bool_t send_ringbacktone)

	*/

	QFont font("simsun",11,QFont::Normal,FALSE);
	a->setFont(font);
	a->setApplicationName(QString::fromUtf8("言通智能呼叫"));

	w = new MainWindow();

	callDialog = new incomingcall();
	
    
    w->show();
	callDialog->show();
	callDialog->hide();

	//testJson();
    ret = a->exec();

	delete callDialog;
	delete w;
	delete a;
	return ret;
}



void testJson()
{
	//QString json("{\"devicename\":\"EV785B20220500728\",\"dynamicdata\":{\"extraparam\":null,\"number\":\"10086\",\"realtimestate\":\"hangup\",\"talkid\":\"EV785B2022050072820220603151938638\",\"type\":\"out\"},\"type\":\"RealTimeState\"}");
	QString json("{\"data\":{\"cid\":null,\"invoke_command\":\"GetConnectedState_Multi\",\"state\":true},\"dynamicdata\":{\"devicelist\":\"EV785B20220500728\"},\"message\":\"\",\"type\":\"CommandResponse\"}");
	QJsonParseError jsonerror;
	QJsonDocument doc = QJsonDocument::fromJson(json.toLatin1(), &jsonerror);
	if (!doc.isNull() && jsonerror.error == QJsonParseError::NoError)
	{
		if(doc.isObject())
		{
			QJsonObject object = doc.object();
			QStringList list = object.keys();
			for(int i = 0; i < list.count(); i++)
			{
				qDebug() << list.at(i);
			}
			if(object.contains("data")){
				QString cmd = object.value("data").toObject().value("invoke_command").toString();
				qDebug() << cmd;
				if(cmd.contains("GetConnectedState")){
					qDebug()<< "device:" << object.value("dynamicdata").toObject().value("devicelist").toString();
				}
			}else if(object.contains("devicename")){
				qDebug() << object.value("devicename").toString();
			}
			QJsonObject::iterator it = object.begin();
			while(it != object.end())
			{
				switch(it.value().type())
				{
				case QJsonValue::String:
					{
						qDebug() << "Type is string";
						QJsonArray sub = it.value().toArray();
						qDebug() << it.key() << "=" << it.value().toString();
						break;
					}
				case QJsonValue::Array:
					{
						qDebug() << "Type is Array";
						qDebug() << it.key() << "=" << it.value().toArray();
						QJsonArray sub = it.value().toArray();
						qDebug() << "index 1:" << sub.at(0).toDouble();
						qDebug() << "index 2:" << sub.at(1).toString();
						qDebug() << "index 3:" << sub.at(2).toBool();
						break;
					}
				case QJsonValue::Bool:
					{
						qDebug() << "Type is Bool";
						qDebug() << it.key() << "=" << it.value().toBool();
						break;
					}
				case QJsonValue::Double:
					{
						qDebug() << "Type is Double";
						qDebug() << it.key() << "=" << it.value().toDouble();
						break;
					}
				case QJsonValue::Object:
					{
						qDebug() << "Type is Object";
						qDebug() << it.key() << "=" << it.value().toObject().value("invoke_command");
						break;
					}
				case QJsonValue::Null:
					{
						qDebug() << "Type is Null";
						qDebug() << it.key() << "= NULL" ;
						break;
					}
				case QJsonValue::Undefined:
					{
						qDebug() << "Type is Undefined";
						break;
					}
				}
				it++;
			}
		}
	}
}