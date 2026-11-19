#include <devkit/memory/list.h>

#include <devkit/log/log.h>
#include <devkit/util/helper.h>

#include <stdlib.h>
#include <string.h>

/**
 * The list is a plain array: item i lives in slot i. Push and pop at the end
 * are O(1), unshift and shift at the front move all items.
 */

/******************************************************************************
 *
 * 				LOCAL INTERFACE
 *
 ******************************************************************************/

/* Pointer to the slot holding item index (0 = first item) */
LOC u8 *l_slot(List *lst, s32 index);

/* Make room for at least min_alloc items */
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
}

PUB void list_clear(List *lst)
{
        if(!lst) {
                LOG(LOG_WARN, "Invalid parameter(s)");
                return;
        }

        lst->number = 0;
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

        memcpy(l_slot(lst, lst->number), data_in, num * lst->item_size);
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
        lst->number -= num;

        if(data_out) {
                memcpy(data_out, l_slot(lst, lst->number),
                       num * lst->item_size);
        }

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

        /* Move the existing items back to make room at the front */
        memmove(l_slot(lst, num), lst->data, lst->number * lst->item_size);
        memcpy(lst->data, data_in, num * lst->item_size);
        lst->number += num;

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
                memcpy(data_out, lst->data, num * lst->item_size);
        }

        /* Move the remaining items to the front */
        lst->number -= num;
        memmove(lst->data, l_slot(lst, num), lst->number * lst->item_size);

        return num;
}

/******************************************************************************
 *
 * 				LOCAL FUNCTIONS
 *
 ******************************************************************************/

LOC u8 *l_slot(List *lst, s32 index)
{
        return (u8 *)lst->data + index * lst->item_size;
}

LOC s32 l_reserve(List *lst, s32 min_alloc)
{
        s32 new_alloc;
        void *ptr;

        if(min_alloc <= lst->alloc) {
                return 0;
        }

        new_alloc = MAX(lst->alloc * 2, min_alloc);

        if(!(ptr = realloc(lst->data, new_alloc * lst->item_size))) {
                LOG(LOG_ERROR, "Failed to allocate memory for list");
                return -1;
        }

        lst->data = ptr;
        lst->alloc = new_alloc;

        return 0;
}
