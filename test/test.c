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
	ASSERT_EQ(1, 1);
}
TEST (myFunction2, testType1) {
	if (fileArgumentsDb_get("verbose", NULL))
		printf("This is a verbose log.... bla bla bla\n");
	ASSERT_EQ(1, 1);
	ASSERT_EQ(1, 1);
}
TEST (myFunction2, testType2) {
	if (fileArgumentsDb_get("verbose", NULL))
		printf("This is a verbose log.... bla bla bla\n");
	ASSERT_EQ(1, 1);
}

#include "./test_main.c"
