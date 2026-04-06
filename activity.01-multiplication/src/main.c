#include <stdio.h>
#include "../lib/multiplication.h"

int main() {
    natural_t num1 = natural_create(22222222);
    natural_t num2 = natural_create(1);

    printf("Number 1: ");
    natural_print(num1);
    printf("\n");

    printf("Number 2: ");
    natural_print(num2);
    printf("\n");

    natural_t result = multiplication(num1, num2);

    printf("num1 * num2 = ");
    natural_print(result);
    printf("\n");

    natural_destroy(&num1);
    natural_destroy(&num2);
    natural_destroy(&result);
    return 0;
}

