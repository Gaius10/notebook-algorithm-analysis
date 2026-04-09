#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../lib/multiplication.h"

struct natural {
    char* digits;
    unsigned length;
};

natural_t natural_create_from_long(unsigned long long n) {
    natural_t number;

    number = malloc(sizeof(struct natural));

    number->digits = malloc(20); // Maximum length for unsigned long long is 20 digits
    number->length = snprintf(number->digits, 20, "%llu", n);
    number->digits = realloc(number->digits, number->length);

    return number;
}

natural_t natural_create(unsigned long long n) {
    return natural_create_from_long(n);
}

natural_t natural_create_from_chars(const char* chars, unsigned length) {
    natural_t number;

    for (unsigned i = 0; i < length; i++) {
        if (chars[i] < '0' || chars[i] > '9') {
            printf("Invalid character '%c' in input string. Only digits are allowed.\n", chars[i]);
            return NULL;
        }
    }

    number = malloc(sizeof(struct natural));
    number->digits = malloc(sizeof(char) * length);

    number->length = length;
    strncpy(number->digits, chars, length);

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

unsigned natural_get_length(const natural_t number) {
    return number->length;
}

unsigned natural_get_digit(const natural_t number, unsigned int index) {
    if (index >= natural_get_length(number)) {
        return 0;
    }

    return number->digits[index] - '0';
}
