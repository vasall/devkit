#include <devkit/memory/queue.h>

#include <devkit/log/log.h>
#include <devkit/util/helper.h>

#include <stdlib.h>
#include <string.h>

/*
 * The queue is a plain array with a head offset: item i lives in slot
 * head_off + i. Shifting only moves the head forward. When a push would run
 * past the end of the buffer, the items are moved back to slot 0 first. The
 * buffer is only reallocated if it is still too small after that.
 */

/******************************************************************************
 *
 * 				LOCAL INTERFACE
 *
 ******************************************************************************/

/* Pointer to the slot holding item index (0 = next item to shift) */
LOC u8 *q_slot(Queue *que, s32 index);

/* Make room for num more items after the last item */
LOC s32 q_reserve(Queue *que, s32 num);

/******************************************************************************
 *
 * 				PUBLIC FUNCTIONS
 *
 ******************************************************************************/

PUB s32 queue_init(Queue *que, s32 item_size, s32 ini)
{
        if(!que || item_size < 1 || ini < 1) {
                LOG(LOG_ERROR, "Invalid parameter(s)");
                return -1;
        }

        if(!(que->data = malloc(ini * item_size))) {
                LOG(LOG_ERROR, "Failed to allocate memory for queue");
                return -1;
        }

        que->item_size = item_size;
        que->number = 0;
        que->alloc = ini;
        que->head_off = 0;

        return 0;
}

PUB void queue_deinit(Queue *que)
{
        if(!que) {
                LOG(LOG_WARN, "Invalid parameter(s)");
                return;
        }

        free(que->data);

        que->item_size = 0;
        que->number = 0;
        que->alloc = 0;
        que->data = NULL;
        que->head_off = 0;
}

PUB void queue_clear(Queue *que)
{
        if(!que) {
                LOG(LOG_WARN, "Invalid parameter(s)");
                return;
        }

        que->number = 0;
        que->head_off = 0;
}

PUB s32 queue_count(Queue *que)
{
        if(!que) {
                LOG(LOG_ERROR, "Invalid parameter(s)");
                return -1;
        }

        return que->number;
}

PUB void *queue_get(Queue *que, s32 index)
{
        if(!que) {
                LOG(LOG_ERROR, "Invalid parameter(s)");
                return NULL;
        }

        if(index < 0 || index >= que->number) {
                LOG(LOG_ERROR, "Index out of bounds");
                return NULL;
        }

        return q_slot(que, index);
}

PUB s32 queue_push(Queue *que, s32 num, void *data_in)
{
        if(!que || num < 1 || !data_in) {
                LOG(LOG_ERROR, "Invalid parameter(s)");
                return -1;
        }

        if(q_reserve(que, num) < 0) {
                return -1;
        }

        memcpy(q_slot(que, que->number), data_in, num * que->item_size);
        que->number += num;

        return num;
}

PUB s32 queue_shift(Queue *que, s32 num, void *data_out)
{
        if(!que || num < 1) {
                LOG(LOG_ERROR, "Invalid parameter(s)");
                return -1;
        }

        num = MIN(num, que->number);

        if(data_out) {
                memcpy(data_out, q_slot(que, 0), num * que->item_size);
        }

        /* An empty queue starts at slot 0 again, so nothing has to move */
        que->number -= num;
        que->head_off = que->number ? que->head_off + num : 0;

        return num;
}

/******************************************************************************
 *
 * 				LOCAL FUNCTIONS
 *
 ******************************************************************************/

LOC u8 *q_slot(Queue *que, s32 index)
{
        return (u8 *)que->data + (que->head_off + index) * que->item_size;
}

LOC s32 q_reserve(Queue *que, s32 num)
{
        s32 needed = que->number + num;
        s32 new_alloc;
        void *ptr;

        /* Enough room behind the last item */
        if(que->head_off + needed <= que->alloc) {
                return 0;
        }

        /* Enough room once the items are moved back to slot 0 */
        if(needed <= que->alloc) {
                memmove(que->data, q_slot(que, 0),
                        que->number * que->item_size);
                que->head_off = 0;
                return 0;
        }

        new_alloc = MAX(que->alloc * 2, needed);

        if(!(ptr = malloc(new_alloc * que->item_size))) {
                LOG(LOG_ERROR, "Failed to allocate memory for queue");
                return -1;
        }

        /* Copy the items to the start of the new buffer */
        memcpy(ptr, q_slot(que, 0), que->number * que->item_size);
        free(que->data);

        que->data = ptr;
        que->alloc = new_alloc;
        que->head_off = 0;

        return 0;
}
