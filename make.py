#!/usr/bin/env python
from sys import argv
import os

CPP_COMPILER = "g++"
C_COMPILER = "gcc"
def all():
    """Runs every time. Compiles all source code."""
    #does not require root
    if not os.path.exists("./bin"):
        os.mkdir("bin")
    os.system(CPP_COMPILER + " len.cpp -o bin/len -O3")
    os.system(CPP_COMPILER + " mass_append.cpp -o bin/mass_append -O3 -lpthread")
    os.system(CPP_COMPILER + " generateString.cpp -o bin/generateString -O3")
    os.system(CPP_COMPILER + " repeat.cpp -o bin/repeat -lpthread -O3")
    os.system(CPP_COMPILER + " choose.cpp -o bin/choose -O3")
    os.system(CPP_COMPILER + " coinFlip.cpp -o bin/coinFlip -O3")
    os.system(CPP_COMPILER + " readFile.cpp -o bin/readFile -O3")
    os.system(CPP_COMPILER + " convert_unicode.cpp -o bin/convert_unicode -O3")
    os.system(CPP_COMPILER + " fraction.cpp -o bin/fraction -lpthread -O3")
    os.system(CPP_COMPILER + " remove-duplicate-files.cpp -o bin/remove-duplicate-files -lz --std=c++17 -O3")
    os.system(CPP_COMPILER + " remove-targeted-duplicate-files.cpp -o bin/remove-targeted-duplicate-files -lz --std=c++17 -O3")
    os.system(C_COMPILER + " simpleCalc.c -lm -o bin/simpleCalc -O3")
    os.system(C_COMPILER + " convert-char.c -o bin/convert-char -O3")
    os.system(C_COMPILER + " generate-random-chars.c -o bin/generate-random-chars -O3")
    os.system(C_COMPILER + " remove-whitespace.c -o bin/remove-whitespace -O3")
    os.system(C_COMPILER + " crc32sum.c -o bin/crc32sum -lpthread -lz -O3")
    os.system(C_COMPILER + " rdmstr.c -o bin/rdmstr -lm -O3")
def localinstall():
    """Installs to the user's local ~/.local/bin/"""
    #does not require root
    #get working directory
    localpath = os.popen("pwd").read()[0:-1]
    #get home directory
    homepath = os.popen("echo $HOME").read()[0:-1]
    if not os.path.exists(homepath + "/.local"):
        os.mkdir(homepath + "/.local/")
    if not os.path.exists(homepath + "/.local/bin"):
        os.mkdir(homepath+"/.local/bin")
    files = os.listdir("bin")
    for fi in files:
        os.system("ln -sf " + localpath + "/bin/" + fi + " ~/.local/bin/")
def localuninstall():
    """Removes the program files from ~/.local/bin/"""
    files = os.listdir("bin")
    for path in files:
        os.system("rm ~/.local/bin/" + path)
def guis():
    """Compiles the guis. Will eventually add support for things like desktop icons."""
    #requres fltk
    if not os.path.exists("./bin/GUIs"):
        os.mkdir("bin/GUIs")
    os.system(CPP_COMPILER + " GUIs/len.cpp -lfltk -o bin/GUIs/len -O3")
    os.system(CPP_COMPILER + " GUIs/mass_append.cpp -lfltk -lpthread -o bin/GUIs/mass_append -O3")
    os.system(CPP_COMPILER + " GUIs/notification.cpp -lfltk -o bin/GUIs/notification -O3")

def install():
    """Universally installs everything on the system to /usr/bin."""
    #requires root
    os.system("cp -r bin/* /usr/bin/")
def uninstall():
    """Uninstalls the programs from /usr/bin."""
    files = os.listdir("bin")
    for path in files:
        os.system("rm /usr/bin/" + path)
def maninstall():
    #requires root
    os.system("cp -r man /usr/local/")

if len(argv) < 2:
    all()
    exit()

if argv[1] == "-h" or argv[1] == "--help":
    print("Usage: make.py <function>")
    print("example: make.py localinstall")
    exit()
function = ""
if len(argv) >= 2:
    function = argv[1] + "()"
all()
exec(function)
