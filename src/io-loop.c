#include <stdlib.h>
#include <ncurses.h>
#include "io-loop.h"
#include "queue.h"

thrd_t create_io_loop(Rico rico) {
    thrd_t thr;
    thrd_create(&thr, (int(*)(void*))&io_loop, rico);
    return thr;
}

int io_loop(Rico rico) {
    DisplaySize currsz = {0}, cmpsz;
    Key key;
    Event* evt;

    initscr();
    raw();
    noecho();

    while (rico->running) {
        getmaxyx(stdscr, cmpsz.rows, cmpsz.cols);

        if (currsz.rows != cmpsz.rows || currsz.cols != cmpsz.cols) {
            currsz = cmpsz;
            redraw(currsz);
        }

        if (evt = queue_pull(rico->display_events)) {
            switch (evt->type) {
            case DISPLAY_PRINT:
                printw((char*)evt->data);
                free((char*)evt->data);
                break;
            }
            destroy_event(evt);
        }

        if ((key = key_scan()).code > 0) {
            queue_push(rico->key_events, create_event(KEY_PRESS, key.code));
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
    clear();
    mvprintw(0, 2, "*keyscan*");
    mvprintw(0, sz.cols-9, "| Rico α");
    move(1, 1);
    refresh();
}
