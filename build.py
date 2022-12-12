from os import *
from os.path import *
import shutil
import platform
import sys

if platform.system() == "Windows":
    system("cls")
elif platform.system() == "Darwin":
    system("clear")
elif platform.system() == "Linux":
    system("clear")
else:
    print("couldn't determine executor os!")
    sys.exit(1)

print("building saturdayOS...")

source = "src/"
gcc = "i686-elf"
gccargs = " -g -ffreestanding -Wall -Wextra -mgeneral-regs-only"
qemu = "i386"
qemuargs = "-machine type=pc-i440fx-3.1"
output = "bin/kernel.bin"

debug = False

try: shutil.rmtree("obj"); 
except: pass
try: shutil.rmtree("bin"); 
except: pass
try: mkdir("obj"); 
except: pass
try: mkdir("bin"); 
except: pass

asmobjects = ""
cobjects = ""

def builddir(dir):
    global asmobjects
    global cobjects

    print("building files from dir \"" + dir + "\"...")

    onlyfiles = [f for f in listdir(getcwd() + "/" + source + dir) if isfile(join(getcwd() + "/" + source + dir, f))]

    for x in onlyfiles:
        if x.endswith(".cpp"):
            print("    compiling file " + x + " ...", end = '')
            cobjects += "obj/" + x.replace(".cpp", ".o ")
            cmd = gcc + "-g++ -c " + source + dir + x + " -o " + "obj/" + x.replace(".cpp", ".o") + gccargs
            if debug: print(cmd)
            system(cmd)
            print(" done!")
        elif x.endswith(".s"):
            print("    compiling file " + x + " ...", end = '')
            asmobjects += "obj/" + x.replace(".s", ".o ")
            cmd = gcc + "-as " + source + dir + x + " -o " + "obj/" + x.replace(".s", ".o")
            if debug: print(cmd)
            system(cmd)
            print(" done!")

    print("compiled " + str(len(onlyfiles)) + " files in dir \"" + dir + "\"")

builddir("./")

print("linking kernel...", end = '')
cmd = gcc + "-gcc -T linker.ld -o " + output + " -ffreestanding -nostdlib -O2 " + asmobjects + cobjects + " -lgcc"
if debug: print(cmd)
system(cmd)
print(" done!")

print("starting qemu...", end = '')
cmd = "qemu-system-" + qemu + " -kernel " + output + " " + qemuargs
if debug: print(cmd)
system(cmd)
print(" done!")