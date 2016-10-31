#ifndef INPUT_LOOP_H
#define INPUT_LOOP_H

#include "rico.h"
#include "c11threads.h"
//#include <threads.h>

typedef struct KeySequence {
    uint8_t k0, k1, k2, k3, k4, k5, k6, k7;
} KeySequence;

typedef union Key {
    uint64_t code;
    KeySequence seq;
} Key;

thrd_t create_input_loop(Rico rico);
int input_loop(Rico rico);
Key input_read();

#endif
