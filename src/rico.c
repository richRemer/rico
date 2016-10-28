#include <stdlib.h>
#include "rico.h"

Rico rico_create() {
    Rico rico = malloc(sizeof(rico_t));

    rico->sig[0] = 'R';
    rico->sig[1] = 'i';
    rico->sig[2] = 'c';
    rico->sig[3] = 'o';
    rico->running = false;

    return rico;
}

bool rico_run(Rico rico) {
    int key;
    char* name;

    if (rico->running) return false;

    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);

    rico_out(rico, "Rico αλφα\n");
    rico->running = true;

    while (false != (key = rico_scan(rico))) {
        rico_outi(rico, key);
        name = malloc(snprintf(NULL, 0, ":%s ", keyname(key)));
        sprintf(name, ":%s ", keyname(key));
        rico_out(rico, name);
        free(name);
    }

    rico_destroy(rico);
    return true;
}

bool rico_destroy(Rico rico) {
    if (!rico->running) return false;

    echo();
    nocbreak();
    endwin();

    rico->running = false;
    free(rico);

    return true;
}

bool rico_out(Rico rico, const char* text) {
    if (!rico->running) return false;

    printw(text);
    refresh();

    return true;
}

bool rico_outi(Rico rico, int i) {
    if (!rico->running) return false;

    printw("%i", i);
    refresh();

    return true;
}

int rico_scan(Rico rico) {
    int key = 0;

    if (rico->running) {
        key = getch();

        if (key == 27) {
            timeout(0);
            key = getch();
            timeout(-1);

            if (key == ERR) key = 27;
            else key += 1000;
        }
    }

    return key;
}

