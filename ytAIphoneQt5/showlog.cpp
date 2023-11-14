#include "showlog.h"
#include <QTime>

ShowLog::ShowLog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

ShowLog::~ShowLog()
{

}

void ShowLog::append_log(const QString &logs)
{
	ui.textBrowser->append("");
	ui.textBrowser->append(QString::fromUtf8("%1\t%2").arg(QTime::currentTime().toString()).arg(logs));
}
