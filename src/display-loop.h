#ifndef DISPLAY_LOOP_H
#define DISPLAY_LOOP_H

#include "rico.h"
#include "c11threads.h"
//#include <threads.h>

typedef struct TermSize {
    short rows;
    short cols;
} TermSize;

thrd_t create_display_loop(Rico rico);
int display_loop(Rico rico);

#endif
