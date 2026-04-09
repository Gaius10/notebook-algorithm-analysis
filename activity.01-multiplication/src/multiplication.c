#include <string.h>
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
    number->digits = malloc(sizeof(char) * length);

    number->length = length;
    strncpy(number->digits, digits, length);

    unsigned zeros = 0;
    while (number->digits[zeros] == '0' && zeros < number->length) {
        zeros++;
    }

    if (zeros == number->length) {
        number->digits[0] = '0';
        number->length = 1;
    } else {
        for (unsigned i = 0; i < number->length - zeros; i++) {
            number->digits[i] = number->digits[i + zeros];
        }
        number->length -= zeros;
        number->digits = realloc(number->digits, number->length);
    }

    return number;
}

void natural_print(const natural_t number) {
    if (number == NULL) {
        printf("NULL");
        return;
    }

    for (unsigned i = 0; i < number->length; i++) {
        printf("%c", number->digits[i]);
    }
}

void natural_destroy(natural_t* number) {
    if (number == NULL || *number == NULL) {
        return;
    }

    free((*number)->digits);
    free(*number);
    number = NULL;
}

natural_t multiply(
    const natural_t num1,
    const natural_t num2
) {
    unsigned result_length = num1->length + num2->length;
    unsigned* result_buffer = malloc(sizeof(unsigned) * (result_length));

    for (unsigned i = 0; i < result_length; i++) {
        result_buffer[i] = 0;
    }

    for (unsigned i = num2->length; i > 0; i--) {
        unsigned carry = 0;
        for (unsigned j = num1->length; j > 0; j--) {
            unsigned multiplication_result = (num2->digits[i-1] - '0') * (num1->digits[j-1] - '0');
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

    natural_t number = _natural_create_from_char(result_digits, result_length);

    free(result_digits);
    free(result_buffer);

    return number;
}
