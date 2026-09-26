// test funcs
#include "hello_freertos_test.h"
#include "unity_config.h"

// for mac os sleep:
#include <unistd.h>

// not being used
void setUp(void) {}

// not being used
void tearDown(void) {}

void test_GPIO(void)
{
    bool gpio = check_GPIO();
    TEST_ASSERT_TRUE_MESSAGE(gpio, "GPIO on/off: Failed.");
}
void test_task_count(void)
{
    bool task_created = get_task_count();
    TEST_ASSERT_TRUE_MESSAGE(task_created, "GPIO on/off: Failed.");
}
void test_main(void)
{
    char test_str1 = 't';
    char test_str2 = 'A';
    char test_str3 = '$';
    TEST_ASSERT_TRUE_MESSAGE(main_test(test_str1) == 'T', "Char to upper: Failed");
    TEST_ASSERT_TRUE_MESSAGE(main_test(test_str2) == 'a', "Char to Lower: Failed");
    TEST_ASSERT_TRUE_MESSAGE(main_test(test_str3) == '$', "Special Character: Failed");
}

void test_toggle(void)
{
    // Test when count % 11 is 0 (Evaluates to False -> Does NOT toggle)
    bool state1 = false;
    TEST_ASSERT_FALSE_MESSAGE(toggle(state1, 0, true), "Count 0 should NOT toggle the state");

    // Test when count % 11 is non-zero (Evaluates to True -> DOES toggle)
    // 1 % 11 = 1 (True), so state1 (false) will become true
    bool state2 = false;
    TEST_ASSERT_TRUE_MESSAGE(toggle(state2, 1, true), "Count 1 SHOULD toggle the state");
}


void main_task (__unused void *params)
{
    sleep_ms(5000); // Give time for TTY to attach.
    printf("Start tests\n");
    UNITY_BEGIN();
    RUN_TEST(test_toggle);
    RUN_TEST(test_main);
    sleep_ms(5000);
    UNITY_END();
}

int main(void)
{
    // can only be used on a pico board
    stdio_init_all();


    const char *rtos_name;
    rtos_name = "FreeRTOS";
    // create and start main a test task:
    TaskHandle_t task;
    xTaskCreate(main_task, "MainTestThread",
                MAIN_TASK_STACK_SIZE, NULL, MAIN_TASK_PRIORITY, &task);
    vTaskStartScheduler();
    return 0;
}
