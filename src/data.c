#include <stdlib.h>
#include <stdio.h>
#include "data.h"

Queue create_queue() {
    Queue queue = malloc(sizeof(TQueue));

    if (queue) {
        queue->head = NULL;
        queue->tail = NULL;

        if ((queue->mutex = malloc(sizeof(mtx_t)))) {
            if (thrd_success != mtx_init(queue->mutex, mtx_plain)) {
                free(queue->mutex);
                free(queue);
                queue = NULL;
            }
        } else {
            free(queue);
            queue = NULL;
        }
    }

    return queue;
}

bool destroy_queue(Queue queue) {
    bool destroyed = false;

    if (queue) {
        do {} while (queue_pull(queue));
        mtx_destroy(queue->mutex);
        free(queue);
        destroyed = true;
    }

    return destroyed;
}

bool queue_push(Queue queue, void* item) {
    QueueEntry entry;
    bool queued = false;

    if (item && (entry = malloc(sizeof(TQueueEntry)))) {
        mtx_lock(queue->mutex);

        if (queue->head) {
            queue->head->next = entry;
            queue->head = entry;
        } else {
            queue->head = entry;
            queue->tail = entry;
        }

        entry->value = item;
        queued = true;

        mtx_unlock(queue->mutex);
    }

    return queued;
}

void* queue_pull(Queue queue) {
    QueueEntry entry;
    void* item = NULL;

    mtx_lock(queue->mutex);

    if (queue->tail) {
        entry = queue->tail;
        item = entry->value;
        queue->tail = entry->next;
        free(entry);

        if (!queue->tail) {
            queue->head = NULL;
        }
    }

    mtx_unlock(queue->mutex);

    return item;
}

