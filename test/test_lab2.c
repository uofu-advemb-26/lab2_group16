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

void setUp() {}

void tearDown() {}

void test_multi_blinks()
{

}

void test_swap_case_()
{
    char test_char = 'a';
    char expected_char = 'A';
    char result_char;
    result_char = swap_case(test_char);
    TEST_ASSERT_TRUE_MESSAGE(expected_char == result_char, "Successfully swaps from lowercase to uppercase");
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
    while (1) {
        sleep_ms(5000); // Give time for TTY to attach.
        printf("Start tests\n");
        UNITY_BEGIN();
        // multi_blink() tests
        RUN_TEST(test_multi_blinks);

        // swap_case() tests
        RUN_TEST(test_swap_case_lower);
        RUN_TEST(test_swap_case_upper);
        RUN_TEST(test_swap_case_symbol);
        RUN_TEST(test_swap_case_digit);
        sleep_ms(5000);
        UNITY_END();
    }
}