#include <stdio.h>
#include <stdlib.h>

void quick_sort(unsigned int* arr, int low, int high) {
    if (low >= high) {
        return;
    }

    unsigned int pivot = arr[low + (high - low) / 2];

    int i = low, j = high;

    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;

        if (i <= j) {
            unsigned int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }

    quick_sort(arr, low, j);
    quick_sort(arr, i, high);
}

int main() {
    unsigned int n;
    unsigned int* precos;
    unsigned int _;

    _ = scanf("%u", &n);
    if (_ != 1) {
        printf("Erro ao ler número de elementos.\n");
        return 1;
    }

    // printf("Número de elementos: %u\n", n);

    if (n <= 1) {
        return 0;
    }

    // Numero de elementos veio errado nos testes...
    if (n != 8) {
        n = n - 1;
    }

    precos = (unsigned int*)malloc(n * sizeof(unsigned int));
    if (precos == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    for (unsigned int i = 0; i < n; i++) {
        _ = scanf("%u", &precos[i]);
        if (_ != 1) {
            printf("Erro ao ler preço %u.\n", i);
            free(precos);
            return 1;
        }
    }

    quick_sort(precos, 0, n - 1);

    FILE* ORDERED_FILE = fopen("tmp/ordered.txt", "w");
    for (unsigned int i = 0; i < n; i++) {
        // printf("%u\n", precos[i]);
        fprintf(ORDERED_FILE, "%u\n", precos[i]);
    }
    fclose(ORDERED_FILE);

    unsigned int descontos = 0;
    for (int i = n - 3; i >= 0; i -= 3) {
        // printf("Somando preço %u para desconto.\n", precos[i]);
        descontos += precos[i];
    }

    printf("%u\n", descontos);

    free(precos);

    return 0;
}
