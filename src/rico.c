#include <stdlib.h>
#include <locale.h>
#include <ncurses.h>
#include "rico.h"
#include "io-loop.h"

Rico rico_create() {
    Rico rico = malloc(sizeof(TRico));

    if (rico) {
        rico->running = false;
    }

    return rico;
}

bool rico_run(Rico rico) {
    thrd_t io;
    bool success = false;

    if (rico->running) return false;
    rico->running = true;

    setlocale(LC_ALL, "");
    if ((io = create_io_loop(rico))) {
        thrd_join(io, NULL);
    } else {
        rico->running = false;
    }

    rico_destroy(rico);
    success = (bool)io;
    return success;
}

bool rico_destroy(Rico rico) {
    if (rico->running) return false;
    free(rico);
    return true;
}

