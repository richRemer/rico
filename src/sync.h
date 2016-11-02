#ifndef SYNC_H
#define SYNC_H

#include <unistd.h>
#include <stdatomic.h>

// void acquire(atomic_flag*);
#define acquire(flag) \
do { \
    while (atomic_flag_test_and_set_explicit(flag, memory_order_acquire)) { \
        usleep(1); \
    } \
} while(false)

// void release(atomic_flag*);
#define release(flag) \
do { \
    atomic_flag_clear_explicit(flag, memory_order_release); \
} while(false)

#endif
