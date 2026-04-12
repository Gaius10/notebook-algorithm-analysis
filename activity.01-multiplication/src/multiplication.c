#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../lib/multiplication.h"

natural_t sum(
    const natural_t num1,
    const natural_t num2
) {
    unsigned len1 = natural_get_length(num1);
    unsigned len2 = natural_get_length(num2);
    unsigned total_len = len1 + len2;

    char* sum_buffer = malloc(sizeof(char) * total_len);

    for (unsigned i = 0; i < total_len; i++) {
        sum_buffer[i] = '0';
    }

    for (unsigned i = 0; i < len1; i++) {
        sum_buffer[total_len - i - 1] += natural_get_digit(num1, len1 - 1 - i);
    }

    for (unsigned i = 0; i < len2; i++) {
        sum_buffer[total_len - i - 1] += natural_get_digit(num2, len2 - 1 - i);

        if (sum_buffer[total_len - i - 1] > '9') {
            sum_buffer[total_len - i - 1] -= 10;
            sum_buffer[total_len - i - 2]++;
        }
    }

    return natural_create_from_chars(sum_buffer, total_len);
}

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
    unsigned length1 = natural_get_length(num1);
    unsigned length2 = natural_get_length(num2);

    if (length1 < 2 || length2 < 2) {
        return multiply(num1, num2);
    }

    natural_t p = natural_get_slice(num1, 0, length1 / 2);
    natural_t q = natural_get_slice(num1, length1 / 2, length1);
    natural_t r = natural_get_slice(num2, 0, length2 / 2);
    natural_t s = natural_get_slice(num2, length2 / 2, length2);

    natural_t mult1 = karatsuba_multiply(p, r);
    natural_t mult2 = karatsuba_multiply(p, s);
    natural_t mult3 = karatsuba_multiply(q, r);
    natural_t mult4 = karatsuba_multiply(q, s);

    unsigned number_1_power = natural_get_length(num1) - natural_get_length(p);
    unsigned number_2_power = natural_get_length(num2) - natural_get_length(r);

    natural_t result = sum(
        sum(
            natural_e(mult1, number_1_power + number_2_power),
            natural_e(mult2, number_1_power)
        ),
        sum(
            natural_e(mult3, number_2_power),
            mult4
        )
    );

    natural_destroy(&p);
    natural_destroy(&q);
    natural_destroy(&r);
    natural_destroy(&s);
    natural_destroy(&mult1);
    natural_destroy(&mult2);
    natural_destroy(&mult3);
    natural_destroy(&mult4);

    return result;
}
