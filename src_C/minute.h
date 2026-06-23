/*------------------------------------------------------------------------------------------------------------------------------
//
//                                            __  __ _             _   _     _____    
//                                           |  \/  (_)_ __       | | | |   |_   _|__ 
//                                           | |\/| | | '_ \ _____| | | |_____| |/ _ \
//                                           | |  | | | | | |_____| |_| |_____| |  __/
//                                           |_|  |_|_|_| |_|      \___/      |_|\___|
//                                                    Minimal Unit Test support
//
// File:      minute.h
//
// Author:    Silvano Catinella
//
// Description
//
//
// Editor parameters: 128 cols, ts=6
------------------------------------------------------------------------------------------------------------------------------*/

#ifndef __MINUTE__
#define __MINUTE__

#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <getopt.h>

#define OKSYMB  "[\033[1;32m  OK  \e[0m]"
#define ERRSYMB "[\033[1;31mERROR!\e[0m]"

#define ASSERT_EQ(x, y) \
	if (x == y) printf("%s", OKSYMB); else  printf("%s", ERRSYMB); \
	printf(" %s(%d)\n", __func__, __LINE__);

#define ASSERT_NE(x, y) \
	if (x != y) printf("%s", OKSYMB); else  printf("%s", ERRSYMB); \
	printf(" %s(%d)\n", __func__, __LINE__);

#define ASSERT_TRUE(x) \
	if (x) printf("%s", OKSYMB); else  printf("%s", ERRSYMB); \
	printf(" %s(%d)\n", __func__, __LINE__);

#define TEST(x, y)  \
	void x##__##y() 


bool fileArgumentsDb_set (const char *arg_a, const char *value);
bool fileArgumentsDb_get (const char *arg_a, char *value);

#endif
