# Microsoft Developer Studio Project File - Name="tokamakdll" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=tokamakdll - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "tokamakdll.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "tokamakdll.mak" CFG="tokamakdll - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "tokamakdll - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "tokamakdll - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "tokamakdll - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "../../lib"
# PROP BASE Intermediate_Dir "obj/Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../lib"
# PROP Intermediate_Dir "obj/Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /O2 /I "../../include/" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_CRT_SECURE_NO_DEPRECATE" /D "TOKAMAK_USE_DLL" /D "TOKAMAK_DLL_EXPORTS" /D "NDEBUG" /YX /FD /c
# ADD CPP /nologo /MD /W3 /O2 /I "../../include/" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_CRT_SECURE_NO_DEPRECATE" /D "TOKAMAK_USE_DLL" /D "TOKAMAK_DLL_EXPORTS" /D "NDEBUG" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "WIN32" /d "_WINDOWS" /d "_USRDLL" /d "_CRT_SECURE_NO_DEPRECATE" /d "TOKAMAK_USE_DLL" /d "TOKAMAK_DLL_EXPORTS" /d "NDEBUG" /i "../../include/"
# ADD RSC /l 0x409 /d "NDEBUG" /d "WIN32" /d "_WINDOWS" /d "_USRDLL" /d "_CRT_SECURE_NO_DEPRECATE" /d "TOKAMAK_USE_DLL" /d "TOKAMAK_DLL_EXPORTS" /d "NDEBUG" /i "../../include/"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /dll /machine:I386 /implib:"../../lib/tokamakdll.lib" /out:"../../lib/tokamakdll.dll" /libpath:"../../lib"
# ADD LINK32 /nologo /dll /machine:I386 /implib:"../../lib/tokamakdll.lib" /out:"../../lib/tokamakdll.dll" /libpath:"../../lib"

!ELSEIF  "$(CFG)" == "tokamakdll - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "../../lib"
# PROP BASE Intermediate_Dir "obj/Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../lib"
# PROP Intermediate_Dir "obj/Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /ZI /Od /I "../../include/" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_CRT_SECURE_NO_DEPRECATE" /D "TOKAMAK_USE_DLL" /D "TOKAMAK_DLL_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /ZI /Od /I "../../include/" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_CRT_SECURE_NO_DEPRECATE" /D "TOKAMAK_USE_DLL" /D "TOKAMAK_DLL_EXPORTS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "WIN32" /d "_WINDOWS" /d "_USRDLL" /d "_CRT_SECURE_NO_DEPRECATE" /d "TOKAMAK_USE_DLL" /d "TOKAMAK_DLL_EXPORTS" /i "../../include/"
# ADD RSC /l 0x409 /d "_DEBUG" /d "WIN32" /d "_WINDOWS" /d "_USRDLL" /d "_CRT_SECURE_NO_DEPRECATE" /d "TOKAMAK_USE_DLL" /d "TOKAMAK_DLL_EXPORTS" /i "../../include/"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /dll /incremental:yes /debug /machine:I386 /implib:"../../lib/tokamakdll_d.lib" /out:"../../lib/tokamakdll_d.dll" /pdbtype:sept /libpath:"../../lib"
# ADD LINK32 /nologo /dll /incremental:yes /debug /machine:I386 /implib:"../../lib/tokamakdll_d.lib" /out:"../../lib/tokamakdll_d.dll" /pdbtype:sept /libpath:"../../lib"

!ENDIF

# Begin Target

# Name "tokamakdll - Win32 Release"
# Name "tokamakdll - Win32 Debug"
# Begin Group "tokamaksrc"

# PROP Default_Filter ""
# Begin Group "src"

# PROP Default_Filter ""
# Begin Source File

SOURCE=../../tokamaksrc/src/collision.h
# End Source File
# Begin Source File

SOURCE=../../tokamaksrc/src/collision2.h
# End Source File
# Begin Source File

SOURCE=../../tokamaksrc/src/constraint.h
# End Source File
# Begin Source File

SOURCE=../../tokamaksrc/src/containers.h
# End Source File
# Begin Source File

SOURCE=../../tokamaksrc/src/dcd.h
# End Source File
# Begin Source File

SOURCE=../../tokamaksrc/src/message.h
# End Source File
# Begin Source File

SOURCE=../../tokamaksrc/src/perfwin32.h
# End Source File
# Begin Source File

SOURCE=../../tokamaksrc/src/rigidbody.h
# End Source File
# Begin Source File

SOURCE=../../tokamaksrc/src/scenery.h
# End Source File
# Begin Source File

SOURCE=../../tokamaksrc/src/simulator.h
# End Source File
# Begin Source File

SOURCE=../../tokamaksrc/src/stack.h
# End Source File
# Begin Source File

SOURCE=../../tokamaksrc/src/boxcylinder.cpp
# End Source File
# Begin Source File

SOURCE=../../tokamaksrc/src/collision.cpp
# End Source File
# Begin Source File

SOURCE=../../tokamaksrc/src/collisionbody.cpp
# End Source File
# Begin Source File

SOURCE=../../tokamaksrc/src/constraint.cpp
# End Source File
# Begin Source File

SOURCE=../../tokamaksrc/src/cylinder.cpp
# End Source File
# Begin Source File

SOURCE=../../tokamaksrc/src/dcd.cpp
# End Source File
# Begin Source File

SOURCE=../../tokamaksrc/src/lines.cpp
# End Source File
# Begin Source File

SOURCE=../../tokamaksrc/src/ne_interface.cpp
# End Source File
# Begin Source File

SOURCE=../../tokamaksrc/src/perfwin32.cpp
# End Source File
# Begin Source File

SOURCE=../../tokamaksrc/src/region.cpp
# End Source File
# Begin Source File

SOURCE=../../tokamaksrc/src/restcontact.cpp
# End Source File
# Begin Source File

SOURCE=../../tokamaksrc/src/rigidbody.cpp
# End Source File
# Begin Source File

SOURCE=../../tokamaksrc/src/rigidbodybase.cpp
# End Source File
# Begin Source File

SOURCE=../../tokamaksrc/src/scenery.cpp
# End Source File
# Begin Source File

SOURCE=../../tokamaksrc/src/simulator.cpp
# End Source File
# Begin Source File

SOURCE=../../tokamaksrc/src/solver.cpp
# End Source File
# Begin Source File

SOURCE=../../tokamaksrc/src/sphere.cpp
# End Source File
# Begin Source File

SOURCE=../../tokamaksrc/src/stack.cpp
# End Source File
# Begin Source File

SOURCE=../../tokamaksrc/src/tricollision.cpp
# End Source File
# Begin Source File

SOURCE=../../tokamaksrc/src/useopcode.cpp
# End Source File
# End Group
# End Group
# End Target
# End Project
