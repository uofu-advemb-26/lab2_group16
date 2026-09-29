#include <hello_freertos_helpers.h>
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"

void multi_blink(int *count, bool *on, int frequency, TickType_t delay) {
    if (*count % frequency == 0) {
        *on = !*on;
    }

    (*count)++;

    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, *on);
    vTaskDelay(delay);
}


//This function takes a character, changes nothing if it is not a letter, swaps the uppercase/lowercase if it is a letter, and outputs it to std output
char swap_case(char c) {
        if (c <= 'z' && c >= 'a') return(c - 32);
        else if (c >= 'A' && c <= 'Z') return(c + 32);
        else return(c);
}