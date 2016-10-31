#include <stdlib.h>
#include <ncurses.h>
#include "rico.h"
#include "input-loop.h"
#include "display-loop.h"

Rico rico_create() {
    Rico rico = malloc(sizeof(TRico));

    if (rico) {
        rico->running = false;
    }

    return rico;
}

bool rico_run(Rico rico) {
    thrd_t input, display;
    bool success = false;

    if (rico->running) return false;

    initscr();

    rico->running = true;
    input = create_input_loop(rico);
    display = create_display_loop(rico);

    if (!input || !display) {
        rico->running = false;
    }

    if (input) thrd_join(input, NULL);
    if (display) thrd_join(display, NULL);

    if (input && display) {
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

