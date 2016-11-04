#include "event.h"

Event create_signal_event(EventType type) {
    return create_event(type, 0, NULL, NULL);
}

Event create_value_event(EventType type, uint64_t value) {
    return create_event(type, value, NULL, NULL);
}

Event create_data_event(EventType type, void* data) {
    return create_event(type, 0, data, NULL);
}

Event create_handled_event(EventType type, void(*handled)(Event)) {
    return create_event(type, 0, NULL, handled);
}

Event create_event(EventType type, uint64_t value, void* data,
    void(*handled)(Event)) {

    Event evt = malloc(sizeof(TEvent));

    if (evt) {
        evt->type = type;
        evt->value = value;
        evt->data = data;
        evt->handled = handled;
    }

    return evt;
}

bool destroy_event(Event evt) {
    if (!evt) return false;
    if (evt->handled) evt->handled(evt);
    free(evt->data);
    free(evt);
    return true;
}

