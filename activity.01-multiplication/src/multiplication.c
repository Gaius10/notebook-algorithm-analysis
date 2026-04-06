#include <stdlib.h>
#include <stdio.h>
#include "../lib/multiplication.h"

struct natural {
    char* digits;
    unsigned length;
};

natural_t _natural_create_from_long(unsigned long long n) {
    natural_t number;

    number = malloc(sizeof(struct natural));

    number->digits = malloc(20);
    number->length = snprintf(number->digits, 20, "%llu", n);
    number->digits = realloc(number->digits, number->length);

    return number;
}

natural_t natural_create(unsigned long long n) {
    return _natural_create_from_long(n);
}

natural_t _natural_create_from_char(char* digits, unsigned length) {
    natural_t number;
    number = malloc(sizeof(struct natural));

    number->length = length;
    number->digits = digits;

    unsigned zeros = 0;
    while (number->digits[zeros] == '0' && zeros < number->length) {
        zeros++;
    }

    if (zeros == number->length) {
        number->digits[0] = '0';
        number->length = 1;
    } else {
        number->digits += zeros;
        number->length -= zeros;
    }

    return number;
}

void natural_destroy(natural_t* number) {
    free((*number)->digits);
    free(*number);
    number = NULL;
}

void multiplication(
    const natural_t num1,
    const natural_t num2,
    natural_t *result
) {
    char* result_buffer = malloc(sizeof(char) * (num1->length + num2->length));
    int carry = 0;
    int multiplication_buffer = 0;

    for (unsigned i = 0; i < num1->length + num2->length; i++) {
        result_buffer[i] = '0';
    }

    for (unsigned i = num2->length - 1; i > 0; i--) {
        for (unsigned j = num1->length - 1; j > 0; j--) {
            multiplication_buffer = (num2->digits[i] - '0') * (num1->digits[j] - '0');
            multiplication_buffer += carry;
            carry = multiplication_buffer / 10;
            result_buffer[i + j + 1] += multiplication_buffer % 10;
        }
    }

    result_buffer[0] += carry;

    *result = _natural_create_from_char(result_buffer, num1->length + num2->length);

    free(result_buffer);
}
