#include <stdlib.h>
#include <ncurses.h>
#include "input-loop.h"

thrd_t create_input_loop(Rico rico) {
    thrd_t thr;
    thrd_create(&thr, (int(*)(void*))&input_loop, rico);
    return thr;
}

int input_loop(Rico rico) {
    Key key;

    while (rico->running) {
        key = input_read();

        if (key.code == 0x3) break;    // ^C

        printw("%016llp:", key.code);
        printw("%s", keyname(key.seq.k0));
        key.code >>= 8;

        while (key.code > 0) {
            printw("%s", keyname(key.seq.k0));
            key.code >>= 8;
        }

        printw("\n ");
    }

    return 0;
}

Key input_read() {
    Key key = {0};
    int ch, i = 0;

    ch = getch();
    key.seq.k0 = ch;

    timeout(0);

    while (++i < 8 && (ERR != (ch = getch()))) {
        key.code |= (uint64_t)ch << i*8;
    }

    timeout(-1);

    return key;
}

