#include "minunit.h"

#include "../pwm_blaster.inc"

void test_setup(void)
{
}

void test_teardown(void)
{
}

MU_TEST(test_check)
{
	mu_check(1);
}

MU_TEST_SUITE(test_suite)
{
	MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
	MU_RUN_TEST(test_check);
}

int main(int argc, char **argv)
{
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
