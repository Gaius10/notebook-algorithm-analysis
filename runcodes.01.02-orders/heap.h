#pragma once

struct toy {
    uint8_t color;
    double length;
    double rate;
};

struct heap {
    toy_t toy;
    struct heap* left;
    struct heap* right;
}


typedef struct toy* toy_t;
typedef struct heap* heap_t;
