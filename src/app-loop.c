#include "app-loop.h"
#include "queue.h"

thrd_t create_app_loop(Rico rico) {
    thrd_t thr;
    thrd_create(&thr, (int(*)(void*))&app_loop, rico);
    rico->running = true;
    return thr;
}

int app_loop(Rico rico) {
    Event* evt, newevt;

    while (rico->running) {
        if (evt = queue_pull(rico->queue)) {
            switch (evt->type) {
            case RICO_CLOSE:
                rico->running = false;
                break;
            case KEY_PRESS:
                switch (evt->data) {
                    case KEY_CTRL_C:
                        newevt = create_event(RICO_CLOSE, 0);
                        queue_push(rico->queue, newevt);
                        break;
                    default:
                        newevt = create_event(
                        printw("%016llp:", key.code);

                }
                break;
            }
            if (evt->type == KEY_PRESS) {
                if (evt->data == KEY_CTRL_C) {
                    queue_push(rico->queue, (Event)
                }
            }

            destroy_event(evt);
        }
    }
}
