#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

unsigned power(uint8_t n, unsigned long long int k);

int main() {
    uint8_t n = 0;
    unsigned long long int k = 0;
    unsigned result = 0;

    uint8_t _ = scanf("%hhu %llu", &n, &k);
    if (_ != 2) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    result = power(n, k);
    printf("%u\n", result);

    return 0;
}

unsigned power(uint8_t n, unsigned long long int k) {
    if (k == 0) {
        return 1;
    }

    if (k % 2 == 0) {
        unsigned half_power = power(n, k / 2);

        return ((half_power % 1000) * (half_power % 1000)) % 1000;
    } else {
        return (n % 1000) * power(n, k - 1);
    }
}
