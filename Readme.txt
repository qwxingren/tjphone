Linphone VS2010 项目

TJphone.sln 
开发环境 ：vs2010(VC++)、windows SDK v6.1

更新日志：

2023-11-13
Qt安装的是Qt5.5.1 vs2010编译版本，安装路径
C:\Qt\Qt5.5.1\5.5\msvc2010\bin



2012-07-04
build解决方案时，可以选择四个配置：

Debug: debug,需要有intel ipp的静态lib放置在tjphone\SDK\Libs\Release\ipp 目录
Release: release,需要有intel ipp的静态lib放置在tjphone\SDK\Libs\Release\ipp 目录

所有配置，都是静态库编译，最终在生成tjphone.exe时link。


2011-08-08：
添加了基于intel ipp 5.1 的g723.1支持。linphone-3.4.1
发现bug：
1. linphone-3.3.1 当被叫不支持所有编码返回4**时，主叫方crash（linux平台上，windows平台还没有测试）
2. 在windows平台，当呼叫一个不存在的被叫时，在发起呼叫后，理解点击quit推出linphone，会出现内存无效访问的情况。（已经uninit linphonecore之后，呼叫超时继续处理callfailure时出错）


2011-08-04：
添加了基于intel ipp 5.1 的g729支持。linphone-3.4.1

2010-09-08：
完成在vs2008环境的build
