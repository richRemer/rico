#ifndef RICO_H
#define RICO_H

#include <locale.h>
#include <ncurses.h>

typedef struct rico_t {
    char sig[4];
    bool running;
} rico_t, *Rico;

Rico rico_create();
bool rico_destroy(Rico rico);
bool rico_run(Rico rico);
bool rico_out(Rico rico, const char* text);
bool rico_outi(Rico rico, int i);
int rico_scan(Rico rico);

#endif
