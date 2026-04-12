
#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#include <stdint.h>
#include <stdbool.h>

// This file contains the declaration of the multiplication function and the number type.
typedef struct natural* natural_t;

// Management of naturals...
natural_t natural_create(unsigned long long n); // Alias for natural_create_from_long
natural_t natural_create_from_long(unsigned long long n);
natural_t natural_create_from_chars(const char* chars, unsigned length);

void natural_print(const natural_t number);
void natural_destroy(natural_t* number);

unsigned natural_get_length(const natural_t number);
uint8_t natural_get_digit(const natural_t number, unsigned int index);
natural_t natural_get_slice(const natural_t number, unsigned start, unsigned end);
natural_t natural_e(const natural_t number, unsigned power_of_ten);
bool natural_is_equal(const natural_t num1, const natural_t num2);

natural_t sum(const natural_t num1, const natural_t num2);
natural_t multiply(const natural_t num1, const natural_t num2);
natural_t karatsuba_multiply(const natural_t num1, const natural_t num2);

#endif

