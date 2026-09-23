// test funcs
#include "hello_freertos_test.h"
#include "unity_config.h"


#define MAIN_TASK_PRIORITY      ( tskIDLE_PRIORITY + 1UL )
#define BLINK_TASK_PRIORITY     ( tskIDLE_PRIORITY + 2UL )
#define MAIN_TASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define BLINK_TASK_STACK_SIZE configMINIMAL_STACK_SIZE


void setUp(void) {}

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
    bool on = false;
    TEST_ASSERT_TRUE_MESSAGE(toggle(on, 0, (bool)true) == true, "Test Toggle on: Passed");
    on = true;
    TEST_ASSERT_TRUE_MESSAGE(toggle(on, 0, true) == false, "Test Toggle off: Passed");
}

int main_task (void)
{
    sleep_ms(5000); // Give time for TTY to attach.
    printf("Start tests\n");
    UNITY_BEGIN();
    RUN_TEST(test_toggle);
    RUN_TEST(test_main);
    sleep_ms(5000);
    UNITY_END();
}

void main()
{
        // initialize everything
    stdio_init_all();

    const char *rtos_name;
    rtos_name = "FreeRTOS";
    // create and start main task:
    TaskHandle_t task;
    xTaskCreate(main_task, "MainTestThread",
                MAIN_TASK_STACK_SIZE, NULL, MAIN_TASK_PRIORITY, &task);
    vTaskStartScheduler();
    return 0;
}
