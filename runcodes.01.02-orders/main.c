#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>



#define NUMBER_OF_AVAILABLE_COLORS 7
char* available_colors[] = {
    "amarelo",
    "azul",
    "branco",
    "preto",
    "rosa",
    "verde",
    "vermelho"
};
uint8_t color_factory(char color_buffer[10]);

int main() {
    unsigned _ = 0;
    unsigned number_of_toys = 0;

    uint8_t* colors = NULL;
    double* lengths = NULL;
    double* rates = NULL;

    unsigned* heap = NULL;

    _ = scanf("%u", &number_of_toys);
    if (_ != 1) {
        fprintf(stderr, "Error reading number of toys.\n");
        return 1;
    }

    colors = (uint8_t*) malloc(number_of_toys * sizeof(uint8_t));
    lengths = (double*) malloc(number_of_toys * sizeof(double));
    rates = (double*) malloc(number_of_toys * sizeof(double));

    heap = (unsigned*) malloc(number_of_toys * sizeof(double));

    char color_buffer[10] = "";
    for (unsigned i = 0; i < number_of_toys; i++) {
        _ = scanf("%10s %lf %lf", &color_buffer, &lengths[i], &rates[i]);
        if (_ != 3) {
            fprintf(stderr, "Error reading data of toy #%u.\n", i);
            return 1;
        }

        colors[i] = color_factory(color_buffer);
    }
}

uint8_t color_factory(char color_buffer[10]) {
    for (unsigned i = 0; i < NUMBER_OF_AVAILABLE_COLORS; i++) {
        if (strcmp(color_buffer, available_colors[i]) == 0) {
            return i;
        }
    }
}
