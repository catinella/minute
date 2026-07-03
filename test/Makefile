#-------------------------------------------------------------------------------------------------------------------------------
#
#                                            __  __ _             _   _     _____    
#                                           |  \/  (_)_ __       | | | |   |_   _|__ 
#                                           | |\/| | | '_ \ _____| | | |_____| |/ _ \
#                                           | |  | | | | | |_____| |_| |_____| |  __/
#                                           |_|  |_|_|_| |_|      \___/      |_|\___|
#                                                    Minimal Unit Test support
#
# File:      Makefile
#
# Author:    Silvano Catinella
#
# Description:
#	This makefile is a useful example on how to build the code of your tests.
#		1) before to compile the test file code, you need to generate the main() function using the 
#		   minute_cCodeGenerator.pl script. Check for the #include<..> line in the file you want to build
#		2) Compile your test-file code with the -I option to find the minute.{h|hpp|..} header file
#		3) Link your testing-code to the proper minute library (eg libMinuteC, libMinuteCPP..)
#	
#	Modifing a templete:
#		It you want to modify a template or adding a new one, consider to clean the old produced files (*main.sgc) before to
#		rebuild the new ones. In fact, all files produced by the code-generator scripts do not depends by their templates
#		and they will be not automatically re-generated.
#		It happens because the script select the correct template considering just the file extension, and specify the
#		template-files here would be a very bad solution. At the end you have just to type "make cleanall"
#
#-------------------------------------------------------------------------------------------------------------------------------
LIBDIR    := $(shell ls -d ../src_[A-Z]*)
LIBOPTS   := $(LIBDIR:%=-L%)
INCOPTS   := $(LIBDIR:%=-I%) 

CC        ?= gcc
CXX       ?= g++
CFLAGS    ?= -Wall -g

codeGen    = ../minute_cCodeGenerator.py

cLibFile   = ../src_C/libMinuteC.a
cppLibFile = ../src_CPP/libMinuteCPP.a

.PHONY:	all libs clean cleanall

all:			libs cTest cppTest

cTest:		cTest.o
			$(CC) -Wall -o $@ $(LIBOPTS) $^ -lMinuteC 

cTest.o:		cTest.c cTest_main.sgc
			$(CC) $(CFLAGS) -std=c99 -c -o $@ -I. $(INCOPTS)  $<

cppTest:		cppTest.o
			$(CXX) -Wall -o $@ $^ $(LIBOPTS) -lMinuteCPP

cppTest.o:		cppTest.cpp cppTest_main.sgc
			$(CXX) $(CFLAGS) -c -o $@ -I. $(INCOPTS)  $<

cTest_main.sgc:	cTest.c
			$(codeGen) --srcFilename=$<  --tgtFilename=$@

cppTest_main.sgc:	cppTest.cpp
			$(codeGen) --srcFilename=$<  --tgtFilename=$@

libs:			
			@for dir in $(LIBDIR); do make --directory=$$dir GDB=1; done

clean:
			@rm -fv *.o *.sgc

cleanall:		clean
			@for dir in $(LIBDIR); do make --directory=$$dir cleanall; done
			@rm -fv cppTest cTest
