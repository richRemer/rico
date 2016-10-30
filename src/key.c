#include <ncurses.h>
#include "key.h"

Key scankey() {
    Key key = {0};
    int ch;

    timeout(0);
    if (ERR != (ch = getch())) {
        key.bytes.byte_1 = ch;
        if (ERR != (ch = getch())) {
            key.bytes.byte_2 = ch;
            if (ERR != (ch = getch())) {
                key.bytes.byte_3 = ch;
                if (ERR != (ch = getch())) {
                    key.bytes.byte_4 = ch;
                }
            }
        }
    }
    timeout(-1);
    return key;
}

Key readkey() {
    Key key = {0};
    int ch;

    key.bytes.byte_1 = getch();
    timeout(0);
    if (ERR != (ch = getch())) {
        key.bytes.byte_2 = ch;
        if (ERR != (ch = getch())) {
            key.bytes.byte_3 = ch;
            if (ERR != (ch = getch())) {
                key.bytes.byte_4 = ch;
                if (ERR != (ch = getch())) {
                    key.bytes.byte_5 = ch;
                    if (ERR != (ch = getch())) {
                        key.bytes.byte_6 = ch;
                    }
                }
            }
        }
    }
    timeout(-1);
    return key;
}

bool printkey(Key key) {
    printw("%llp:(", key.keycode);

    if (key.bytes.byte_2 == 0) {
        printw("%s", keyname(key.bytes.byte_1));
    } else if (key.bytes.byte_3 == 0) {
        printw("%s%s", keyname(key.bytes.byte_1), keyname(key.bytes.byte_2));
    } else if (key.bytes.byte_4 == 0) {
        printw("%s%s%s", keyname(key.bytes.byte_1), keyname(key.bytes.byte_2),
            keyname(key.bytes.byte_3));
    } else if (key.bytes.byte_5 == 0) {
        printw("%s%s%s%s", keyname(key.bytes.byte_1), keyname(key.bytes.byte_2),
            keyname(key.bytes.byte_3), keyname(key.bytes.byte_4));
    } else if (key.bytes.byte_6 == 0) {
        printw("%s%s%s%s%s", keyname(key.bytes.byte_1),
            keyname(key.bytes.byte_2), keyname(key.bytes.byte_3),
            keyname(key.bytes.byte_4), keyname(key.bytes.byte_5));
    } else {
        printw("%s%s%s%s%s%s", keyname(key.bytes.byte_1),
            keyname(key.bytes.byte_2), keyname(key.bytes.byte_3),
            keyname(key.bytes.byte_4), keyname(key.bytes.byte_5),
            keyname(key.bytes.byte_6));
    }
    
    printw("):%s\n", keyname(key.keycode));

    return true;
}

