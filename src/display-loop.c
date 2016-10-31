#include <unistd.h>
#include <ncurses.h>
#include "display-loop.h"

thrd_t create_display_loop(Rico rico) {
    thrd_t thr;
    thrd_create(&thr, (int(*)(void*))&display_loop, rico);
    return thr;
}

int display_loop(Rico rico) {
    TermSize known_size, term;

    while (rico->running) {
        getmaxyx(stdscr, term.rows, term.cols);

        if (term.rows != known_size.rows || term.cols != known_size.cols) {
            known_size.rows = term.rows;
            known_size.cols = term.cols;
            move(0, 0);
            clrtoeol();
            mvprintw(0, 2, "*keyscan*");
            mvprintw(0, term.cols-9, "| Rico α");
            move(1, 1);
        }

        //usleep(10000);  // 16.6k is 60fps
    }

    return 0;
}
