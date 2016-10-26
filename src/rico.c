#include "rico.h"

bool rico_init(Rico* rico) {
    rico->sig[0] = 'R';
    rico->sig[1] = 'i';
    rico->sig[2] = 'c';
    rico->sig[3] = 'o';
    rico->started = false;

    return true;
}

bool rico_start(Rico* rico) {
    if (rico->started) return false;

    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();

    rico->started = true;

    return true;
}

bool rico_stop(Rico* rico) {
    if (!rico->started) return false;

    echo();
    nocbreak();
    endwin();

    rico->started = false;

    return true;
}

bool rico_out(Rico* rico, const char* text) {
    if (!rico->started) return false;

    printw(text);
    refresh();

    return true;
}

bool rico_outi(Rico* rico, int i) {
    if (!rico->started) return false;

    printw("%i", i);
    refresh();

    return true;
}

int rico_scan(Rico* rico) {
    int key = 0;

    if (rico->started) {
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

