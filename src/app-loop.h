#ifndef APP_LOOP_H
#define APP_LOOP_H

#include "rico.h"
#include "event.h"
#include "mt.h"

thrd_t create_app_loop(Rico rico);
int app_loop(Rico rico);

#endif
