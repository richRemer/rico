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

Event create_close_event() {
    return create_signal_event(RICO_CLOSE);
}

Event create_error_event(RicoError err) {
    return create_value_event(RICO_ERROR, err);
}

Event create_keypress_event(uint64_t code) {
    return create_value_event(KEY_PRESS, code);
}

Event create_print_event(char* s) {
    return create_data_event(DISPLAY_PRINT, s);
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

