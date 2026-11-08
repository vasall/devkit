#ifndef VASALL_DEVKIT_LIST_H
#define VASALL_DEVKIT_LIST_H

#include <devkit/scope.h>
#include <devkit/types.h>

typedef struct List {
        s32   item_size; /* The size of a single item in bytes */
        s32   number;    /* The number of items in the list */
        s32   alloc;     /* The number of allocated slots in the list */
        void *data;      /* The data buffer */
        s32   head_off;  /*  The index offset for the first element */
} List;

/*
 * Initialize with room for ini items of item_size bytes each.
 * Returns 0 on success, -1 on error.
 */
PUB s32 list_init(List *lst, s32 item_size, s32 ini);

/*
 * Free the buffer and reset all fields.
 */
PUB void list_deinit(List *lst);

/*
 * Remove all items. The buffer is kept for reuse.
 */
PUB void list_clear(List *lst);

/*
 * Returns the number of items, or -1 on error.
 */
PUB s32 list_count(List *lst);

/*
 * Returns a pointer to the item at index (0 = first item), or NULL
 * if index is out of range. The pointer is invalidated by any call that
 * adds items, since the buffer may be reallocated.
 */
PUB void *list_get(List *lst, s32 index);

/*
 * Append num items from data_in to the end, growing the buffer if
 * needed. Returns num, or -1 on error.
 */
PUB s32 list_push(List *lst, s32 num, void *data_in);

/*
 * Remove up to num items from the end and copy them to data_out in
 * list order (data_out may be NULL to discard them).
 * Returns the number of items removed, or -1 on error.
 */
PUB s32 list_pop(List *lst, s32 num, void *data_out);

/*
 * Insert num items from data_in at the front, so data_in[0] becomes
 * the first item. Returns num, or -1 on error.
 */
PUB s32 list_unshift(List *lst, s32 num, void *data_in);

/*
 * Remove up to num items from the front and copy them to data_out in
 * list order (data_out may be NULL to discard them).
 * Returns the number of items removed, or -1 on error.
 */
PUB s32 list_shift(List *lst, s32 num, void *data_out);

#endif /* VASALL_DEVKIT_LIST_H */
