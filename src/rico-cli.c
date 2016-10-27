#include <stdlib.h>
#include "rico.h"

int main(int argc, char* argv[]) {
    Rico rico = rico_create();
    rico_run(rico);
    return 0;
}

