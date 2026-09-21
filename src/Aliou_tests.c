/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// test funcs
#include "hello_freertos_test.h"


bool LED_tast_start = false;
bool main_task_start = false;

#define MAIN_TASK_PRIORITY      ( tskIDLE_PRIORITY + 1UL )
#define BLINK_TASK_PRIORITY     ( tskIDLE_PRIORITY + 2UL )
#define MAIN_TASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define BLINK_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

// -----------------------------------------------------------------------------------------------
/**
 * A duplication of the RTOS system so that each test can start with a clean slate
 */

// duplicate blink task
void blink_task_test(__unused void *params) {
    int count = 0;
    bool on = false;
    hard_assert(cyw43_arch_init() == PICO_OK);

    while(LED_tast_start){
        while (true) {
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, on);
            if (count++ % 11) on = !on;
            vTaskDelay(500);
        }
    }
    // delete task:
    vTaskDelete(NULL);
}

// duplicate main task
void main_task_test(__unused void *params) {
    char c;
    while(main_task_start){
        // read Std In and return the opposite capitalization
        while(c = getchar()) {
            if (c <= 'z' && c >= 'a') putchar(c - 32);
            else if (c >= 'A' && c <= 'Z') putchar(c + 32);
            else putchar(c);
        }
    }
    vTaskDelete(NULL); // delete task
}

void start_tasks()
{
    // initialize everything
    stdio_init_all();
    const char *rtos_name;
    rtos_name = "FreeRTOS";

    // allow task to run:
    LED_tast_start = true;
    main_task_start = true;

    // create and start main task:
    TaskHandle_t task;
    xTaskCreate(main_task_test, "MainThread",
                MAIN_TASK_STACK_SIZE, NULL, MAIN_TASK_PRIORITY, &task);
    // create and start LED task:
    xTaskCreate(blink_task_test, "BlinkThread",
                BLINK_TASK_STACK_SIZE, NULL, BLINK_TASK_PRIORITY, NULL);

    vTaskStartScheduler();
}

// test toggle: definition
bool toggle (bool on, int count, bool PICO_OK) {

    if (!PICO_OK){ }// failed

    if (count++ % 11) on = !on;
    return on;
}

// test function: definition
char main_test (char c) {

    // assuume these work: xTaskCreate, getchar, putchar
    if (c <= 'z' && c >= 'a')
        return (c - 32);
    else if (c >= 'A' && c <= 'Z')
        return (c + 32);
    else
        return c;
}

/** -------- (TEST) TASK COUNT ----------
 *  Test that 2 task were actually created --> there should only be two
 * */
bool get_task_count () {

    // start the task:
    start_tasks();

    // wait a couple second before checking
    sleep_ms(2000); // 2 second

    // -------- RUN CHECK -------
    UBaseType_t taskCount = uxTaskGetNumberOfTasks();

    // -------- STOP TASKs -------
    LED_tast_start = false;
    main_task_start = false;

    return ((int)taskCount >= 2) ? true: false;
}
/** -------- (TEST) GPIO SET----------
 * the LED is flipped every 11 interation ~ 5.5 second
 *  1) wait for iteration cycle to restart (LED on)
 *  2) check after about 6 second --> should be off
 *  3) wait another 6 second --> should be on
 * */
bool check_GPIO () {

    // start the task:
    start_tasks();
    sleep_ms(2000);

    // -------- RUN CHECK -------
        // Wait for LED to become ON
        while (gpio_get(0) == 0)
        {
            sleep_ms(10);
        }
        // Wait approximately 6 seconds
        sleep_ms(6000);

        // LED should have changed to OFF
        if (gpio_get(0) != 0)
        {
            // -------- STOP TASKs -------
            LED_tast_start = false;
            main_task_start = false;
            return false;
        }
        // Wait another ~6 seconds
        sleep_ms(6000);

        // LED should have changed back to ON
        if (gpio_get(0) == 0)
        {
            // -------- STOP TASKs -------
            LED_tast_start = false;
            main_task_start = false;
            return false;
        }

    // -------- STOP TASKs -------
    LED_tast_start = false;
    main_task_start = false;

    return true;
}

