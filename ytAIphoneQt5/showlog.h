#ifndef SHOWLOG_H
#define SHOWLOG_H

#include <QDialog>
#include "ui_showlog.h"

class ShowLog : public QDialog
{
	Q_OBJECT

public:
	ShowLog(QWidget *parent = 0);
	~ShowLog();
	void append_log(const QString &logs);

private:
	Ui::ShowLog ui;
};

#endif // SHOWLOG_H
