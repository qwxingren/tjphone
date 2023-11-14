#ifndef DB_H
#define DB_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>


class sip_account_data
{
public:
	QString number;
	QString secret;
	QString proxy;
	QString domain;
	unsigned int port;
};

class db : public QObject
{
	Q_OBJECT

public:
	db(QObject *parent);
	~db();
	bool get_sipconfig(sip_account_data &sip_config);
	bool save_sipconfig(sip_account_data &sip_config);
private:
	QSqlDatabase _db;
	//QSqlQuery _query;
	bool dbIsOk;
};



#endif // DB_H
