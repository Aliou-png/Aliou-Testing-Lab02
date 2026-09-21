#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

// This example uses a common include to avoid repetition
#include "FreeRTOSConfig_examples_common.h"

#include <stdio.h>

#include "FreeRTOS.h"

#include "pico/stdlib.h"
#include "pico/multicore.h" // for task
#include "pico/cyw43_arch.h" // for LED

#include "stack_macros.h"

#include "task.h"
// #include <pico_w.h>

#include <stdint.h>
// test funcs

#include <unity.h>

// #include "unity_config.h"
// #include "stdint.h"

/** Testing Toggle:
 * Input:
 *      - on: prev flag (on status)
 *      - count: keeps track of loop interation (from other blink task)
 *      - PICO_OK: dependency test
 *  Ouput: toggled version
 */
bool toggle (bool on, int count, bool PICO_OK);

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