#ifndef IO_LOOP_H
#define IO_LOOP_H

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

typedef struct DisplaySize {
    short rows;
    short cols;
} DisplaySize;

thrd_t create_io_loop(Rico rico);
int io_loop(Rico rico);
Key key_scan();
void redraw(DisplaySize sz);

#endif
