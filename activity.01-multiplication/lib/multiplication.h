
#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

// This file contains the declaration of the multiplication function and the number type.
typedef struct natural* natural_t;

// Management of naturals...
natural_t natural_create(unsigned long long n); // Alias for natural_create_from_long
natural_t natural_create_from_long(unsigned long long n);
natural_t natural_create_from_chars(const char* chars, unsigned length);

void natural_print(const natural_t number);
void natural_destroy(natural_t* number);

unsigned natural_get_length(const natural_t number);
unsigned natural_get_digit(const natural_t number, unsigned int index);

natural_t multiply(const natural_t num1, const natural_t num2);
natural_t karatsuba_multiply(const natural_t num1, const natural_t num2);

#endif

