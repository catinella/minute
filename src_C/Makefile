
alib = libMinuteC.a

GDB  ?= 0

ifeq ($(GDB), 0)
	CFLAGS = -Wall -o0
else
	CFLAGS = -Wall -g
endif

$(alib):	minute.o
		ar rcs $@ $^

minute.o:	minute.c minute.h
		$(CC) $(CFLAGS) -c -I. -o $@ $<

clean:
		rm -fv *.o

cleanall:	clean
		rm -fv $(alib)
