LIBDIR    := $(shell ls -d ../src_[A-Z]*)
LIBOPTS   := $(LIBDIR:%=-L%)
INCOPTS   := $(LIBDIR:%=-I%) 

codeGen    = ../minute_cCodeGenerator.pl

cLibFile   = ../src_C/libMinuteC.a
cppLibFile = ../src_CPP/libMinuteCPP.a

.PHONY:	all libs clean cleanall

all:			libs test

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
			@rm -fv test *Test_main.*
