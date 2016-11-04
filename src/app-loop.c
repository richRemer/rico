#include <stdio.h>
#include <string.h>
#include "app-loop.h"
#include "data.h"

thrd_t create_app_loop(Rico rico) {
    thrd_t thr;
    thrd_create(&thr, (int(*)(void*))&app_loop, rico);
    rico->running = true;
    return thr;
}

int app_loop(Rico rico) {
    Event evt, newevt;
    char* msg;
    int len;

    while (rico->running) {
        if ((evt = queue_pull(rico->app_events))) {
            switch (evt->type) {
            case RICO_CLOSE:
                rico->running = false;
                break;
            case RICO_ERROR:
                msg = malloc(6);
                strcpy(msg, "err\n ");
                newevt = create_print_event(msg);
                queue_push(rico->display_events, newevt);
                break;
            case KEY_PRESS:
                switch (evt->value) {
                    case KEY_CTRL_C:
                        newevt = create_close_event();
                        queue_push(rico->app_events, newevt);
                        break;
                    default:
                        len = snprintf(msg, 0, "%16p\n ", (void*)evt->value);
                        msg = malloc(len * sizeof(char));

                        if (msg) {
                            sprintf(msg, "%16p\n ", (void*)evt->value);
                            newevt = create_print_event(msg);
                            queue_push(rico->display_events, newevt);
                        } else {
                            newevt = create_error_event(EVENT_NOT_CREATED);
                            queue_push(rico->app_events, newevt);
                        }
                }
                break;
            case DISPLAY_PRINT:
                newevt = create_error_event(EVENT_TYPE_INVALID);
                queue_push(rico->app_events, newevt);
                break;
            }

            destroy_event(evt);
        }
    }

    return 0;
}
