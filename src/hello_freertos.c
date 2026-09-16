/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"

int count = 0;
bool on = false;

#define MAIN_TASK_PRIORITY      ( tskIDLE_PRIORITY + 1UL )
#define BLINK_TASK_PRIORITY     ( tskIDLE_PRIORITY + 2UL ) // blink task has a higher priority than main task; blink can interrupt main
#define MAIN_TASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define BLINK_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

void blink_task(__unused void *params) {

    // check to make sure GPIO library support is enabled properly
    hard_assert(cyw43_arch_init() == PICO_OK);

    // do this forever unless interrupted
    while (true) {

        // for each loop iteration, toggle the led unless the current loop number is a multiple of 11 (i.e. 11, 22, 33, 44, 55, 66, etc.)
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, on);
        if (count++ % 11) on = !on;
        on = get_new_on(count,on);

        // wait a bit after toggling the led so that the change is visible to the human eye
        vTaskDelay(500);
    }
}

void main_task(__unused void *params) {

    // start a new thread to run the blink test
    xTaskCreate(blink_task, "BlinkThread",
                BLINK_TASK_STACK_SIZE, NULL, BLINK_TASK_PRIORITY, NULL);
    char c;

    // until we receive the NULL character ('\0' acts as a 'stop message')
    while(c = getchar()) {

        // check for a received char over usb. if the char is a lower-case letter a through z, transmit that same letter, but as upper-case
        if (c <= 'z' && c >= 'a') putchar(c - 32);

        // if the received char is an upper-case letter, transmit that same letter, but as lower-case
        else if (c >= 'A' && c <= 'Z') putchar(c + 32);

        // if the character is not a letter, simply transmit that same character without modification
        else putchar(c);
    }
}

int main( void )
{
    stdio_init_all();
    const char *rtos_name;
    rtos_name = "FreeRTOS";
    TaskHandle_t task;
    xTaskCreate(main_task, "MainThread",
                MAIN_TASK_STACK_SIZE, NULL, MAIN_TASK_PRIORITY, &task);
    vTaskStartScheduler();
    return 0;
}
