#include "db.h"
#include <QMessageBox>
#include <QTextCodec>

#include <QtSql/QSqlDriver>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlResult>
#include <QVariant>

#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif 

db::db(QObject *parent)
	: QObject(parent)
{

	QTextCodec *codec=QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);
   
	dbIsOk=false;
	_db = QSqlDatabase::QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE", "sqlite1"));
    _db.setDatabaseName("./ytCall.db");
	
	if( !_db.open())
    {
		QMessageBox::warning(NULL,QString::fromUtf8("无法建立数据库连接"),
								   _db.lastError().text(),
								   QMessageBox::Ok);
        return;
    }
	QSqlQuery _query = QSqlQuery(_db);
	QString sql = QString("select * from sqlite_master where type = 'table' and  name='sipaccount'");
	if(!_query.exec(sql)){
		QMessageBox::warning(NULL,QString::fromUtf8("sqlite数据库无法查询"),
								_db.lastError().text(),
								QMessageBox::Ok);
        return;
	}

	if(!_query.next()){
		bool success = _query.exec("create table sipaccount(id int primary key,number varchar,"
								  "secret varchar,proxy varchar,port int,"
								  "domain varchar)");
		if(!success)
		{
			QMessageBox::warning(NULL,QString::fromUtf8("数据库表创建失败"),
									_db.lastError().text(),
								    QMessageBox::Ok);
			return;
		}
	}

	dbIsOk=true;
}

db::~db()
{
}

bool db::get_sipconfig(sip_account_data &sip_config)
{
	QSqlQuery _query = QSqlQuery(_db);
	if(_query.exec("select count(id) as re_count from sipaccount"))
	{
		if(_query.record().count()>0 && _query.next()){
			if(_query.record().value("re_count").toUInt()==0){
				return true;
			}
		}else{
			return false;
		}
	}


	if(_query.exec("select * from sipaccount"))
	{
		if(_query.record().count()>0 && _query.next()){
			sip_config.domain = _query.record().value("domain").toString();
			sip_config.number = _query.record().value("number").toString();
			sip_config.port = _query.record().value("port").toUInt();
			sip_config.proxy=_query.record().value("proxy").toString();
			sip_config.secret=_query.record().value("secret").toString();
		}else{
			QMessageBox::warning(NULL,QString::fromUtf8("sipaccount表查询失败"),
								_db.lastError().text(),
								QMessageBox::Ok);
			return false;
		}
	}else{
		QMessageBox::warning(NULL,QString::fromUtf8("sipaccount表查询失败"),
								_db.lastError().text(),
								QMessageBox::Ok);
		return false;
	}
	return true;
}

bool db::save_sipconfig(sip_account_data &sip_config)
{

	QSqlQuery _query = QSqlQuery(_db);
	QString sql = QString("delete from sipaccount");
	if(!_query.exec(sql)){
		QMessageBox::warning(NULL,QString::fromUtf8("sipaccount表删除失败"),
								_db.lastError().text(),
								QMessageBox::Ok);
		return false;
	}else{
		/*
		sql = QString("insert into sipaccount (id, number, secret, proxy, port, domain) value(" 
						+ sip_config.number + "','"
						+ sip_config.secret + "','"
						+ sip_config.proxy + "',"
						+ QString::number(sip_config.port) + ",'"
						+ sip_config.domain + "')");
		*/
		_query.prepare("insert into sipaccount (id, number, secret, proxy, port, domain) VALUES (:id, :number, :secret, :proxy, :port, :domain)");
		_query.bindValue(":id", 1);
		_query.bindValue(":number", sip_config.number);
		_query.bindValue(":secret", sip_config.secret);
		_query.bindValue(":proxy", sip_config.proxy);
		_query.bindValue(":port", sip_config.port);
		_query.bindValue(":domain", sip_config.domain);

		if(!_query.exec()){
			QMessageBox::warning(NULL,QString::fromUtf8("sipaccount表写入失败"),
								_db.lastError().text(),
								QMessageBox::Ok);
			return false;
		}
	}
	return true;
}