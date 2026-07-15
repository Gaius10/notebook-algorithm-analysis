#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

struct toy {
    unsigned long long id;
    uint8_t color;
    double length;
    double rate;
};

struct toy_heap {
    struct toy* toy;
    struct toy_heap* parent;
    struct toy_heap* left;
    struct toy_heap* right;
};

typedef struct toy* toy_t;
typedef struct toy_heap* heap_t;

/**
 * 1 -> amarelo
 * 2 -> azul
 * 3 -> branco
 * 4 -> preto
 * 5 -> rosa
 * 6 -> verde
 * 7 -> vermeho
 */
char* color_names[] = {
    "desconecido",
    "amarelo",
    "azul",
    "branco",
    "preto",
    "rosa",
    "verde",
    "vermelho"
};
unsigned color_factory(char color_string[20]);

/**
 * Returns:
    *   -1 if a < b
    *    0 if a == b
    *    1 if a > b
 */
int toy_compare(toy_t a, toy_t b);
void toy_print(toy_t toy);

heap_t heap_create(toy_t toy, heap_t parent, heap_t left, heap_t right);
unsigned heap_insert(heap_t heap, toy_t toy);
void heap_print(const heap_t heap);
void heap_destroy(heap_t* heap);
unsigned heap_get_height(heap_t heap);

void heapify(heap_t heap);
void heap_swap(heap_t child, heap_t parent);
int heap_compare(heap_t a, heap_t b);

int main() {
    unsigned _ = 0;
    unsigned number_of_toys = 0;
    toy_t* toys = NULL;

    /**
     * Step 1: Init and read input
     */

    printf("DEBUG: Starting to read the number of toys.\n");

    // Number of toys
    _ = scanf("%u", &number_of_toys);
    if (_ != 1) {
        fprintf(stderr, "Failed to read the number of toys.\n");
        return 1;
    }

    // Toys data
    toys = (toy_t*) malloc(sizeof(toy_t) * number_of_toys);
    if (toys == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(toys);
        return 1;
    }

    char color_buffer[20] = "";
    double length_buffer = 0;
    double rate_buffer = 0;

    printf("DEBUG: Starting to read toy data for %u toys.\n", number_of_toys);

    for (unsigned i = 0; i < number_of_toys; i++) {
        _ = scanf("%20s %lf %lf", &color_buffer[0], &length_buffer, &rate_buffer);
        if (_ != 3) {
            fprintf(stderr, "Failed to read toy number %d\n", i);
            return 1;
        }

        toys[i] = (toy_t) malloc(sizeof(struct toy));
        if (toys[i] == NULL) {
            fprintf(stderr, "Memory allocation failed for toy number %d\n", i);

            for (unsigned j = 0; j < i; j++) {
                free(toys[j]);
            }
            free(toys);

            return 1;
        }

        toys[i]->id = i;
        toys[i]->color = color_factory(color_buffer);
        toys[i]->length = length_buffer;
        toys[i]->rate = rate_buffer;

        toy_print(toys[i]);
    }

    printf("DEBUG: Successfully read %u toys.\n", number_of_toys);

    /**
     * Step 2: Populate the heap
     */
    heap_t toy_heap = heap_create(toys[0], NULL, NULL, NULL);
    if (toy_heap == NULL) {
        fprintf(stderr, "Failed to create the heap.\n");
        for (unsigned i = 0; i < number_of_toys; i++) {
            free(toys[i]);
        }
        free(toys);
        return 1;
    }

    for (unsigned i = 1; i < number_of_toys; i++) {
        _ = heap_insert(toy_heap, toys[i]);
        if (_ != 0) {
            fprintf(stderr, "Error inserting toy number %u.\n", i);
            for (unsigned i = 0; i < number_of_toys; i++) {
                free(toys[i]);
            }
            free(toys);
            return 1;
        }
    }

    /**
     * Step 3: Print the heap
     */

    heap_print(toy_heap);
    printf("\n");

    /**
     * Step 4: Cleanup
     */
    for (unsigned i = 0; i < number_of_toys; i++) {
        free(toys[i]);
    }
    free(toys);
    heap_destroy(&toy_heap);

    return 0;
}

unsigned color_factory(char color_string[20]) {
    if (strcmp(color_string, "amarelo") == 0) return 1;
    if (strcmp(color_string, "azul")    == 0) return 2;
    if (strcmp(color_string, "branco")  == 0) return 3;
    if (strcmp(color_string, "preto")   == 0) return 4;
    if (strcmp(color_string, "rosa")    == 0) return 5;
    if (strcmp(color_string, "verde")   == 0) return 6;
    if (strcmp(color_string, "vermelho") == 0) return 7;

    printf("Warning: Unrecognized color '%s'. Defaulting to 0.\n", color_string);
    return 0;
}

heap_t heap_create(toy_t toy, heap_t parent, heap_t left, heap_t right) {
    heap_t new_heap = (heap_t) malloc(sizeof(struct toy_heap));
    if (new_heap == NULL) {
        fprintf(stderr, "Memory allocation failed for heap node.\n");
        return NULL;
    }

    if (toy == NULL) {
        fprintf(stderr, "Toy cannot be NULL when creating a heap node.\n");
        free(new_heap);
        return NULL;
    }

    new_heap->toy = toy;
    new_heap->parent = parent;
    new_heap->left = left;
    new_heap->right = right;

    return new_heap;
}


unsigned heap_insert(heap_t heap, toy_t toy) {
    if (heap == NULL) {
        fprintf(stderr, "Cannot insert into a NULL heap.\n");
        return 1;
    }

    unsigned left_height = heap_get_height(heap->left);
    unsigned right_height = heap_get_height(heap->right);

    heap_t* target_heap = (left_height <= right_height) ? &heap->left : &heap->right;
    if (*target_heap == NULL) {
        *target_heap = heap_create(toy, heap, NULL, NULL);
        if (*target_heap == NULL) {
            fprintf(stderr, "Failed to create a new heap node for the toy.\n");
            return 1;
        }

        heapify(*target_heap);
        return 0;
    }

    return heap_insert(*target_heap, toy);
}

void heapify(heap_t heap) {
    if (heap == NULL || heap->parent == NULL) {
        return;
    }

    int cmp = toy_compare(heap->toy, heap->parent->toy);
    if (cmp > 0) {
        heap_swap(heap, heap->parent);
        heapify(heap->parent);
    }
}

void heap_swap(heap_t child, heap_t parent) {
    toy_t temp_child_toy = child->toy;

    child->toy = parent->toy;
    parent->toy = temp_child_toy;
}

void heap_print(const heap_t heap) {
    if (heap == NULL) {
        return;
    }

    // toy_print(heap->toy);
    // printf("%llu;", heap->toy->id);

    // printf("%llu is parent of %d and %d\n",
    //     heap->toy->id,
    //     heap->left ? heap->left->toy->id : -1,
    //     heap->right ? heap->right->toy->id : -1
    // );

    int left_comes_first = heap_compare(heap->left, heap->right);

    printf("%llu is parent of %d and %d. Left comes first? %d\n",
        heap->toy->id,
        heap->left ? heap->left->toy->id : -1,
        heap->right ? heap->right->toy->id : -1,
        left_comes_first
    );

    if (left_comes_first == 1) {
        heap_print(heap->left);
        heap_print(heap->right);
    } else {
        heap_print(heap->right);
        heap_print(heap->left);
    }
}

int heap_compare(heap_t a, heap_t b) {
    if (a == NULL && b == NULL) {
        return 0;
    }

    if (a == NULL) {
        return -1;
    }

    if (b == NULL) {
        return 1;
    }

    return toy_compare(a->toy, b->toy);
}

/**
 * Returns:
    *   -1 if a < b
    *    0 if a == b
    *    1 if a > b
 */
int toy_compare(toy_t a, toy_t b) {
    if (a == NULL && b == NULL) {
        return 0;
    }

    if (a == NULL) {
        return -1;
    }

    if (b == NULL) {
        return 1;
    }

    // Order colors alphabetically
    if (a->color < b->color) {
        return 1;
    }

    if (a->color > b->color) {
        return -1;
    }

    // Smaller toys come first
    if (a->length < b->length) {
        return 1;
    }

    if (a->length > b->length) {
        return -1;
    }

    // Higher rates come first
    if (a->rate > b->rate) {
        return 1;
    }

    if (a->rate < b->rate) {
        return -1;
    }

    return 0;
}

void heap_destroy(heap_t* heap) {
    if (heap == NULL || *heap == NULL) {
        return;
    }

    heap_destroy(&(*heap)->left);
    heap_destroy(&(*heap)->right);

    free(*heap);
    *heap = NULL;
}

unsigned heap_get_height(heap_t heap) {
    if (heap == NULL) {
        return 0;
    }

    unsigned left_height = heap_get_height(heap->left);
    unsigned right_height = heap_get_height(heap->right);

    return 1 + (left_height > right_height ? left_height : right_height);
}

void toy_print(toy_t toy) {
    if (toy == NULL) {
        printf("Toy is NULL\n");
        return;
    }

    printf(
        "Toy ID: %llu, Color: %u - %s, Length: %.2lf, Rate: %.2lf\n",
        toy->id,
        toy->color,
        color_names[toy->color],
        toy->length,
        toy->rate
    );
}
