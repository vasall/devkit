#include <devkit/memory/queue.h>
#include <devkit/memory/list.h>

#include <devkit/log/log.h>

#include <stddef.h>

/*
 * A queue is a list restricted to push at the back and shift at the front.
 * Queue and List have the same fields, so each call copies the fields into a
 * List, runs the list function and copies the result back.
 */

/******************************************************************************
 *
 * 				LOCAL INTERFACE
 *
 ******************************************************************************/

LOC List q_to_list(Queue *que);
LOC void q_from_list(Queue *que, List *lst);

/******************************************************************************
 *
 * 				PUBLIC FUNCTIONS
 *
 ******************************************************************************/

PUB s32 queue_init(Queue *que, s32 item_size, s32 ini)
{
        List lst;

        if(!que) {
                LOG(LOG_ERROR, "Invalid parameter(s)");
                return -1;
        }

        if(list_init(&lst, item_size, ini) < 0) {
                return -1;
        }

        q_from_list(que, &lst);
        return 0;
}

PUB void queue_deinit(Queue *que)
{
        List lst;

        if(!que) {
                LOG(LOG_WARN, "Invalid parameter(s)");
                return;
        }

        lst = q_to_list(que);
        list_deinit(&lst);
        q_from_list(que, &lst);
}

PUB void queue_clear(Queue *que)
{
        List lst;

        if(!que) {
                LOG(LOG_WARN, "Invalid parameter(s)");
                return;
        }

        lst = q_to_list(que);
        list_clear(&lst);
        q_from_list(que, &lst);
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
        List lst;

        if(!que) {
                LOG(LOG_ERROR, "Invalid parameter(s)");
                return NULL;
        }

        lst = q_to_list(que);
        return list_get(&lst, index);
}

PUB s32 queue_push(Queue *que, s32 num, void *data_in)
{
        List lst;
        s32 ret;

        if(!que) {
                LOG(LOG_ERROR, "Invalid parameter(s)");
                return -1;
        }

        lst = q_to_list(que);
        ret = list_push(&lst, num, data_in);
        q_from_list(que, &lst);

        return ret;
}

PUB s32 queue_shift(Queue *que, s32 num, void *data_out)
{
        List lst;
        s32 ret;

        if(!que) {
                LOG(LOG_ERROR, "Invalid parameter(s)");
                return -1;
        }

        lst = q_to_list(que);
        ret = list_shift(&lst, num, data_out);
        q_from_list(que, &lst);

        return ret;
}

/******************************************************************************
 *
 * 				LOCAL FUNCTIONS
 *
 ******************************************************************************/

LOC List q_to_list(Queue *que)
{
        List lst;
        lst.item_size = que->item_size;
        lst.number = que->number;
        lst.alloc = que->alloc;
        lst.data = que->data;
        lst.head_off = que->head_off;
        return lst;
}

LOC void q_from_list(Queue *que, List *lst)
{
        que->item_size = lst->item_size;
        que->number = lst->number;
        que->alloc = lst->alloc;
        que->data = lst->data;
        que->head_off = lst->head_off;
}
