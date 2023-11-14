#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QtWebSockets>
#include <QTimer>
#include <QString>

#include "showlog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
	void registration_state_changed(QString &status);

	void set_call_status(int card, QString &status);
	bool SIPRegStatus;
	void readJson(const QString &json);
	void CallOut(const QString &number);
	void AnswerIncomingCall(const QString &number);
	void HangUp();

	void showCards();
	ShowLog *_logDlg;

public slots:
	void linphone_qt_iterate();


private slots:
	void sip_register();
	void on_actiongaojie_triggered();
	void on_actionyantong_triggered();
	void on_actionquit_triggered();
	void on_actionTestcall_triggered();
	void SIPAccount();
	void ChangCard();
	
	void WSConnect();
	void WSSend(const QString &cmd);
	void onDisConnected();
	void heartbit();
	void MSrecieved(const QString &msg);

	void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
	//QTimer *timer_iterate;
	QString sip_identity;
	bool SIPstatus;
	bool voip_init();
	void voip_uninit();
	void updateValidCards();
	void append_log(const QString &log);
	void update_called_count(int cardindex);

	QWebSocket *WSclient;
	bool WSconnectstatus;
	bool showWScloseInfo;
	bool HeartBeat_status; //true£¬have received HeartBeat response¡£false£¬ send a HeartBeat data
	bool wsfirstrun;
	QTimer *m_timer;
	QTimer *timer_iterate;

	QList<QStringList> initCmd;

	
};
extern MainWindow *w;
#endif // MAINWINDOW_H
