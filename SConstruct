import os

environment = Environment()

if os.name == 'posix':
    environment.Append(CCFLAGS = " -Wall -Wextra -pedantic -Werror -Os -g ", CFLAGS = " -ansi ", CXXFLAGS = " -std=c++11 -fno-rtti -fno-exceptions")

default_environment = environment.Clone()
turbojson = SConscript(dirs = [os.getcwd()], exports = "default_environment")
