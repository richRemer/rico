#include <stdlib.h>
#include "rico.h"

int main(int argc, char* argv[]) {
    Rico* rico = malloc(sizeof (Rico));
    int key;

    rico_init(rico);
    rico_start(rico);

    rico_out(rico, "Rico αλφα\n");

    while ((key = rico_scan(rico))) {
        rico_outi(rico, key);
        rico_out(rico, " ");
    }

    rico_stop(rico);
    free(rico);

    return 0;
}

