#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../lib/multiplication.h"

natural_t multiply(
    const natural_t num1,
    const natural_t num2
) {
    unsigned result_length = natural_get_length(num1) + natural_get_length(num2);
    unsigned* result_buffer = malloc(sizeof(unsigned) * (result_length));

    for (unsigned i = 0; i < result_length; i++) {
        result_buffer[i] = 0;
    }

    for (unsigned i = natural_get_length(num2); i > 0; i--) {
        unsigned carry = 0;
        for (unsigned j = natural_get_length(num1); j > 0; j--) {
            unsigned multiplication_result = (natural_get_digit(num2, i - 1)) * (natural_get_digit(num1, j - 1));
            multiplication_result += carry;
            multiplication_result += result_buffer[i + j - 1];

            carry = multiplication_result / 10;
            result_buffer[i + j - 1] = multiplication_result % 10;
        }

        result_buffer[i - 1] += carry;
    }

    char* result_digits = malloc(sizeof(char) * result_length);
    for (unsigned i = 0; i < result_length; i++) {
        result_digits[i] = result_buffer[i] + '0';
    }

    natural_t number = natural_create_from_chars(result_digits, result_length);

    free(result_digits);
    free(result_buffer);

    return number;
}

natural_t karatsuba_multiply(
    const natural_t num1,
    const natural_t num2
) {
    // @todo
}
