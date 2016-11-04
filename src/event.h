#ifndef EVENT_H
#define EVENT_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define KEY_CTRL_C 0x3

typedef enum RicoError {
    EVENT_NOT_CREATED = 1,
    EVENT_TYPE_INVALID = 2
} RicoError;

typedef enum EventType {
    RICO_CLOSE = 1,
    RICO_ERROR = 2,
    KEY_PRESS = 3,
    DISPLAY_PRINT = 4
} EventType;

typedef struct TEvent {
    EventType type;
    uint64_t value;
    void* data;
    void(*handled)(struct TEvent*);
} TEvent, *Event;

Event create_signal_event(EventType type);
Event create_value_event(EventType type, uint64_t value);
Event create_data_event(EventType type, void* data);
Event create_handled_event(EventType type, void(*handled)(Event));
Event create_event(EventType type, uint64_t value, void* data,
    void(*handled)(Event));
bool destroy_event(Event evt);

#endif
