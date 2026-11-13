#ifndef VASALL_DEVKIT_STACK_H
#define VASALL_DEVKIT_STACK_H

#include <devkit/scope.h>
#include <devkit/types.h>

typedef struct Stack {
        s32   item_size; /* The size of a single item in bytes */
        s32   number;    /* The number of items in the list */
        s32   alloc;     /* The number of allocated slots in the list */
        void *data;      /* The data buffer */
} Stack;

/**
 * Initialize with room for ini items of item_size bytes each.
 * Returns 0 on success, -1 on error.
 */
PUB s32 stack_init(Stack *stk, s32 item_size, s32 ini);

/**
 * Free the buffer and reset all fields.
 */
PUB void stack_deinit(Stack *stk);

/**
 * Remove all items. The buffer is kept for reuse.
 */
PUB void stack_clear(Stack *stk);

/**
 * Returns the number of items, or -1 on error.
 */
PUB s32 stack_count(Stack *stk);

/**
 * Copy num items starting at off (0 = bottom of the stack) to
 * data_out without removing them. Returns 0 on success, -1 if the range
 * is out of bounds or on error.
 */
PUB s32 stack_get(Stack *stk, s32 off, s32 num,
                        void *data_out);

/**
 * Push num items from data_in onto the top of the stack.
 * Returns num, or -1 on error.
 */
PUB s32 stack_push(Stack *stk, s32 num, void *data_in);

/**
 * Remove up to num items from the top and copy them to data_out in
 * the order they were pushed (data_out may be NULL to discard them).
 * Returns the number of items removed, or -1 on error.
 */
PUB s32 stack_pop(Stack *stk, s32 num, void *data_out);

#endif /* VASALL_DEVKIT_STACK_H */
