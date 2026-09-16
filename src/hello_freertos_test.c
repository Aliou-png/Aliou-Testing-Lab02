/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>

// #include "pico/stdlib.h"
#include "pico/multicore.h" // for task
// #include "pico/cyw43_arch.h" // for LED

// test funcs
#include "hello_freertos_test.h"


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
