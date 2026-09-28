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

void led_blink(bool);
void my_put_char(char);
void multi_blink(int);

int count = 0;
bool on = false;
const int delay = 500; //delay: how long should multi_blink wait in between calls?
int frequency = 11; //frequency: how many times do I have to run multi_blink for the led to toggle?

#define MAIN_TASK_PRIORITY      ( tskIDLE_PRIORITY + 1UL )
#define BLINK_TASK_PRIORITY     ( tskIDLE_PRIORITY + 2UL )
#define MAIN_TASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define BLINK_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

// Task that toggles the LED once every 500 ticks.
void blink_task(__unused void *params) {
    hard_assert(cyw43_arch_init() == PICO_OK);
    while (true) {
        multi_blink(frequency);
    }
}

// Creates a task that runs blink_task. While loop reads for user input and outputs
// upper-case letter if input is lower-case, and vice-versa.
void main_task(__unused void *params) {
    xTaskCreate(blink_task, "BlinkThread",
                BLINK_TASK_STACK_SIZE, NULL, BLINK_TASK_PRIORITY, NULL);
    char c;
    //c is all characters put into standard input
    while(c = getchar()) {
        //this will output transformed characters to standard output (see function)
        my_put_char(c); 
    }
}

// Initializes stdio devices. Creates a task for main_task. Starts scheduler that
// hands control of tasks to the kernel, which runs the tasks.
int main( void )
{
    stdio_init_all();
    const char *rtos_name;
    rtos_name = "FreeRTOS";
    TaskHandle_t task;
    xTaskCreate(main_task, "MainThread",
                MAIN_TASK_STACK_SIZE, NULL, MAIN_TASK_PRIORITY, &task);
    // Hands kernel control of tasks, which starts them.
    vTaskStartScheduler();
    return 0;
}

void led_blink(bool on) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, on);
}

void multi_blink(int frequency) {
    led_blink(on);
    if (count++ % frequency) on = !on;
    vTaskDelay(delay);
}


//This function takes a character, changes nothing if it is not a letter, swaps the uppercase/lowercase if it is a letter, and outputs it to std output
void my_put_char(char c) {
        if (c <= 'z' && c >= 'a') putchar(c - 32);
        else if (c >= 'A' && c <= 'Z') putchar(c + 32);
        else putchar(c);
}