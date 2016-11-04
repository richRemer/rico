#ifndef RICO_H
#define RICO_H

#include <stdbool.h>
#include "mt.h"

typedef struct TRico {
    bool running;
} TRico, *Rico;

Rico rico_create();
bool rico_destroy(Rico rico);
bool rico_run(Rico rico);

#endif
