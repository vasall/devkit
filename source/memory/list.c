#include <devkit/memory/list.h>

#include <devkit/log/log.h>
#include <devkit/util/helper.h>

#include <stdlib.h>
#include <string.h>

/*
 * The list is a ring buffer: item i lives in slot (head_off + i) % alloc.
 * This keeps push/pop at the end and unshift/shift at the front all O(1).
 */

/******************************************************************************
 *
 * 				LOCAL INTERFACE
 *
 ******************************************************************************/

/* Pointer to the slot holding item index (0 = first item) */
LOC u8 *l_slot(List *lst, s32 index);

/* Copy num items starting at item index out of the ring into dst */
LOC void l_read(List *lst, s32 index, s32 num, void *dst);

/* Copy num items from src into the ring starting at item index */
LOC void l_write(List *lst, s32 index, s32 num, void *src);

/* Make room for at least min_alloc items, keeping the item order */
LOC s32 l_reserve(List *lst, s32 min_alloc);

/******************************************************************************
 *
 * 				PUBLIC FUNCTIONS
 *
 ******************************************************************************/

PUB s32 list_init(List *lst, s32 item_size, s32 ini)
{
        if(!lst || item_size < 1 || ini < 1) {
                LOG(LOG_ERROR, "Invalid parameter(s)");
                return -1;
        }

        if(!(lst->data = malloc(ini * item_size))) {
                LOG(LOG_ERROR, "Failed to allocate memory for list");
                return -1;
        }

        lst->item_size = item_size;
        lst->number = 0;
        lst->alloc = ini;
        lst->head_off = 0;

        return 0;
}

PUB void list_deinit(List *lst)
{
        if(!lst) {
                LOG(LOG_WARN, "Invalid parameter(s)");
                return;
        }

        free(lst->data);

        lst->item_size = 0;
        lst->number = 0;
        lst->alloc = 0;
        lst->data = NULL;
        lst->head_off = 0;
}

PUB void list_clear(List *lst)
{
        if(!lst) {
                LOG(LOG_WARN, "Invalid parameter(s)");
                return;
        }

        lst->number = 0;
        lst->head_off = 0;
}

PUB s32 list_count(List *lst)
{
        if(!lst) {
                LOG(LOG_ERROR, "Invalid parameter(s)");
                return -1;
        }

        return lst->number;
}

PUB void *list_get(List *lst, s32 index)
{
        if(!lst) {
                LOG(LOG_ERROR, "Invalid parameter(s)");
                return NULL;
        }

        if(index < 0 || index >= lst->number) {
                LOG(LOG_ERROR, "Index out of bounds");
                return NULL;
        }

        return l_slot(lst, index);
}

PUB s32 list_push(List *lst, s32 num, void *data_in)
{
        if(!lst || num < 1 || !data_in) {
                LOG(LOG_ERROR, "Invalid parameter(s)");
                return -1;
        }

        if(l_reserve(lst, lst->number + num) < 0) {
                return -1;
        }

        l_write(lst, lst->number, num, data_in);
        lst->number += num;

        return num;
}

PUB s32 list_pop(List *lst, s32 num, void *data_out)
{
        if(!lst || num < 1) {
                LOG(LOG_ERROR, "Invalid parameter(s)");
                return -1;
        }

        num = MIN(num, lst->number);

        if(data_out) {
                l_read(lst, lst->number - num, num, data_out);
        }

        lst->number -= num;

        return num;
}

PUB s32 list_unshift(List *lst, s32 num, void *data_in)
{
        if(!lst || num < 1 || !data_in) {
                LOG(LOG_ERROR, "Invalid parameter(s)");
                return -1;
        }

        if(l_reserve(lst, lst->number + num) < 0) {
                return -1;
        }

        /* Move the head back by num slots, wrapping around */
        lst->head_off = (lst->head_off - num % lst->alloc + lst->alloc) %
                        lst->alloc;
        lst->number += num;

        l_write(lst, 0, num, data_in);

        return num;
}

PUB s32 list_shift(List *lst, s32 num, void *data_out)
{
        if(!lst || num < 1) {
                LOG(LOG_ERROR, "Invalid parameter(s)");
                return -1;
        }

        num = MIN(num, lst->number);

        if(data_out) {
                l_read(lst, 0, num, data_out);
        }

        lst->number -= num;
        lst->head_off = lst->number ? (lst->head_off + num) % lst->alloc : 0;

        return num;
}

/******************************************************************************
 *
 * 				LOCAL FUNCTIONS
 *
 ******************************************************************************/

LOC u8 *l_slot(List *lst, s32 index)
{
        s32 slot = (lst->head_off + index) % lst->alloc;
        return (u8 *)lst->data + slot * lst->item_size;
}

LOC void l_read(List *lst, s32 index, s32 num, void *dst)
{
        s32 start = (lst->head_off + index) % lst->alloc;
        s32 first = MIN(num, lst->alloc - start);
        u8 *out = (u8 *)dst;

        /* The range may wrap past the end of the buffer: copy in two parts */
        memcpy(out, l_slot(lst, index), first * lst->item_size);
        memcpy(out + first * lst->item_size, lst->data,
               (num - first) * lst->item_size);
}

LOC void l_write(List *lst, s32 index, s32 num, void *src)
{
        s32 start = (lst->head_off + index) % lst->alloc;
        s32 first = MIN(num, lst->alloc - start);
        u8 *in = (u8 *)src;

        memcpy(l_slot(lst, index), in, first * lst->item_size);
        memcpy(lst->data, in + first * lst->item_size,
               (num - first) * lst->item_size);
}

LOC s32 l_reserve(List *lst, s32 min_alloc)
{
        s32 new_alloc;
        void *ptr;

        if(min_alloc <= lst->alloc) {
                return 0;
        }

        new_alloc = MAX(lst->alloc * 2, min_alloc);

        if(!(ptr = malloc(new_alloc * lst->item_size))) {
                LOG(LOG_ERROR, "Failed to allocate memory for list");
                return -1;
        }

        /* Unwrap the items into the new buffer, starting at slot 0 */
        l_read(lst, 0, lst->number, ptr);
        free(lst->data);

        lst->data = ptr;
        lst->alloc = new_alloc;
        lst->head_off = 0;

        return 0;
}
