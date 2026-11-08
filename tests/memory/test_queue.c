#include "unity.h"

#include <devkit/memory/queue.h>

/******************************************************************************
 *
 * 				TEST CASES
 *
 ******************************************************************************/

extern void test_init_deinit(void);
extern void test_fifo_order(void);
extern void test_get(void);
extern void test_interleaved(void);
extern void test_clear(void);

/******************************************************************************
 *
 * 				TEST RUNNER
 *
 ******************************************************************************/

extern void setUp(void) {}
extern void tearDown(void) {}

int main(void)
{
        UNITY_BEGIN();

        RUN_TEST(test_init_deinit);
        RUN_TEST(test_fifo_order);
        RUN_TEST(test_get);
        RUN_TEST(test_interleaved);
        RUN_TEST(test_clear);

        return UNITY_END();
}

/******************************************************************************
 *
 * 				TEST FUNCTIONS
 *
 ******************************************************************************/

extern void test_init_deinit(void)
{
        Queue que;

        TEST_ASSERT_EQUAL(0, queue_init(&que, sizeof(s32), 8));
        TEST_ASSERT_NOT_NULL(que.data);
        TEST_ASSERT_EQUAL(0, queue_count(&que));

        queue_deinit(&que);
        TEST_ASSERT_NULL(que.data);
        TEST_ASSERT_EQUAL(0, que.alloc);

        TEST_ASSERT_EQUAL(-1, queue_init(NULL, sizeof(s32), 8));
        TEST_ASSERT_EQUAL(-1, queue_init(&que, sizeof(s32), 0));
}

extern void test_fifo_order(void)
{
        Queue que;
        s32 i;

        queue_init(&que, sizeof(s32), 2);

        for(i = 0; i < 500; i++) {
                TEST_ASSERT_EQUAL(1, queue_push(&que, 1, &i));
        }

        TEST_ASSERT_EQUAL(500, queue_count(&que));

        for(i = 0; i < 500; i++) {
                s32 out;
                TEST_ASSERT_EQUAL(1, queue_shift(&que, 1, &out));
                TEST_ASSERT_EQUAL(i, out);
        }

        TEST_ASSERT_EQUAL(0, queue_shift(&que, 1, NULL));

        queue_deinit(&que);
}

extern void test_get(void)
{
        s32 items[3] = {4, 5, 6};
        Queue que;

        queue_init(&que, sizeof(s32), 4);
        queue_push(&que, 3, items);
        queue_shift(&que, 1, NULL);

        TEST_ASSERT_EQUAL(5, *(s32 *)queue_get(&que, 0));
        TEST_ASSERT_EQUAL(6, *(s32 *)queue_get(&que, 1));
        TEST_ASSERT_NULL(queue_get(&que, 2));

        queue_deinit(&que);
}

extern void test_interleaved(void)
{
        s32 items[3] = {0, 0, 0};
        s32 out[3];
        s32 next_in = 0;
        s32 next_out = 0;
        Queue que;
        s32 round;
        s32 i;

        queue_init(&que, sizeof(s32), 3);

        /* Push 3, shift 2 each round so the queue grows while wrapping */
        for(round = 0; round < 100; round++) {
                for(i = 0; i < 3; i++) {
                        items[i] = next_in++;
                }
                queue_push(&que, 3, items);

                TEST_ASSERT_EQUAL(2, queue_shift(&que, 2, out));
                TEST_ASSERT_EQUAL(next_out, out[0]);
                TEST_ASSERT_EQUAL(next_out + 1, out[1]);
                next_out += 2;
        }

        TEST_ASSERT_EQUAL(next_in - next_out, queue_count(&que));

        queue_deinit(&que);
}

extern void test_clear(void)
{
        s32 v = 1;
        Queue que;

        queue_init(&que, sizeof(s32), 4);
        queue_push(&que, 1, &v);
        queue_push(&que, 1, &v);
        queue_clear(&que);

        TEST_ASSERT_EQUAL(0, queue_count(&que));
        TEST_ASSERT_EQUAL(0, queue_shift(&que, 1, NULL));

        queue_deinit(&que);
}
