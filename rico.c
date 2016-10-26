#include <locale.h>
#include <ncurses.h>

typedef struct {
    char sig[4];
    bool started;
} Rico;

bool init(Rico* rico) {
    rico->sig[0] = 'R';
    rico->sig[1] = 'i';
    rico->sig[2] = 'c';
    rico->sig[3] = 'o';
    rico->started = false;

    return true;
}

bool start(Rico* rico) {
    if (rico->started) return false;

    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();

    rico->started = true;

    return true;
}

bool stop(Rico* rico) {
    if (!rico->started) return false;

    echo();
    nocbreak();
    endwin();

    rico->started = false;

    return true;
}

bool out(Rico* rico, const char* text) {
    if (!rico->started) return false;

    printw(text);
    refresh();

    return true;
}

bool outi(Rico* rico, int i) {
    if (!rico->started) return false;

    printw("%i", i);
    refresh();

    return true;
}

int scankey(Rico* rico) {
    int key = 0;

    if (rico->started) {
        key = getch();

        if (key == 27) {
            timeout(0);
            key = getch();
            timeout(-1);

            if (key == ERR) key = 27;
            else key += 1000;
        }
    }

    return key;
}

int main() {
    Rico rico = {0};
    int key;

    init(&rico);
    start(&rico);

    out(&rico, "Rico αλφα\n");

    while (key = scankey(&rico)) {
        outi(&rico, key);
        out(&rico, " ");
    }

    stop(&rico);
}

