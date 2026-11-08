#ifndef VASALL_DEVKIT_QUEUE_H
#define VASALL_DEVKIT_QUEUE_H

#include <devkit/scope.h>
#include <devkit/types.h>

typedef struct Queue {
        s32   item_size; /* The size of a single item in bytes */
        s32   number;    /* The number of items in the list */
        s32   alloc;     /* The number of allocated slots in the list */
        void *data;      /* The data buffer */
        s32   head_off;  /*  The index offset for the first element */
} Queue;

/*
 * Initialize with room for ini items of item_size bytes each.
 * Returns 0 on success, -1 on error.
 */
PUB s32 queue_init(Queue *que, s32 item_size, s32 ini);

/*
 * Free the buffer and reset all fields.
 */
PUB void queue_deinit(Queue *que);

/*
 * Remove all items. The buffer is kept for reuse.
 */
PUB void queue_clear(Queue *que);

/*
 * Returns the number of items, or -1 on error.
 */
PUB s32 queue_count(Queue *que);

/*
 * Returns a pointer to the item at index (0 = next item to shift), or
 * NULL if index is out of range. The pointer is invalidated by
 * queue_push(), since the buffer may be reallocated.
 */
PUB void *queue_get(Queue *que, s32 index);

/*
 * Add num items from data_in to the back of the queue.
 * Returns num, or -1 on error.
 */
PUB s32 queue_push(Queue *que, s32 num, void *data_in);

/*
 * Remove up to num items from the front and copy them to data_out,
 * oldest first (data_out may be NULL to discard them).
 * Returns the number of items removed, or -1 on error.
 */
PUB s32 queue_shift(Queue *que, s32 num, void *data_out);

#endif /* VASALL_DEVKIT_QUEUE_H */
