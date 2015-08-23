import os
import sys

Import("environment")

environment = Environment(tools=['default', 'nasm'])
environment.Replace(AS = "yasm")

disable_asm = False
tj_source = ["array.c", "number.c", "object.c", "string.c", "error.c", "parse.c"]
tj_modules = []

def AddModule(name, env, module_list, asm):
    module_path = os.path.join(os.path.join(os.getcwd(), "modules"), name)
    env.Append(CPPPATH = [module_path])
    if asm:
        module_list+=[os.path.join(module_path, name + ".amd64.s")]
    else:
        module_list+=[os.path.join(module_path, name + ".c")]

if (sys.platform == 'darwin' or (sys.platform.startswith('linux') and platform.machine() == 'x86_64')) and not disable_asm:
    if (sys.platform == 'darwin'):
        environment.Append(ASFLAGS = " -f macho64 -m amd64")
    else:
        environment.Append(ASFLAGS = " -f elf64")
    tj_source += ["value.amd64.s", "value_utils.c"]
    environment.Append(CPPDEFINES = "NDEBUG=1")
    AddModule("find_quote", environment, tj_modules, True)
    AddModule("literal_atom", environment, tj_modules, True)
    AddModule("whitespace", environment, tj_modules, True)
    AddModule("number_literal", environment, tj_modules, False)
else:
    tj_source += ["value.c"]
    AddModule("find_quote", environment, tj_modules, False)
    AddModule("literal_atom", environment, tj_modules, False)
    AddModule("whitespace", environment, tj_modules, False)
    AddModule("number_literal", environment, tj_modules, False)

environment.Append(CCFLAGS = " -Os -ansi ")

turbojson = environment.Library("turbojson", tj_source + tj_modules)

test = environment.Program("test", ["test.c"], LIBS = [turbojson])

Return("turbojson")
