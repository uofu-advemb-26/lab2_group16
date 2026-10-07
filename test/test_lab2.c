#include <stdio.h>
#include <pico/stdlib.h>
#include <stdint.h>
#include <unity.h>
#include "unity_config.h"
#include "hello_freertos_helpers.h"
#include "FreeRTOS.h"
#include "task.h"
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"
#include "pico/stdio_usb.h"

void setUp() {}

void tearDown() {}

// At count 0, toggle the LED on, then increment the count. This test assures that things are passed through correctly and the led toggles
void test_multi_blink_toggles_at_count_zero(void)
{
    int count = 0;
    bool on = false;

    multi_blink(&count, &on, 5, 10);

    TEST_ASSERT_EQUAL_MESSAGE(1, count, "count increments");
    TEST_ASSERT_EQUAL_MESSAGE(true, on, "led toggles, count = 0");
}

// Before we reach frequency, the led doesn't toggle. the led should only toggle on count 5
void test_multi_blink_does_not_toggle_between_boundaries(void)
{
    int count = 4;
    bool on = true;

    multi_blink(&count, &on, 5, 10);

    TEST_ASSERT_EQUAL_MESSAGE(5, count, "count increments");
    TEST_ASSERT_EQUAL_MESSAGE(true, on, "LED should not toggle before count 5");
}


void test_multi_blink_toggles_at_frequency_boundary(void)
{
    int count = 5;
    bool on = true;

    multi_blink(&count, &on, 5, 10);

    TEST_ASSERT_EQUAL_MESSAGE(6, count, "count increments");
    TEST_ASSERT_EQUAL_MESSAGE(false, on, "LED toggles on count 5");
}

void test_swap_case_lower()
{
    char test_char = 'a';
    char expected_char = 'A';
    char result_char;
    result_char = swap_case(test_char);

    char test_char2 = 'z';
    char expected_char2 = 'Z';
    char result_char2;
    result_char2 = swap_case(test_char2);

    bool test_pass = (expected_char == result_char) && (expected_char2 == result_char2);
    TEST_ASSERT_TRUE_MESSAGE(test_pass, "Successfully swaps from lowercase to uppercase");
}

void test_swap_case_upper()
{
    char test_char = 'A';
    char expected_char = 'a';
    char result_char;
    result_char = swap_case(test_char);

    char test_char2 = 'Z';
    char expected_char2 = 'z';
    char result_char2;
    result_char2 = swap_case(test_char2);

    bool test_pass = (expected_char == result_char) && (expected_char2 == result_char2);
    TEST_ASSERT_TRUE_MESSAGE(test_pass, "Successfully swaps from uppercase to lowercase");
}

void test_swap_case_symbol()
{
    char test_char = '?';
    char expected_char = '?';
    char result_char;
    result_char = swap_case(test_char);

    char test_char2 = '.';
    char expected_char2 = '.';
    char result_char2;
    result_char2 = swap_case(test_char2);

    bool test_pass = (expected_char == result_char) && (expected_char2 == result_char2);
    TEST_ASSERT_TRUE_MESSAGE(test_pass, "Successfully returns the input symbol");
}

void test_swap_case_digit()
{
    char test_char = '0';
    char expected_char = '0';
    char result_char;
    result_char = swap_case(test_char);

    char test_char2 = '9';
    char expected_char2 = '9';
    char result_char2;
    result_char2 = swap_case(test_char2);

    bool test_pass = (expected_char == result_char) && (expected_char2 == result_char2);
    TEST_ASSERT_TRUE_MESSAGE(test_pass, "Successfully returns the input digit");
}

int main (void)
{
    stdio_init_all();

    while (true) {
        printf("Start tests\n");
        UNITY_BEGIN();
        // swap_case() tests
        RUN_TEST(test_swap_case_lower);
        RUN_TEST(test_swap_case_upper);
        RUN_TEST(test_swap_case_symbol);
        RUN_TEST(test_swap_case_digit);
        sleep_ms(2000);
        // multi_blink() tests
        RUN_TEST(test_multi_blink_toggles_at_frequency_boundary);
        RUN_TEST(test_multi_blink_does_not_toggle_between_boundaries);
        RUN_TEST(test_multi_blink_toggles_at_count_zero);
        sleep_ms(5000);

        UNITY_END();
    }
}