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
#-------------------------------------------------------------------------------------------------------------------------------
alib = libMinuteCPP.a

GDB  ?= 0
CC   ?= g++

ifeq ($(GDB), 0)
	CFLAGS = -Wall -o0
else
	CFLAGS = -Wall -g
endif

$(alib):	minute.o
		ar rcs $@ $^

minute.o:	minute.cpp minute.hpp
		$(CC) $(CFLAGS) -c -I. -o $@ $<

clean:
		rm -fv *.o

cleanall:	clean
		rm -fv $(alib)
