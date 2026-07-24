#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <stdbool.h>

#define MAX_NUM_SALAS 10000

/**
 * @brief Função que implementa o algoritmo de Dijkstra para encontrar o caminho mais curto
 *        de um nó de origem para um nó alvo em um grafo representado por uma matriz de adjacência.
 *
 * @param matriz Matriz de adjacência representando o grafo.
 * @param target Nó alvo para o qual queremos encontrar o caminho mais curto.
 * @param num_salas Número de salas no grafo.
 * @return O custo do caminho mais curto do nó de origem para o nó alvo.
 */
float dijkstra(
    float **matriz,
    unsigned int target,
    unsigned int num_salas
);

int main() {
    unsigned int salas, corredores, tubulacoes;
    unsigned int consultas;
    unsigned int _;

    float** matriz_comum = NULL;
    float** matriz_impostor = NULL;

    // Init context

    _ = scanf("%u %u %u %u", &salas, &corredores, &tubulacoes, &consultas);
    if (_ != 4) {
        printf("Erro na leitura da entrada.\n");
        return 1;
    }

    if (salas > MAX_NUM_SALAS) {
        printf("Número de salas excede o limite máximo de %d.\n", MAX_NUM_SALAS);
        return 1;
    }

    matriz_comum = (float**)malloc(salas * sizeof(float*));
    matriz_impostor = (float**)malloc(salas * sizeof(float*));
    for (unsigned int i = 0; i < salas; i++) {
        matriz_comum[i] = (float*)malloc(salas * sizeof(float));
        matriz_impostor[i] = (float*)malloc(salas * sizeof(float));

        for (unsigned int j = 0; j < salas; j++) {
            matriz_comum[i][j] = -1;
            matriz_impostor[i][j] = -1;
        }
    }

    for (unsigned int i = 0; i < corredores; i++) {
        unsigned int sala1, sala2;
        float distancia;

        _ = scanf("%u %u %f", &sala1, &sala2, &distancia);
        if (_ != 3) {
            printf("Erro na leitura do corredor %u.\n", i + 1);
            return 1;
        }

        matriz_comum[sala1][sala2] = distancia;
        matriz_impostor[sala1][sala2] = distancia;
        matriz_comum[sala2][sala1] = distancia;
        matriz_impostor[sala2][sala1] = distancia;
    }

    for (unsigned int i = 0; i < tubulacoes; i++) {
        unsigned int sala1, sala2;

        _ = scanf("%u %u", &sala1, &sala2);
        if (_ != 2) {
            printf("Erro na leitura da tubulação %u.\n", i + 1);
            return 1;
        }

        if (matriz_impostor[sala1][sala2] == -1 || matriz_impostor[sala1][sala2] > 1) {
            matriz_impostor[sala1][sala2] = 1;
        }
        if (matriz_impostor[sala2][sala1] == -1 || matriz_impostor[sala2][sala1] > 1) {
            matriz_impostor[sala2][sala1] = 1;
        }
    }

    // FILE* DEBUG_MATRIX = fopen("tmp/debug_matrix.txt", "w");
    // FILE* DEBUG_MATRIX_IMPOSTOR = fopen("tmp/debug_matrix_impostor.txt", "w");

    // fprintf(DEBUG_MATRIX, "    ");
    // fprintf(DEBUG_MATRIX_IMPOSTOR, "    ");
    // for (unsigned int i = 0; i < salas; i++) {
    //     fprintf(DEBUG_MATRIX, "%4u ", i);
    //     fprintf(DEBUG_MATRIX_IMPOSTOR, "%4u ", i);
    // }
    // fprintf(DEBUG_MATRIX, "\n");
    // fprintf(DEBUG_MATRIX_IMPOSTOR, "\n");

    // for (unsigned int i = 0; i < salas; i++) {
    //     fprintf(DEBUG_MATRIX, "%2u: ", i);
    //     fprintf(DEBUG_MATRIX_IMPOSTOR, "%2u: ", i);

    //     for (unsigned int j = 0; j < salas; j++) {
    //         fprintf(DEBUG_MATRIX, "%.2f ", matriz_comum[i][j]);
    //         fprintf(DEBUG_MATRIX_IMPOSTOR, "%.2f ", matriz_impostor[i][j]);
    //     }
    //     fprintf(DEBUG_MATRIX, "\n");
    //     fprintf(DEBUG_MATRIX_IMPOSTOR, "\n");
    // }

    // fclose(DEBUG_MATRIX);
    // fclose(DEBUG_MATRIX_IMPOSTOR);

    // Core of the program
    for (unsigned int i = 0; i < consultas; i++) {
        unsigned int target;

        _ = scanf("%u", &target);
        if (_ != 1) {
            printf("Erro na leitura da consulta %u.\n", i + 1);
            return 1;
        }

        float custo_comum = dijkstra(matriz_comum, target, salas);
        float custo_impostor = dijkstra(matriz_impostor, target, salas);

        // printf("\n");
        // printf("Consulta %u (target = %u):\n", i, target);
        // printf("Custo comum: %.2f\n", custo_comum);
        // printf("Custo impostor: %.2f\n", custo_impostor);

        if (custo_impostor < custo_comum - 1e-4f) {
            printf("defeat\n");
            continue;
        }

        printf("victory\n");
    }

    // Freedom
    for (unsigned int i = 0; i < salas; i++) {
        free(matriz_comum[i]);
        free(matriz_impostor[i]);
    }
    free(matriz_comum);
    free(matriz_impostor);

    return 0;
}

float dijkstra(
    float **matriz,
    unsigned int target,
    unsigned int num_salas
) {
    float* custos = (float*)malloc(num_salas * sizeof(float));
    bool* visitados = (bool*)malloc(num_salas * sizeof(bool));

    if (custos == NULL || visitados == NULL) {
        printf("Erro ao alocar memória para custos ou visitados.\n");
        return -1.0f;
    }

    for (unsigned int i = 0; i < num_salas; i++) {
        custos[i] = FLT_MAX;
        visitados[i] = false;
    }

    custos[0] = 0.0f;

    for (unsigned int i = 0; i < num_salas - 1; i++) {
        float min_custo = FLT_MAX;
        int min_index = -1;

        for (unsigned int j = 0; j < num_salas; j++) {
            if (!visitados[j] && custos[j] < min_custo) {
                min_custo = custos[j];
                min_index = j;
            }
        }

        if (min_index == -1) {
            break; // No more reachable nodes
        }

        visitados[min_index] = true;

        for (unsigned int j = 0; j < num_salas; j++) {
            if (
                !visitados[j] &&
                matriz[min_index][j] != -1 &&
                custos[min_index] != FLT_MAX &&
                custos[min_index] + matriz[min_index][j] < custos[j]
            ) {
                custos[j] = custos[min_index] + matriz[min_index][j];
            }
        }
    }

    float resultado = custos[target];

    free(visitados);
    free(custos);

    return resultado;
}
