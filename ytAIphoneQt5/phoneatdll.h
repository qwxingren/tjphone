#ifndef PHONEATDLL_H
#define PHONEATDLL_H
#include <windows.h>
/*#if defined(PHONEATDLL_LIBRARY)
#  define PHONEATDLL_API Q_DECL_EXPORT
#else
#  define PHONEATDLL_API Q_DECL_IMPORT
#endif*/

#if defined(PHONEATDLL_LIBRARY)
#define PHONEATDLL_API __declspec(dllexport)
#else
#define PHONEATDLL_API __declspec(dllimport)
#endif

#pragma pack(push, 1)
typedef struct tagCallRecord
{
    int type;
    int index;
    char number[20];
    char time[20];
    char callId[33];
} CALLRECORD;
#pragma pack(pop)//恢复对齐状态



typedef int (__stdcall *Pkaer_Box_CallBack)(int type, const char*lpMultiByteStr, const char *a4, int a5, int a6);
typedef int(__stdcall *Pkaer_EncryptMsg_CallBack)(/*[IN]*/const char* pszSrcMsg, /*[IN]*/const unsigned int uSrcLen, /*[IN-OUT]*/char* pszDstMsg, /*[IN-OUT]*/unsigned int* puDstLen);
typedef int(__stdcall *Pkaer_DecryptMsg_CallBack)(/*[IN]*/const char* pszSrcMsg, /*[IN]*/const unsigned int uSrcLen, /*[INT-OUT]*/char* pszDstMsg, /*[INT-OUT]*/unsigned int* puDstLen, /*[OUT]*/ unsigned int* puValidLen);

extern "C" PHONEATDLL_API int __stdcall kaer_module_init();
extern "C" PHONEATDLL_API int __stdcall kaer_module_initex(int port);
extern "C" PHONEATDLL_API int __stdcall kaer_module_exit();
extern "C" PHONEATDLL_API int __stdcall kaer_Dial_Number(const char* number);
extern "C" PHONEATDLL_API int __stdcall kaer_Dial_callId(const char* number, int hidden, char * callId);
extern "C" PHONEATDLL_API int __stdcall kaer_Read_Version(char*a1, size_t a2);
extern "C" PHONEATDLL_API int __stdcall kaer_Read_Serial_Num(char*a1, size_t a2);
extern "C" PHONEATDLL_API int __stdcall kaer_Box_Open(Pkaer_Box_CallBack callBack);
extern "C" PHONEATDLL_API int __stdcall kaer_setEncryptCallback(Pkaer_EncryptMsg_CallBack pEncryptCallBack, Pkaer_DecryptMsg_CallBack pDecryptCallBack);
extern "C" PHONEATDLL_API int __stdcall kaer_Dial_Dtmf(const char* number);
extern "C" PHONEATDLL_API int __stdcall kaer_Msg_Send(const char* number, const char*msg);
extern "C" PHONEATDLL_API int __stdcall kaer_Hang_Up();
extern "C" PHONEATDLL_API int __stdcall kaer_Answer();
extern "C" PHONEATDLL_API int __stdcall kaer_setPhoneMode(int mode);
extern "C" PHONEATDLL_API int __stdcall kaer_getPhoneMode();
extern "C" PHONEATDLL_API int __stdcall kaer_Dial_NumberHide(const char* number);
extern "C" PHONEATDLL_API int __stdcall kaer_getPhoneCsq();
extern "C" PHONEATDLL_API int __stdcall kaer_getCallStat();
extern "C" PHONEATDLL_API int __stdcall kaer_setRecordMode(int flag);
extern "C" PHONEATDLL_API int __stdcall kaer_setNetFlow(int swit);
extern "C" PHONEATDLL_API int __stdcall kaer_getNetFlow();
extern "C" PHONEATDLL_API int __stdcall kaer_setPhoneTime(const char *time);
extern "C" PHONEATDLL_API int __stdcall kaer_setMicSwitch(int swit);
extern "C" PHONEATDLL_API int __stdcall SetWirelessPhoneLog(const char *pwszLogPath);
extern "C" PHONEATDLL_API int __stdcall kaer_Read_Sim_Card_Status();
extern "C" PHONEATDLL_API int __stdcall kaer_hideNumber(int type, int hidden);
extern "C" PHONEATDLL_API int __stdcall kaer_getNumberHiden(int type);
extern "C" PHONEATDLL_API int __stdcall kaer_setRecordVoice(int voice);
extern "C" PHONEATDLL_API int __stdcall kaer_Read_phoneNumber(char*a1, size_t a2);
extern "C" PHONEATDLL_API int __stdcall kaer_setRecordFormat(int recordFormat);
extern "C" PHONEATDLL_API int __stdcall kaer_StartRecording(const char* pszRecordFile);
extern "C" PHONEATDLL_API int __stdcall kaer_StopRecording();
extern "C" PHONEATDLL_API int __stdcall kaer_Read_Reg_Status();
extern "C" PHONEATDLL_API int __stdcall kaer_setCallVoice(int voice);
extern "C" PHONEATDLL_API int __stdcall SetMainHandle(HWND wnd);
extern "C" PHONEATDLL_API int __stdcall kaer_callWait(int waitType);
extern "C" PHONEATDLL_API int __stdcall kaer_setPhoneUOC(int UOC);
extern "C" PHONEATDLL_API int __stdcall kaer_getPhoneUOC();
extern "C" PHONEATDLL_API int __stdcall kaer_httpPost(const char *url, const char *contentType, const char *body, char *resBody);
extern "C" PHONEATDLL_API int __stdcall kaer_httpPostFile(const char *url, const char *forms, const char *files, char *resBody);
extern "C" PHONEATDLL_API int __stdcall kaer_getHardVer(char *hardVer, int size);
extern "C" PHONEATDLL_API int __stdcall kaer_getGinMod();
extern "C" PHONEATDLL_API int __stdcall kaer_setGinMod(int mod);
extern "C" PHONEATDLL_API int __stdcall kaer_getCallVoice();
extern "C" PHONEATDLL_API int __stdcall kaer_getCallVoice();
extern "C" PHONEATDLL_API int __stdcall kaer_reboot();
extern "C" PHONEATDLL_API int __stdcall kaer_upgrade();
extern "C" PHONEATDLL_API int __stdcall kaer_readCallRecords(int type, int begIndex, int endIndex, CALLRECORD*pCallRecords, int *count);
extern "C" PHONEATDLL_API int __stdcall kaer_readMeid(char *meid);
extern "C" PHONEATDLL_API int __stdcall kaer_setAutoRecord(int autoRecord);
extern "C" PHONEATDLL_API int __stdcall kaer_setAllowCall(int swit);
extern "C" PHONEATDLL_API int __stdcall kaer_setSpeedCall(int num, const char *number);
extern "C" PHONEATDLL_API int __stdcall kaer_getSpeedCall(int num, char *number);
extern "C" PHONEATDLL_API int __stdcall kaer_setLocalPlay(int swit);
extern "C" PHONEATDLL_API int __stdcall kaer_setRecordPath(const char *pRecordPath);
extern "C" PHONEATDLL_API int __stdcall kaer_changeSim(int simIndex);
extern "C" PHONEATDLL_API int __stdcall kaer_downloadFile(const char *pFilePath);
extern "C" PHONEATDLL_API int __stdcall kaer_deleteFile(const char *pFilePath);
extern "C" PHONEATDLL_API int __stdcall kaer_getIccid(char *iccid, char *localNumber, char *sim);
extern "C" PHONEATDLL_API int __stdcall kaer_getHardStatus(int *dc, int *csq, int *sim);
extern "C" PHONEATDLL_API int __stdcall kaer_executeAt(const char *buf, char *resData);
extern "C" PHONEATDLL_API int __stdcall kaer_getSimIndex();
extern "C" PHONEATDLL_API int __stdcall kaer_send_device(const char *pszMsg, const unsigned int uLen);
#endif // PHONEATDLL_H
