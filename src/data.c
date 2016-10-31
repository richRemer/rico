#include <stdlib.h>
#include "data.h"

Queue create_queue() {
    Queue queue = malloc(sizeof(TQueue));

    if (queue) {
        queue->head = NULL;
        queue->tail = NULL;
    }

    return queue;
}

bool destroy_queue(Queue queue) {
    bool destroyed = false;

    if (queue) {
        do {} while (queue_pull(queue));
        free(queue);
        destroyed = true;
    }

    return destroyed;
}

bool queue_push(Queue queue, void* item) {
    QueueEntry entry;
    bool queued = false;

    if (item && (entry = malloc(sizeof(TQueueEntry)))) {
        acquire(&queue->sync);

        if (queue->head) {
            queue->head->next = entry;
            queue->head = entry;
        } else {
            queue->head = entry;
            queue->tail = entry;
        }

        entry->value = item;
        queued = true;

        release(&queue->sync);
    }

    return queued;
}

void* queue_pull(Queue queue) {
    QueueEntry entry;
    void* item;

    acquire(&queue->sync);

    if (queue->tail) {
        entry = queue->tail;
        item = entry->value;
        queue->tail = entry->next;
        free(entry);

        if (!queue->tail) {
            queue->head = NULL;
        }
    }

    release(&queue->sync);

    return item;
}

