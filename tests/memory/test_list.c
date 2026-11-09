#include "unity.h"

#include <devkit/memory/list.h>

/******************************************************************************
 *
 * 				TEST CASES
 *
 ******************************************************************************/

extern void test_init_deinit(void);
extern void test_init_invalid(void);
extern void test_push_get(void);
extern void test_pop(void);
extern void test_unshift_shift(void);
extern void test_contiguous(void);
extern void test_unshift_grow(void);
extern void test_mixed_against_reference(void);
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
        RUN_TEST(test_init_invalid);
        RUN_TEST(test_push_get);
        RUN_TEST(test_pop);
        RUN_TEST(test_unshift_shift);
        RUN_TEST(test_contiguous);
        RUN_TEST(test_unshift_grow);
        RUN_TEST(test_mixed_against_reference);
        RUN_TEST(test_clear);

        return UNITY_END();
}

/******************************************************************************
 *
 * 				HELPERS
 *
 ******************************************************************************/

static s32 get_s32(List *lst, s32 index)
{
        s32 *p = (s32 *)list_get(lst, index);
        TEST_ASSERT_NOT_NULL(p);
        return *p;
}

/******************************************************************************
 *
 * 				TEST FUNCTIONS
 *
 ******************************************************************************/

extern void test_init_deinit(void)
{
        List lst;

        TEST_ASSERT_EQUAL(0, list_init(&lst, sizeof(s32), 16));
        TEST_ASSERT_NOT_NULL(lst.data);
        TEST_ASSERT_EQUAL(0, list_count(&lst));
        TEST_ASSERT_EQUAL(16, lst.alloc);

        list_deinit(&lst);
        TEST_ASSERT_NULL(lst.data);
        TEST_ASSERT_EQUAL(0, lst.alloc);
}

extern void test_init_invalid(void)
{
        List lst;

        TEST_ASSERT_EQUAL(-1, list_init(NULL, sizeof(s32), 16));
        TEST_ASSERT_EQUAL(-1, list_init(&lst, 0, 16));
        TEST_ASSERT_EQUAL(-1, list_init(&lst, sizeof(s32), 0));
}

extern void test_push_get(void)
{
        s32 items[3] = {7, 8, 9};
        List lst;
        s32 i;

        list_init(&lst, sizeof(s32), 2);

        for(i = 0; i < 100; i++) {
                TEST_ASSERT_EQUAL(1, list_push(&lst, 1, &i));
        }
        TEST_ASSERT_EQUAL(3, list_push(&lst, 3, items));

        TEST_ASSERT_EQUAL(103, list_count(&lst));
        for(i = 0; i < 100; i++) {
                TEST_ASSERT_EQUAL(i, get_s32(&lst, i));
        }
        TEST_ASSERT_EQUAL(9, get_s32(&lst, 102));

        TEST_ASSERT_NULL(list_get(&lst, 103));
        TEST_ASSERT_NULL(list_get(&lst, -1));

        list_deinit(&lst);
}

extern void test_pop(void)
{
        s32 items[5] = {1, 2, 3, 4, 5};
        s32 out[5];
        List lst;

        list_init(&lst, sizeof(s32), 8);
        list_push(&lst, 5, items);

        /* Popped items come out in list order */
        TEST_ASSERT_EQUAL(2, list_pop(&lst, 2, out));
        TEST_ASSERT_EQUAL_INT32_ARRAY(&items[3], out, 2);

        TEST_ASSERT_EQUAL(1, list_pop(&lst, 1, NULL));
        TEST_ASSERT_EQUAL(2, list_pop(&lst, 10, out));
        TEST_ASSERT_EQUAL_INT32_ARRAY(items, out, 2);
        TEST_ASSERT_EQUAL(0, list_pop(&lst, 1, out));

        list_deinit(&lst);
}

extern void test_unshift_shift(void)
{
        s32 front[2] = {-2, -1};
        s32 back[2] = {1, 2};
        s32 out[4];
        s32 expected[4] = {-2, -1, 1, 2};
        List lst;

        list_init(&lst, sizeof(s32), 8);
        list_push(&lst, 2, back);
        TEST_ASSERT_EQUAL(2, list_unshift(&lst, 2, front));

        /* data_in[0] becomes the first item */
        TEST_ASSERT_EQUAL(-2, get_s32(&lst, 0));
        TEST_ASSERT_EQUAL(2, get_s32(&lst, 3));

        TEST_ASSERT_EQUAL(4, list_shift(&lst, 4, out));
        TEST_ASSERT_EQUAL_INT32_ARRAY(expected, out, 4);
        TEST_ASSERT_EQUAL(0, list_shift(&lst, 1, out));

        list_deinit(&lst);
}

extern void test_contiguous(void)
{
        s32 items[4] = {1, 2, 3, 4};
        s32 front = 0;
        List lst;
        s32 *arr;
        s32 i;

        list_init(&lst, sizeof(s32), 2);

        /* Shift and unshift so the items are moved, then grow the buffer */
        list_push(&lst, 4, items);
        list_shift(&lst, 1, NULL);
        list_unshift(&lst, 1, &front);
        list_push(&lst, 4, items);

        /* Item i must be right after item i - 1 */
        arr = (s32 *)list_get(&lst, 0);
        for(i = 0; i < list_count(&lst); i++) {
                TEST_ASSERT_EQUAL_PTR(&arr[i], list_get(&lst, i));
        }
        TEST_ASSERT_EQUAL(0, arr[0]);
        TEST_ASSERT_EQUAL(4, arr[3]);
        TEST_ASSERT_EQUAL(1, arr[4]);

        list_deinit(&lst);
}

extern void test_unshift_grow(void)
{
        s32 items[3] = {1, 2, 3};
        s32 front[3] = {-3, -2, -1};
        s32 expected[6] = {-3, -2, -1, 1, 2, 3};
        s32 out[6];
        List lst;

        list_init(&lst, sizeof(s32), 3);
        list_push(&lst, 3, items);

        /* Growing at the front must keep the order */
        TEST_ASSERT_EQUAL(3, list_unshift(&lst, 3, front));
        TEST_ASSERT_GREATER_OR_EQUAL(6, lst.alloc);
        TEST_ASSERT_EQUAL(6, list_shift(&lst, 6, out));
        TEST_ASSERT_EQUAL_INT32_ARRAY(expected, out, 6);

        list_deinit(&lst);
}

extern void test_mixed_against_reference(void)
{
        /* Replay a pseudo-random sequence on the list and a plain array */
        s32 ref[4096];
        s32 ref_head = 2048;
        s32 ref_num = 0;
        s32 next = 0;
        u32 seed = 12345;
        List lst;
        s32 step;
        s32 i;

        list_init(&lst, sizeof(s32), 1);

        for(step = 0; step < 2000; step++) {
                s32 vals[3];
                s32 out[3];
                s32 n;
                s32 got;

                seed = seed * 1103515245u + 12345u;
                n = (s32)((seed >> 8) % 3) + 1;

                for(i = 0; i < n; i++) {
                        vals[i] = next++;
                }

                switch((seed >> 16) % 4) {
                case 0:
                        list_push(&lst, n, vals);
                        for(i = 0; i < n; i++) {
                                ref[ref_head + ref_num++] = vals[i];
                        }
                        break;

                case 1:
                        list_unshift(&lst, n, vals);
                        ref_head -= n;
                        ref_num += n;
                        for(i = 0; i < n; i++) {
                                ref[ref_head + i] = vals[i];
                        }
                        break;

                case 2:
                        got = list_pop(&lst, n, out);
                        TEST_ASSERT_EQUAL(n < ref_num ? n : ref_num, got);
                        ref_num -= got;
                        if(got > 0) {
                                TEST_ASSERT_EQUAL_INT32_ARRAY(
                                    &ref[ref_head + ref_num], out, got);
                        }
                        break;

                default:
                        got = list_shift(&lst, n, out);
                        TEST_ASSERT_EQUAL(n < ref_num ? n : ref_num, got);
                        if(got > 0) {
                                TEST_ASSERT_EQUAL_INT32_ARRAY(&ref[ref_head],
                                                              out, got);
                        }
                        ref_head += got;
                        ref_num -= got;
                        break;
                }

                TEST_ASSERT_EQUAL(ref_num, list_count(&lst));

                /* Keep the reference array itself in bounds */
                TEST_ASSERT_TRUE(ref_head >= 3 && ref_head + ref_num <= 4093);
        }

        for(i = 0; i < ref_num; i++) {
                TEST_ASSERT_EQUAL(ref[ref_head + i], get_s32(&lst, i));
        }

        list_deinit(&lst);
}

extern void test_clear(void)
{
        s32 items[3] = {1, 2, 3};
        List lst;

        list_init(&lst, sizeof(s32), 4);
        list_push(&lst, 3, items);
        list_clear(&lst);

        TEST_ASSERT_EQUAL(0, list_count(&lst));
        TEST_ASSERT_NULL(list_get(&lst, 0));

        list_push(&lst, 1, &items[2]);
        TEST_ASSERT_EQUAL(3, get_s32(&lst, 0));

        list_deinit(&lst);
}
