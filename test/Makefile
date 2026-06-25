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
#-------------------------------------------------------------------------------------------------------------------------------
LIBDIR    := $(shell ls -d ../src_[A-Z]*)
LIBOPTS   := $(LIBDIR:%=-L%)
INCOPTS   := $(LIBDIR:%=-I%) 

codeGen    = ../minute_cCodeGenerator.pl

cLibFile   = ../src_C/libMinuteC.a
cppLibFile = ../src_CPP/libMinuteCPP.a

.PHONY:	all libs clean cleanall

all:			libs cTest cppTest

cTest:		cTest.o
			gcc -Wall -o $@ $(LIBOPTS) $^ -lMinuteC 

cTest.o:		cTest.c cTest_main.c
			gcc -Wall -g -c -o $@ -I. -I$(INCOPTS)  $<

cppTest:		cppTest.o
			g++ -Wall -o $@ $(LIBOPTS) $^ -lMinuteCPP

cppTest.o:		cppTest.cpp cppTest_main.cpp
			g++ -Wall -g -c -o $@ -I. -I$(INCOPTS)  $<

cTest_main.c:	cTest.c
			$(codeGen) --srcFilename=$<  --tgtFilename=$@

cppTest_main.cpp:	cppTest.cpp
			$(codeGen) --srcFilename=$<  --tgtFilename=$@

libs:			
			@for dir in $(LIBDIR); do make --directory=$$dir GDB=1; done

clean:
			@rm -fv *.o

cleanall:		clean
			@for dir in $(LIBDIR); do make --directory=$$dir cleanall; done
			@rm -fv *Test *Test_main.*
