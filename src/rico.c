#include <stdlib.h>
#include <locale.h>
#include <ncurses.h>
#include "rico.h"
#include "input-loop.h"

Rico rico_create() {
    Rico rico = malloc(sizeof(TRico));

    if (rico) {
        rico->running = false;
    }

    return rico;
}

bool rico_run(Rico rico) {
    thrd_t input;
    bool success = false;

    if (rico->running) return false;

    setlocale(LC_ALL, "");
    initscr();
    //cbreak();
    raw();
    noecho();

    rico->running = true;
    rico_draw(rico);

    if ((input = create_input_loop(rico))) {
        thrd_join(input, NULL);
        success = true;
    }

    rico_destroy(rico);
    return success;
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

bool rico_draw(Rico rico) {
    int x;

    getmaxyx(stdscr, x, x);
    mvprintw(0, 2, "*untitled*");
    mvprintw(0, x-9, "│ Rico α");
    move(1, 1);

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

