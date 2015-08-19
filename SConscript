import sys

Import("default_environment")

environment = default_environment.Clone()
environment.Replace(AS = ARGUMENTS.get('assembler', 'yasm'))
utils = ["whitespace.c", "string.c"]

disable_asm = False

if sys.platform == 'darwin' and not disable_asm:
    environment.Append(ASFLAGS = " -f macho64")
    utils = ["whitespace.amd64.s", "string.amd64.s"]
elif sys.platform.startswith('linux') and not disable_asm:
    environment.Append(ASFLAGS = " -f elf64 ")
    utils = ["whitespace.amd64.s", "string.amd64.s"]

turbojson = environment.StaticLibrary("turbojson", ["turbojson.cpp"] + utils)

Return("turbojson")
