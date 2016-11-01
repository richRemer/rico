#include <stdlib.h>
#include <ncurses.h>
#include "io-loop.h"

thrd_t create_io_loop(Rico rico) {
    thrd_t thr;
    thrd_create(&thr, (int(*)(void*))&io_loop, rico);
    return thr;
}

int io_loop(Rico rico) {
    DisplaySize currsz = {0}, cmpsz;
    Key key;

    initscr();
    raw();
    noecho();

    while (rico->running) {
        getmaxyx(stdscr, cmpsz.rows, cmpsz.cols);

        if (currsz.rows != cmpsz.rows || currsz.cols != cmpsz.cols) {
            currsz = cmpsz;
            redraw(currsz);
        }

        if ((key = key_scan()).code > 0) {
            if (key.code == 0x3) {  // ^C
                rico->running = false;
            }

            printw("%016llp:", key.code);
            printw("%s", keyname(key.seq.k0));
            key.code >>= 8;

            while (key.code > 0) {
                printw("%s", keyname(key.seq.k0));
                key.code >>= 8;
            }

            printw("\n ");
        }
    }

    echo();
    noraw();
    endwin();

    return 0;
}

Key key_scan() {
    Key key = {0};
    int ch, i = 0;

    timeout(0);

    while (i < 8 && (ERR != (ch = getch()))) {
        key.code |= (uint64_t)ch << 8*i++;
    }

    timeout(-1);

    return key;
}

void redraw(DisplaySize sz) {
    move(0, 0);
    clrtoeol();
    mvprintw(0, 2, "*keyscan*");
    mvprintw(0, sz.cols-9, "| Rico α");

    for (int row = 1; row <= sz.rows; row++) {
        move(row, 0);
        clrtoeol();
    }

    move(1, 1);
    refresh();
}
