/*------------------------------------------------------------------------------------------------------------------------------
//
//                                            __  __ _             _   _     _____    
//                                           |  \/  (_)_ __       | | | |   |_   _|__ 
//                                           | |\/| | | '_ \ _____| | | |_____| |/ _ \
//                                           | |  | | | | | |_____| |_| |_____| |  __/
//                                           |_|  |_|_|_| |_|      \___/      |_|\___|
//                                                    Minimal Unit Test support
//
// File:      cppTest.cpp
//
// Author:    Silvano Catinella
//
// Description
//	It is a simple unit-test example in C++
//
// Editor parameters: 128 cols, ts=6
------------------------------------------------------------------------------------------------------------------------------*/
#include <minute.hpp>

TEST (myFunction1, testType1) {
	if (fileArgumentsDb_get("verbose", NULL))
		cout << "This is a verbose log.... bla bla bla" << endl;
	ASSERT_EQ(1, 1);
	ASSERT_EQ(1, 1);
}
TEST (myFunction1, testType2) {
	if (fileArgumentsDb_get("verbose", NULL))
		cout << "This is a verbose log.... bla bla bla" << endl;
	ASSERT_EQ(1, 1);
	ASSERT_EQ(1, 1);
}
TEST (myFunction2, testType1) {
	if (fileArgumentsDb_get("verbose", NULL))
		cout << "This is a verbose log.... bla bla bla" << endl;
	ASSERT_EQ(1, 1);
	ASSERT_EQ(1, 1);
}
TEST (myFunction2, testType2) {
	if (fileArgumentsDb_get("verbose", NULL))
		cout << "This is a verbose log.... bla bla bla" << endl;
	ASSERT_EQ(1, 1);
}

#include "./cppTest_main.cpp"
