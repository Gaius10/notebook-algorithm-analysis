#include <stdio.h>
#include "../lib/multiplication.h"

void print_multiplication(natural_t num1, natural_t num2, natural_t result);

int main() {
    natural_t num1 = natural_create(22222222);
    natural_t num2 = natural_create(25);
    natural_t num3 = natural_create(123456789);

    natural_t result1 = NULL;
    natural_t result2 = NULL;
    natural_t result3 = NULL;
    natural_t result4 = NULL;

    result1 = multiply(num1, num2);
    result2 = multiply(num1, num3);
    result3 = multiply(num2, num3);
    result4 = multiply(num1, num1);

    print_multiplication(num1, num2, result1);
    print_multiplication(num1, num3, result2);
    print_multiplication(num2, num3, result3);
    print_multiplication(num1, num1, result4);

    natural_destroy(&num1);
    natural_destroy(&num2);
    natural_destroy(&num3);
    natural_destroy(&result1);
    natural_destroy(&result2);
    natural_destroy(&result3);
    natural_destroy(&result4);
    return 0;
}

void print_multiplication(natural_t num1, natural_t num2, natural_t result) {
    printf("Multiplication: ");
    natural_print(num1);
    printf(" * ");
    natural_print(num2);
    printf(" = ");
    natural_print(result);
    printf("\n");
}
