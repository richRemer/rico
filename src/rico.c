#include <stdlib.h>
#include <locale.h>
#include "rico.h"
#include "app-loop.h"
#include "io-loop.h"

Rico rico_create() {
    Rico rico = malloc(sizeof(TRico));
    Queue app_events = create_queue();
    Queue display_events = create_queue();

    if (!(rico && app_events && display_events)) goto failure;

    rico->running = false;
    rico->app_events = app_events;
    rico->display_events = display_events;

    return rico;

failure:
    destroy_queue(display_events);
    destroy_queue(app_events);
    free(rico);
    return NULL;
}

bool rico_run(Rico rico) {
    thrd_t app, io;
    bool success = false;

    setlocale(LC_ALL, "");

    if (!rico->running
        && (app = create_app_loop(rico))
        && (io = create_io_loop(rico))) {

        success = true;
    } else {
        rico->running = false;
    }

    if (app) thrd_join(app, NULL);
    if (io) thrd_join(io, NULL);

    rico_destroy(rico);
    return success;
}

bool rico_destroy(Rico rico) {
    if (rico->running) return false;
    free(rico);
    return true;
}

