# Microsoft Developer Studio Project File - Name="gsm" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=gsm - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "gsm.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "gsm.mak" CFG="gsm - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "gsm - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "gsm - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "gsm - Win32 No Crypto Release" (based on\
 "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe

!IF  "$(CFG)" == "gsm - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir "."
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Target_Dir "."
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /I ".\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "gsm - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir "."
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Target_Dir "."
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /Z7 /Od /I ".\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "gsm - Win32 No Crypto Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "No Crypto Release"
# PROP BASE Intermediate_Dir "No Crypto Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Nocrypto"
# PROP Intermediate_Dir ".\Nocrypto"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /I ".\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I ".\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "gsm - Win32 Release"
# Name "gsm - Win32 Debug"
# Name "gsm - Win32 No Crypto Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\Add.c
# End Source File
# Begin Source File

SOURCE=.\Code.c
# End Source File
# Begin Source File

SOURCE=.\Debug.c
# End Source File
# Begin Source File

SOURCE=.\Decode.c
# End Source File
# Begin Source File

SOURCE=.\Gsm_crea.c
# End Source File
# Begin Source File

SOURCE=.\Gsm_deco.c
# End Source File
# Begin Source File

SOURCE=.\Gsm_dest.c
# End Source File
# Begin Source File

SOURCE=.\Gsm_enco.c
# End Source File
# Begin Source File

SOURCE=.\Gsm_expl.c
# End Source File
# Begin Source File

SOURCE=.\Gsm_impl.c
# End Source File
# Begin Source File

SOURCE=.\Gsm_opti.c
# End Source File
# Begin Source File

SOURCE=.\Gsm_prin.c
# End Source File
# Begin Source File

SOURCE=.\Long_ter.c
# End Source File
# Begin Source File

SOURCE=.\Lpc.c
# End Source File
# Begin Source File

SOURCE=.\Preproce.c
# End Source File
# Begin Source File

SOURCE=.\Rpe.c
# End Source File
# Begin Source File

SOURCE=.\Short_te.c
# End Source File
# Begin Source File

SOURCE=.\Table.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\inc\config.h
# End Source File
# Begin Source File

SOURCE=.\inc\gsm.h
# End Source File
# Begin Source File

SOURCE=.\inc\private.h
# End Source File
# Begin Source File

SOURCE=.\inc\proto.h
# End Source File
# Begin Source File

SOURCE=.\Inc\Unproto.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
