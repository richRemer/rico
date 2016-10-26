#ifndef RICO_H
#define RICO_H

#include <locale.h>
#include <ncurses.h>

typedef struct {
    char sig[4];
    bool started;
} Rico;

bool rico_init(Rico* rico);
bool rico_start(Rico* rico);
bool rico_stop(Rico* rico);
bool rico_out(Rico* rico, const char* text);
bool rico_outi(Rico* rico, int i);
int rico_scan(Rico* rico);

#endif
