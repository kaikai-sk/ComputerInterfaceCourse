###############################################################################
# Makefile for project 
###############################################################################

## General options
PROJECT = 
MCU = 8086
COMPILER = "Digital Mars C"
TARGET = Debug
SHELL = c:/WINDOWS/system32/cmd.exe

## Tools general options
ASMFLAGS=/c
CCFLAGS=-g -ms -0 -c
LDFLAGS=/CO /NODEF:SDS

## Processing Tools
CC=dmc.exe
ASM=ml.exe
LD=optlink.exe
#  C:/Users/dell/Desktop/单凯课程设计/8086/Debug/Debug.exe: TOOL=LD
#     C:/Users/dell/Desktop/单凯课程设计/8086/Debug/main.obj: TOOL=CC
#        C:/Users/dell/Desktop/单凯课程设计/8086/main.c
#     C:/Users/dell/Desktop/单凯课程设计/8086/Debug/rtl.obj: TOOL=ASM
#        C:/Users/dell/Desktop/单凯课程设计/8086/rtl.asm

# Build tree:
all:	Debug

Debug:	Debug.exe

Debug.exe:	main.obj rtl.obj 
	$(LD) $(LDFLAGS) main.obj+rtl.obj,Debug.exe

main.obj:	../main.c 
	$(CC) $(CCFLAGS) -omain.obj ../main.c

rtl.obj:	../rtl.asm 
	$(ASM) $(ASMFLAGS) ../rtl.asm

# tidy - delete all temporary files which are not involved in the target generation
tidy:

# cleanup - delete all generated files
clean:	tidy
	rm -rf Debug.exe
	rm -rf main.obj
	rm -rf rtl.obj
