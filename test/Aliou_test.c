
#define configUSE_TRACE_FACILITY                  1
#define configUSE_STATS_FORMATTING_FUNCTIONS      1
#define configSTATS_BUFFER_MAX_LENGTH             400


// test funcs
#include "hello_freertos_test.h"
#include "unity_config.h"

// for mac os sleep:
#include <unistd.h>

volatile bool LED_tast_start = false;
volatile bool main_task_start = false;

// not being used
void setUp(void) {

    // make sure the task are not running on the other core
    LED_tast_start = false;
    main_task_start = false;

    // IMPORTANT: need a hardware sleep
    sleep_ms(600);
}

// not being used
void tearDown(void) {
    // SAME thing make sure tasks terminate
    // make sure the task are not running on the other core
    LED_tast_start = false;
    main_task_start = false;

    // IMPORTANT: need a hardware sleep
    sleep_ms(600);
}

void test_GPIO(void)
{
    bool gpio = check_GPIO();
    TEST_ASSERT_TRUE_MESSAGE(gpio, "GPIO on/off: Failed.");
}
void test_task_count(void)
{
    bool task_created = get_task_count();
    TEST_ASSERT_TRUE_MESSAGE(task_created, "Number of Tasked Created: Failed.");
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
    sleep_ms(5000); // Give time for TTY to attach
    printf("Start tests\n");
    // call this once
    hard_assert(cyw43_arch_init() == PICO_OK);

    UNITY_BEGIN();
    RUN_TEST(test_toggle);
    RUN_TEST(test_main);
    RUN_TEST(test_GPIO);
    RUN_TEST(test_task_count);
    sleep_ms(5000);
    // safly kill
    cyw43_arch_deinit();
    UNITY_END();

    printf("Tests complete. System idling safely. Press Ctrl+A then K to exit screen.\n");

    // FIX: Trap the task here so FreeRTOS never attempts to drop to a hardware sleep state
    for (;;) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main(void)
{
    // can only be used on a pico board
    stdio_init_all();

    // NEW FIX: Force the Pico to pause here until you open the 'screen' command on your Mac
    while (!stdio_usb_connected()) {
        sleep_ms(10); // Check every 10 milliseconds
    }

    printf("terminal screen connected.");

    const char *rtos_name;
    rtos_name = "FreeRTOS";
    // create and start main a test task:
    TaskHandle_t task;
    xTaskCreate(main_task, "MainTestThread",
                MAIN_TASK_STACK_SIZE, NULL, MAIN_TASK_PRIORITY, &task);
    vTaskStartScheduler();
    return 0;
}
