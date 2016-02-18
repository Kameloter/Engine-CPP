-- Tokamak Premake (c) Adrian Boeing 2007 
-- http://www.adrianboeing.com 

-- tokamak : http://sourceforge.net/projects/tokamakp/
-- premake : http://premake.sourceforge.net/ 

--[[
Tokamak Physics Engine Premake file
Copyright (c) 2007, Adrian Boeing.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.

Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

Neither the names of tokamak's premake copyright owner nor the names of its
contributors may be used to endorse or promote products derived from
this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
]]--

--Project name (MSVC solution) 
project.name = "tokamak"
--location where the project make files will be located
project.path = "build/" .. target
--location where the executable files will be located
project.bindir = "lib" --dll's
project.libdir = "lib" --lib's

--==========================================
--This is the tokamak STATIC project
--Package : (MSVC project) 
package = newpackage()
package.name = "tokamak"
--location where the project make files will be located
package.path = "build/" .. target
--name of lib file
package.config["Debug"].target   = "tokamak_md"
package.config["Release"].target = "tokamak_m"
--type of project, ie exe,winexe,dll,lib
package.kind = "lib"
package.language = "c++"
--location of the program source code
rloc = "../../"
package.includepaths = {rloc .. "include/" }
package.files = { 
	matchfiles(rloc .. "tokamaksrc/src/*.h", rloc.."tokamaksrc/src/*.cpp")
	}
--exclude operating specific files
if (windows) then
package.excludes = {
  rloc .. "tokamaksrc/src/test.cpp",
  rloc .. "tokamaksrc/src/perflinux.cpp",
  rloc .. "tokamaksrc/src/perflinux.h"
  }
else
package.excludes = {
  rloc .. "tokamaksrc/src/test.cpp",
  rloc .. "tokamaksrc/src/perfwin32.cpp",
  rloc .. "tokamaksrc/src/perfwin32.h"
  }
end
--set the compiler definitions
package.config["Release"].defines = {"NDEBUG"}
if (windows) then
	package.defines = { "WIN32", "_LIB", "_CRT_SECURE_NO_DEPRECATE"}
end
--set the build flags
package.buildflags = { "no-exceptions", "no-rtti", "static-runtime" }

--==========================================
if (windows) then
--This is the tokamak DLL project
--Package : (MSVC project) 
package = newpackage()
package.name = "tokamakdll"
--location where the project make files will be located
package.path = "build/" .. target
--name of lib file
package.config["Debug"].target   = "tokamakdll_d"
--type of project, ie exe,winexe,dll,lib
package.kind = "dll"
package.language = "c++"
--location of the program source code
rloc = "../../"
package.includepaths = {rloc .. "include/" }
package.files = { 
	matchfiles(rloc .. "tokamaksrc/src/*.h", rloc.."tokamaksrc/src/*.cpp")
	}
--exclude operating specific files
if (windows) then
package.excludes = {
  rloc .. "tokamaksrc/src/test.cpp",
  rloc .. "tokamaksrc/src/perflinux.cpp",
  rloc .. "tokamaksrc/src/perflinux.h"
  }
else
package.excludes = {
  rloc .. "tokamaksrc/src/test.cpp",
  rloc .. "tokamaksrc/src/perfwin32.cpp",
  rloc .. "tokamaksrc/src/perfwin32.h"
  }
end
--set the compiler definitions
package.config["Release"].defines = {"NDEBUG"}
if (windows) then
	package.defines = { "WIN32", "_WINDOWS", "_USRDLL", "_CRT_SECURE_NO_DEPRECATE", "TOKAMAK_USE_DLL","TOKAMAK_DLL_EXPORTS"}
end
--set the build flags
package.buildflags = { "no-exceptions", "no-rtti" }
end

 