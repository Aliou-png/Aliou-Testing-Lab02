#include <stdio.h>
#include <pico/stdlib.h>
#include <stdint.h>
// test funcs
#include "hello_freertos_test.h"
#include <unity.h>
#include "unity_config.h"



void setUp(void) {}

void tearDown(void) {}

void test_task_count()
{
    TEST_ASSERT_TRUE_MESSAGE(get_task_count(),"Tasks Created: Passed.");
}

void test_GPIO(void)
{
    TEST_ASSERT_TRUE_MESSAGE(check_GPIO(), "GPIO on/off: Passed.");
}

int main (void)
{
    stdio_init_all();

    sleep_ms(5000); // Give time for TTY to attach.
    printf("Start tests\n");
    UNITY_BEGIN();
    RUN_TEST(test_task_count);
    RUN_TEST(test_GPIO);
    sleep_ms(5000);
    UNITY_END();

}
