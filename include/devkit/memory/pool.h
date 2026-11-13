#ifndef VASALL_DEVKIT_POOL_H
#define VASALL_DEVKIT_POOL_H

#include <devkit/scope.h>
#include <devkit/types.h>

#include <devkit/memory/list.h>
#include <devkit/memory/stack.h>

/******************************************************************************
 *
 * 				 DEFINES/MACROS
 *
 ******************************************************************************/

/**
 * Check if a handle was handed out by a pool. Works for every struct with
 * index and generation fields, so typed handles can use it too. It doesn't
 * tell if the item was removed since; pool_get does.
 */
#define POOL_HANDLE_VALID(h) ((h).index >= 0 && (h).generation != 0)

/* Initializer for a handle that refers to nothing: { POOL_HANDLE_NONE } */
#define POOL_HANDLE_NONE -1, 0

/******************************************************************************
 *
 * 				   STRUCTURES
 *
 ******************************************************************************/

/**
 * Refers to an item in a pool. Removing an item bumps the generation of its
 * slot, so old handles stop working instead of reaching a newer item in the
 * same slot. Generation 0 is never used, so a zeroed handle is invalid.
 */
typedef struct PoolHandle {
        s32 index;
        u32 generation;
} PoolHandle;

/**
 * Stores items of one size in slots that are reused after removal. The items
 * live in chunks that are never moved, so a pointer to an item stays valid
 * until the item is removed or the pool is freed.
 */
typedef struct Pool {
        s32 item_size;          /* The size of a single item in bytes */
        s32 chunk_items;        /* Items per chunk */

        List chunks;            /* List of u8 *, the item memory */
        List slots;             /* List of PoolSlot, one per item */
        Stack free_slots;       /* Indices of removed items, s32 */
        s32 count;              /* The number of items in the pool */
} Pool;

/******************************************************************************
 *
 * 				PUBLIC INTERFACE
 *
 ******************************************************************************/

/**
 * Initialize an empty pool.
 *
 * @param pool Pointer to the pool
 * @param item_size The size of one item in bytes
 * @param chunk_items How many items are allocated at once
 *
 * @returns 0 on success, -1 on error
 */
PUB s32 pool_init(Pool *pool, s32 item_size, s32 chunk_items);

/**
 * Free the pool. The items are not looked at, free what they own first.
 */
PUB void pool_deinit(Pool *pool);

/**
 * Make a handle from its parts.
 */
PUB PoolHandle pool_handle(s32 index, u32 generation);

/**
 * Add an item, reusing the slot of a removed item if there is one.
 *
 * @param pool Pointer to the pool
 * @param item The item to copy into the pool, or NULL for a zeroed item
 * @param handle_out Receives the handle of the item
 *
 * @returns A pointer to the item in the pool, or NULL on error
 */
PUB void *pool_add(Pool *pool, const void *item, PoolHandle *handle_out);

/**
 * Get an item.
 *
 * @returns A pointer to the item, or NULL if the handle is invalid or the
 *          item was removed
 */
PUB void *pool_get(Pool *pool, PoolHandle handle);

/**
 * Remove an item. Its handle and pointers to it become invalid.
 *
 * @returns 0 on success, -1 if the handle is invalid or already removed
 */
PUB s32 pool_remove(Pool *pool, PoolHandle handle);

/**
 * Get the number of items in the pool.
 */
PUB s32 pool_count(Pool *pool);

/**
 * Get the number of slots, used or free. Together with pool_at this walks
 * over all items:
 *
 *   for(i = 0; i < pool_slots(&pool); i++) {
 *           Item *it = pool_at(&pool, i, NULL);
 *           if(it) { ... }
 *   }
 */
PUB s32 pool_slots(Pool *pool);

/**
 * Get the item in a slot.
 *
 * @param pool Pointer to the pool
 * @param slot The slot, 0 .. pool_slots - 1
 * @param handle_out Receives the item's handle (may be NULL)
 *
 * @returns The item, or NULL if the slot is free or out of range
 */
PUB void *pool_at(Pool *pool, s32 slot, PoolHandle *handle_out);

#endif /* VASALL_DEVKIT_POOL_H */
