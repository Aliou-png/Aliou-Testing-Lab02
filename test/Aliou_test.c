// test funcs
#include "hello_freertos_test.h"





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
void test_main(void)
{
    char test_str1 = 't';
    char test_str2 = 'A';
    char test_str3 = '$';
    TEST_ASSERT_TRUE_MESSAGE(main_test(test_str1) == 'T', "Char to upper: Passed");
    TEST_ASSERT_TRUE_MESSAGE(main_test(test_str2) == 'a', "Char to Lower: Passed");
    TEST_ASSERT_TRUE_MESSAGE(main_test(test_str3) == '$', "Special Character: Passed");
}

void test_toggle(void)
{
    // bool on = false;
    // TEST_ASSERT_TRUE_MESSAGE(toggle(on, 0, (bool)true) == true, "Test Toggle on: Passed");
   //  on = true;
   //  TEST_ASSERT_TRUE_MESSAGE(toggle(on, 0, true) == false, "Test Toggle off: Passed");
}

int main (void)
{
    stdio_init_all();

    sleep_ms(5000); // Give time for TTY to attach.
    printf("Start tests\n");
    UNITY_BEGIN();
    RUN_TEST(test_task_count);
    RUN_TEST(test_GPIO);
   // RUN_TEST(test_toggle);
    RUN_TEST(test_main);
    sleep_ms(5000);
    UNITY_END();

}
