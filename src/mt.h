#ifndef MT_H
#define MT_H

#if __STDC_NO_THREADS__
#include "c11threads.h"
#else
#include <threads.h>
#endif

#endif
