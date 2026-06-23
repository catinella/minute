#include <minute.h>

TEST (myFunction1, testType1) {
	ASSERT_EQ(1, 1);
	ASSERT_EQ(1, 1);
}
TEST (myFunction1, testType2) {
	ASSERT_EQ(1, 1);
	ASSERT_EQ(1, 1);
}
TEST (myFunction2, testType2) {
	ASSERT_EQ(1, 1);
	ASSERT_EQ(1, 1);
}
TEST (myFunction2, testType1) {
	ASSERT_EQ(1, 1);
}

#include "./test_main.c"
