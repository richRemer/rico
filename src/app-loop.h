#ifndef APP_LOOP_H
#define APP_LOOP_H

#include "rico.h"
#include "c11threads.h"
//#include <threads.h>

thrd_t create_app_loop(Rico rico);
int app_loop(Rico rico);

#endif
