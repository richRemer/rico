#ifndef DATA_H
#define DATA_H

#include <stdbool.h>
#include "sync.h"

typedef struct TQueueEntry {
    struct TQueueEntry* next;
    void* value;
} TQueueEntry, *QueueEntry;

typedef struct TQueue {
    QueueEntry head;
    QueueEntry tail;
    atomic_flag sync;
} TQueue, *Queue;

Queue create_queue();
bool destroy_queue(Queue queue);
bool queue_push(Queue queue, void* item);
void* queue_pull(Queue queue);

#endif
