@echo off
@echo on
copy %0 command.bat
copy "d:\works\softphone\linphone-vc++\linphone-3.1.0\coreapi\build\vs2005\Debug\libcoreapi.lib" "D:\works\softphone\linphone-vc++\linphone-3.1.0\coreapi\build\vs2005\libs\Debug\"

if errorlevel 1 goto VCReportError
goto VCEnd
:VCReportError
echo Project : error PRJ0019: ���ߴ�"����ִ�����ɺ��¼�..."
exit 1
:VCEnd