
alib = libMinuteC.a

$(alib):	minute.o
		ar rcs $@ $^

minute.o:	minute.c minute.h
		gcc -Wall -c -I. -o $@ $<

clean:
		rm -fv *.o

cleanall:	clean
		rm -fv $(alib)
