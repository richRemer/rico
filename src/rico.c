#include <stdlib.h>
#include <locale.h>
#include "rico.h"
#include "app-loop.h"
#include "io-loop.h"

Rico rico_create() {
    Rico rico = malloc(sizeof(TRico));
    Queue key_events = malloc(sizeof(TQueue));
    Queue display_events = malloc(sizeof(TQueue));

    if (!rico || !key_events || !display_events) goto failure;

    rico->running = false;
    rico->key_events = events;
    rico->display_events = display_events;

    return rico;

failure:
    free(display_events);
    free(key_events);
    free(rico);
    return NULL;
}

bool rico_run(Rico rico) {
    thrd_t app, io;
    bool success = false;

    setlocale(LC_ALL, "");

    if (!rico->running
        && (app = create_app_loop(rico))
        && (io = create_io_loop(rico)) {

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

