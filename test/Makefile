
codeGen = ../minute_cCodeGenerator.pl
libPath = ../src_C
libFile = libMinuteC.a

all:			$(libPath)/$(libFile) test

test:			test.o
			gcc -Wall -o $@ -L$(libPath) $^ -lMinuteC 

test.o:		test.c test_main.c
			gcc -Wall -g -c -o $@ -I. -I$(libPath)  $<

test_main.c:	test.c
			$(codeGen) --srcFilename=$<  --tgtFilename=$@

$(libPath)/%:
			make --directory=$(libPath) GDB=1

clean:
			rm -fv *.o

cleanall:		clean
			rm -fv test test_main.c
			make --directory=$(libPath) cleanall
