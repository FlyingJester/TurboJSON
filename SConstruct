import os
environment = Environment()
if os.name == 'posix':
    environment.Append(CCFLAGS = " -Wall -Wextra -pedantic -Werror -Os -g ", CFLAGS = " -ansi ", CXXFLAGS = " -std=c++11 -fno-rtti -fno-exceptions", LINKFLAGS = " -g ")
SConscript(dirs=["."], exports=["environment"])