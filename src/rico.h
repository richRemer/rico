#ifndef RICO_H
#define RICO_H

#include <stdbool.h>
#include "data.h"
#include "mt.h"

typedef struct TRico {
    bool running;
    Queue app_events;
    Queue display_events;
} TRico, *Rico;

Rico rico_create();
bool rico_destroy(Rico rico);
bool rico_run(Rico rico);

#endif
