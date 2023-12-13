#include <stdio.h>
#include <assert.h>
#include <check.h>
#include "buf.h"

START_TEST(test_dummy) {
 	assert(buf_grow1 != NULL);
	return 0;
}
END_TEST

int main(int argc, char** argv) {
	Suite *suite = suite_create("Dummy");
	TCase *testcase = tcase_create("Dummy");
	SRunner *runner = srunner_create(suite);
	int ret;

	suite_add_tcase(suite, testcase);
	tcase_add_test(testcase, test_dummy);
	srunner_run_all(runner, CK_ENV);
	ret = srunner_ntests_failed(runner);
	srunner_free(runner);
	return ret != 0;
}
