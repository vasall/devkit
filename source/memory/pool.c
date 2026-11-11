#include <devkit/memory/pool.h>

#include <devkit/log/log.h>

#include <stdlib.h>
#include <string.h>

/******************************************************************************
 *
 * 				LOCAL INTERFACE
 *
 ******************************************************************************/

typedef struct PoolSlot {
        u32 generation;
        s32 used;
} PoolSlot;

/* The slot of a handle, or NULL if the handle doesn't match a used slot */
LOC PoolSlot *p_slot(Pool *pool, PoolHandle handle);

/* Pointer to the item memory of a slot */
LOC u8 *p_item(Pool *pool, s32 index);

/* Add a new slot at the end, allocating a chunk when needed */
LOC s32 p_new_slot(Pool *pool);

/******************************************************************************
 *
 * 				PUBLIC FUNCTIONS
 *
 ******************************************************************************/

PUB s32 pool_init(Pool *pool, s32 item_size, s32 chunk_items)
{
        if(!pool || item_size < 1 || chunk_items < 1) {
                LOG(LOG_ERROR, "Invalid parameter(s)");
                return -1;
        }

        if(list_init(&pool->chunks, sizeof(u8 *), 4) < 0) {
                goto err;
        }

        if(list_init(&pool->slots, sizeof(PoolSlot), chunk_items) < 0) {
                goto err_chunks;
        }

        if(stack_init(&pool->free_slots, sizeof(s32), 8) < 0) {
                goto err_slots;
        }

        pool->item_size = item_size;
        pool->chunk_items = chunk_items;
        pool->count = 0;

        return 0;

err_slots:
        list_deinit(&pool->slots);

err_chunks:
        list_deinit(&pool->chunks);

err:
        LOG(LOG_ERROR, "Failed to initialize pool");
        return -1;
}

PUB void pool_deinit(Pool *pool)
{
        s32 i;

        if(!pool) {
                return;
        }

        for(i = 0; i < list_count(&pool->chunks); i++) {
                free(*(u8 **)list_get(&pool->chunks, i));
        }

        stack_deinit(&pool->free_slots);
        list_deinit(&pool->slots);
        list_deinit(&pool->chunks);
        pool->count = 0;
}

PUB PoolHandle pool_handle(s32 index, u32 generation)
{
        PoolHandle handle;

        handle.index = index;
        handle.generation = generation;

        return handle;
}

PUB void *pool_add(Pool *pool, const void *item, PoolHandle *handle_out)
{
        PoolSlot *slot;
        s32 index;
        u8 *mem;

        if(!pool || !handle_out) {
                LOG(LOG_ERROR, "Invalid parameter(s)");
                return NULL;
        }

        /* Reuse a removed slot; it kept the generation it got on removal */
        if(stack_count(&pool->free_slots) > 0) {
                stack_pop(&pool->free_slots, 1, &index);
        }
        else if((index = p_new_slot(pool)) < 0) {
                return NULL;
        }

        slot = list_get(&pool->slots, index);
        slot->used = 1;

        mem = p_item(pool, index);
        if(item) {
                memcpy(mem, item, pool->item_size);
        }
        else {
                memset(mem, 0, pool->item_size);
        }

        pool->count++;

        handle_out->index = index;
        handle_out->generation = slot->generation;

        return mem;
}

PUB void *pool_get(Pool *pool, PoolHandle handle)
{
        if(!pool || !p_slot(pool, handle)) {
                return NULL;
        }

        return p_item(pool, handle.index);
}

PUB s32 pool_remove(Pool *pool, PoolHandle handle)
{
        PoolSlot *slot;

        if(!pool || !(slot = p_slot(pool, handle))) {
                return -1;
        }

        if(stack_push(&pool->free_slots, 1, &handle.index) < 0) {
                LOG(LOG_ERROR, "Failed to free pool slot");
                return -1;
        }

        slot->used = 0;

        /* Skip 0 on overflow, so a zeroed handle never becomes valid */
        if(++slot->generation == 0) {
                slot->generation = 1;
        }

        pool->count--;

        return 0;
}

PUB s32 pool_count(Pool *pool)
{
        return pool ? pool->count : 0;
}

PUB s32 pool_slots(Pool *pool)
{
        return pool ? list_count(&pool->slots) : 0;
}

PUB void *pool_at(Pool *pool, s32 slot, PoolHandle *handle_out)
{
        PoolSlot *s;

        if(!pool || slot < 0 || slot >= list_count(&pool->slots)) {
                return NULL;
        }

        s = list_get(&pool->slots, slot);
        if(!s->used) {
                return NULL;
        }

        if(handle_out) {
                handle_out->index = slot;
                handle_out->generation = s->generation;
        }

        return p_item(pool, slot);
}

/******************************************************************************
 *
 * 				LOCAL FUNCTIONS
 *
 ******************************************************************************/

LOC PoolSlot *p_slot(Pool *pool, PoolHandle handle)
{
        PoolSlot *slot;

        if(handle.index < 0 || handle.index >= list_count(&pool->slots)) {
                return NULL;
        }

        slot = list_get(&pool->slots, handle.index);
        if(!slot->used || slot->generation != handle.generation) {
                return NULL;
        }

        return slot;
}

LOC u8 *p_item(Pool *pool, s32 index)
{
        u8 *chunk = *(u8 **)list_get(&pool->chunks,
                                     index / pool->chunk_items);

        return chunk + (index % pool->chunk_items) * pool->item_size;
}

LOC s32 p_new_slot(Pool *pool)
{
        PoolSlot slot;
        s32 index = list_count(&pool->slots);

        /* The chunks are full: add one; it is never moved or resized */
        if(index == list_count(&pool->chunks) * pool->chunk_items) {
                u8 *chunk = malloc(pool->chunk_items * pool->item_size);

                if(!chunk) {
                        LOG(LOG_ERROR, "Failed to allocate pool chunk");
                        return -1;
                }

                if(list_push(&pool->chunks, 1, &chunk) < 0) {
                        free(chunk);
                        return -1;
                }
        }

        slot.generation = 1;
        slot.used = 0;

        if(list_push(&pool->slots, 1, &slot) < 0) {
                return -1;
        }

        return index;
}
