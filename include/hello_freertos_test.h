#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#define MAIN_TASK_PRIORITY      ( tskIDLE_PRIORITY + 1UL )
#define BLINK_TASK_PRIORITY     ( tskIDLE_PRIORITY + 2UL )
#define MAIN_TASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define BLINK_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

#include "pico/stdlib.h"
#include "pico/multicore.h" // for task
#include "pico/cyw43_arch.h" // for LED

// This example uses a common include to avoid repetition
#include "FreeRTOSConfig_examples_common.h"

#include <stdio.h>
#include <stdbool.h>

#include "FreeRTOS.h"


#include <unity.h>
#include "stack_macros.h"

#include "task.h"
// #include <pico_w.h>

#include <stdint.h>
// test funcs



//#include "unity_config.h"
// #include "stdint.h"

/** Testing Toggle:
 * Input:
 *      - on: prev flag (on status)
 *      - count: keeps track of loop interation (from other blink task)
 *      - PICO_OK: dependency test
 *  Ouput: toggled version
 */
bool toggle (bool on, int count, bool status);

/** Testing Main:
 * Input:
 *      - on: prev flag (on status)
 *      - count: keeps track of loop interation (from other blink task)
 *      - PICO_OK: dependency test
 *  Ouput: toggled version
 */
char main_test (char c);

// -------- (TEST) TASK COUNT ----------
bool get_task_count ();
// -------- (TEST) GPIO SET----------
bool check_GPIO ();

#endif