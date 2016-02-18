# Microsoft Developer Studio Project File - Name="tokamak" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=tokamak - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "tokamak.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "tokamak.mak" CFG="tokamak - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "tokamak - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "tokamak - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "tokamak - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /O2 /I "../../include/" /D "WIN32" /D "_LIB" /D "_CRT_SECURE_NO_DEPRECATE" /D "NDEBUG" /YX /FD /c
# ADD CPP /nologo /MT /W3 /O2 /I "../../include/" /D "WIN32" /D "_LIB" /D "_CRT_SECURE_NO_DEPRECATE" /D "NDEBUG" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "WIN32" /d "_LIB" /d "_CRT_SECURE_NO_DEPRECATE" /d "NDEBUG" /i "../../include/"
# ADD RSC /l 0x409 /d "NDEBUG" /d "WIN32" /d "_LIB" /d "_CRT_SECURE_NO_DEPRECATE" /d "NDEBUG" /i "../../include/"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../lib/tokamak_m.lib"

!ELSEIF  "$(CFG)" == "tokamak - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /ZI /Od /I "../../include/" /D "WIN32" /D "_LIB" /D "_CRT_SECURE_NO_DEPRECATE" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /ZI /Od /I "../../include/" /D "WIN32" /D "_LIB" /D "_CRT_SECURE_NO_DEPRECATE" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "WIN32" /d "_LIB" /d "_CRT_SECURE_NO_DEPRECATE" /i "../../include/"
# ADD RSC /l 0x409 /d "_DEBUG" /d "WIN32" /d "_LIB" /d "_CRT_SECURE_NO_DEPRECATE" /i "../../include/"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../lib/tokamak_md.lib"

!ENDIF

# Begin Target

# Name "tokamak - Win32 Release"
# Name "tokamak - Win32 Debug"
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
