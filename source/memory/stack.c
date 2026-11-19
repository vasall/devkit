#include <devkit/memory/stack.h>

#include <devkit/log/log.h>
#include <devkit/util/helper.h>

#include <stdlib.h>
#include <string.h>

/******************************************************************************
 *
 * 				LOCAL INTERFACE
 *
 ******************************************************************************/

/* Check if the items [off, off + num) exist */
LOC s32 s_in_range(Stack *stk, s32 off, s32 num);

/* Pointer to the item at index */
LOC u8 *s_offset(Stack *stk, s32 index);

/* Pointer to the first free slot after the last item */
LOC u8 *s_tail(Stack *stk);

/******************************************************************************
 *
 * 				PUBLIC FUNCTIONS
 *
 ******************************************************************************/

PUB s32 stack_init(Stack *stk, s32 item_size, s32 ini)
{
        if(!stk || item_size < 1 || ini < 1) {
                LOG(LOG_ERROR, "Invalid parameter(s)");
                return -1;
        }

        if(!(stk->data = malloc(ini * item_size))) {
                LOG(LOG_ERROR, "Failed to allocate memory for stack");
                return -1;
        }

        stk->item_size = item_size;
        stk->number = 0;
        stk->alloc = ini;

        return 0;
}

PUB void stack_deinit(Stack *stk)
{
        if(!stk) {
                LOG(LOG_WARN, "Invalid parameter(s)");
                return;
        }

        free(stk->data);

        stk->item_size = 0;
        stk->number = 0;
        stk->alloc = 0;
        stk->data = NULL;
}

PUB void stack_clear(Stack *stk)
{
        if(!stk) {
                LOG(LOG_WARN, "Invalid parameter(s)");
                return;
        }

        stk->number = 0;
}

PUB s32 stack_count(Stack *stk)
{
        if(!stk) {
                LOG(LOG_ERROR, "Invalid parameter(s)");
                return -1;
        }

        return stk->number;
}

PUB s32 stack_get(Stack *stk, s32 off, s32 num, void *data_out)
{
        if(!stk || num < 1 || !data_out) {
                LOG(LOG_ERROR, "Invalid parameter(s)");
                return -1;
        }

        if(!s_in_range(stk, off, num)) {
                LOG(LOG_ERROR, "Given range is out of bounds");
                return -1;
        }

        memcpy(data_out, s_offset(stk, off), num * stk->item_size);

        return 0;
}

PUB s32 stack_push(Stack *stk, s32 num, void *data_in)
{
        s32 new_number;

        if(!stk || num < 1 || !data_in) {
                LOG(LOG_ERROR, "Invalid parameter(s)");
                return -1;
        }

        new_number = stk->number + num;
        if(new_number > stk->alloc) {
                void *ptr;
                s32 new_alloc;

                /* Grow by at least 1.5x so pushes stay amortized O(1) */
                new_alloc = MAX(stk->alloc + stk->alloc / 2, new_number);

                if(!(ptr = realloc(stk->data, new_alloc * stk->item_size))) {
                        LOG(LOG_ERROR, "Failed to realloc stack memory");
                        return -1;
                }

                stk->data = ptr;
                stk->alloc = new_alloc;
        }

        memcpy(s_tail(stk), data_in, num * stk->item_size);
        stk->number += num;

        return num;
}

PUB s32 stack_pop(Stack *stk, s32 num, void *data_out)
{
        if(!stk || num < 1) {
                LOG(LOG_ERROR, "Invalid parameter(s)");
                return -1;
        }

        num = MIN(num, stk->number);

        if(data_out) {
                memcpy(data_out, s_offset(stk, stk->number - num),
                       num * stk->item_size);
        }

        stk->number -= num;

        return num;
}

/******************************************************************************
 *
 * 				LOCAL FUNCTIONS
 *
 ******************************************************************************/

LOC s32 s_in_range(Stack *stk, s32 off, s32 num)
{
        if(off < 0 || off >= stk->number) return 0;
        if(off + num > stk->number) return 0;
        return 1;
}

LOC u8 *s_offset(Stack *stk, s32 index)
{
        return (u8 *)stk->data + index * stk->item_size;
}

LOC u8 *s_tail(Stack *stk)
{
        return s_offset(stk, stk->number);
}
