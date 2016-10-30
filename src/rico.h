#ifndef RICO_H
#define RICO_H

#include <stdbool.h>

typedef struct TRico {
    bool running;
} TRico, *Rico;

Rico rico_create();
bool rico_destroy(Rico rico);
bool rico_run(Rico rico);
bool rico_draw(Rico rico);
bool rico_out(Rico rico, const char* text);
bool rico_outi(Rico rico, int i);
int rico_scan(Rico rico);

#endif
