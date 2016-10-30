#ifndef KEY_H
#define KEY_H

#include <ncurses.h>

typedef struct KeyBytes {
    uint8_t byte_1;
    uint8_t byte_2;
    uint8_t byte_3;
    uint8_t byte_4;
    uint8_t byte_5;
    uint8_t byte_6;
    uint16_t reserved;
} KeyBytes;

typedef union Key {
    int64_t keycode;
    KeyBytes bytes;
} Key;

Key scankey();
Key readkey();
bool printkey(Key key);

#endif
