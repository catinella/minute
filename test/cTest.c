/*------------------------------------------------------------------------------------------------------------------------------
//
//                                            __  __ _             _   _     _____    
//                                           |  \/  (_)_ __       | | | |   |_   _|__ 
//                                           | |\/| | | '_ \ _____| | | |_____| |/ _ \
//                                           | |  | | | | | |_____| |_| |_____| |  __/
//                                           |_|  |_|_|_| |_|      \___/      |_|\___|
//                                                    Minimal Unit Test support
//
// File:      cTest.c
//
// Author:    Silvano Catinella
//
// Description
//	It is a simple unit-test example in C
//
// Editor parameters: 128 cols, ts=6
------------------------------------------------------------------------------------------------------------------------------*/
#include <minute.h>

TEST (myFunction1, testType1) {
	if (fileArgumentsDb_get("verbose", NULL))
		printf("This is a verbose log.... bla bla bla\n");
	ASSERT_EQ(1, 1);
	ASSERT_EQ(1, 1);
}
TEST (myFunction1, testType2) {
	if (fileArgumentsDb_get("verbose", NULL))
		printf("This is a verbose log.... bla bla bla\n");
	ASSERT_EQ(1, 1);
	WMASSERT_EQ(1, 1, "Test 1024C");
}
TEST (myFunction2, testType1) {
	if (fileArgumentsDb_get("verbose", NULL))
		printf("This is a verbose log.... bla bla bla\n");
	ASSERT_EQ(1, 1);
	WMASSERT_EQ(1, 1, "Test 1048C");
}
TEST (myFunction2, testType2) {
	if (fileArgumentsDb_get("verbose", NULL))
		printf("This is a verbose log.... bla bla bla\n");
	ASSERT_EQ(1, 1);
}

#include "./cTest_main.sgc"
