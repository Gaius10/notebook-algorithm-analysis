
#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

// This file contains the declaration of the multiplication function and the number type.
typedef struct natural* natural_t;

// Management of naturals...
natural_t natural_create(unsigned long long n);
void natural_print(const natural_t number);
void natural_destroy(natural_t* number);

natural_t multiplication(const natural_t num1, const natural_t num2);

#endif

