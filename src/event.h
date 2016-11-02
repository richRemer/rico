#ifndef EVENT_H
#define EVENT_H

#define KEY_CTRL_C = 0x3

enum EventType {
    RICO_CLOSE = 1,
    KEY_PRESS = 2,
    DISPLAY_PRINT = 3
}

typedef struct Event {
    EventType type;
    uint64_t data;
} Event;

Event* create_event(EventType type, uint64_t data) {
    Event* evt = malloc(sizeof(Event));

    if (evt) {
        evt->type = type;
        evt->data = data;
    }

    return evt;
}

bool destroy_event(Event* evt) {
    if (!evt) return false;
    free(evt);
    return true;
}

#endif
