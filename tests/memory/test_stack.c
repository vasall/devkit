#include "unity.h"

#include <devkit/memory/stack.h>

/******************************************************************************
 *
 * 				TEST CASES
 *
 ******************************************************************************/

/**
 *
 */
extern void test_init_stack(void);

/**
 *
 */
extern void test_deinit_stack(void);

/**
 *
 */
extern void test_push_single_items(void);

/**
 *
 */
extern void test_push_multiple_items(void);

/**
 *
 */
extern void test_pop_single_items(void);

/**
 *
 */
extern void test_pop_multiple_items(void);

/**
 *
 */
extern void test_get_items(void);

/**
 *
 */
extern void test_clear_stack(void);

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

        RUN_TEST(test_init_stack);
        RUN_TEST(test_deinit_stack);
        RUN_TEST(test_push_single_items);
        RUN_TEST(test_push_multiple_items);
        RUN_TEST(test_pop_single_items);
        RUN_TEST(test_pop_multiple_items);
        RUN_TEST(test_get_items);
        RUN_TEST(test_clear_stack);

        return UNITY_END();
}

/******************************************************************************
 *
 * 				TEST FUNCTIONS
 *
 ******************************************************************************/

extern void test_init_stack(void)
{
        s32 ret;
        Stack stack;

        ret = stack_init(&stack, sizeof(int), 1000);
        TEST_ASSERT(ret == 0);

        TEST_ASSERT_NOT_NULL(stack.data);
        TEST_ASSERT_EQUAL(0, stack.number);
        TEST_ASSERT_EQUAL(1000, stack.alloc);

        stack_deinit(&stack);
}

extern void test_deinit_stack(void)
{
        s32 ret;
        Stack stack;

        ret = stack_init(&stack, sizeof(int), 1000);
        TEST_ASSERT(ret == 0);

        stack_deinit(&stack);
        TEST_ASSERT_NULL(stack.data);
        TEST_ASSERT_EQUAL(0, stack.number);
        TEST_ASSERT_EQUAL(0, stack.alloc);
}

extern void test_push_single_items(void)
{
        s32 ret;
        Stack stack;
        s32 i;
        s32 old_alloc;

        ret = stack_init(&stack, sizeof(int), 10);
        TEST_ASSERT(ret == 0);
        TEST_ASSERT_EQUAL(10, stack.alloc);

        old_alloc = stack.alloc;

        for(i = 0; i < 2000; i++) {
                ret = stack_push(&stack, 1, &i);
                TEST_ASSERT_NOT_EQUAL(-1, ret);
        }

        TEST_ASSERT_GREATER_THAN(old_alloc, stack.alloc);
        TEST_ASSERT_EQUAL(2000, stack.number);

        stack_deinit(&stack);
}

extern void test_push_multiple_items(void)
{
        s32 items[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        s32 ret;
        s32 i;
        Stack stack;

        ret = stack_init(&stack, sizeof(s32), 4);
        TEST_ASSERT(ret == 0);

        /* Pushing more than fits at once must grow the buffer far enough */
        for(i = 0; i < 100; i++) {
                ret = stack_push(&stack, 10, items);
                TEST_ASSERT_EQUAL(10, ret);
        }

        TEST_ASSERT_GREATER_OR_EQUAL(1000, stack.alloc);
        TEST_ASSERT_EQUAL(1000, stack.number);

        for(i = 0; i < 1000; i++) {
                TEST_ASSERT_EQUAL(i % 10 + 1, ((s32 *)stack.data)[i]);
        }

        stack_deinit(&stack);
}

extern void test_pop_single_items(void)
{
        s32 ret;
        Stack stack;
        s32 i;

        ret = stack_init(&stack, sizeof(int), 1000);
        TEST_ASSERT(ret == 0);

        for(i = 0; i < 2000; i++) {
                ret = stack_push(&stack, 1, &i);
        }

        TEST_ASSERT_EQUAL(2000, stack_count(&stack));

        for(i = 1999; i >= 0; i--) {
                s32 popped;

                ret = stack_pop(&stack, 1, &popped);
                TEST_ASSERT_EQUAL(i, popped);
        }

        TEST_ASSERT_EQUAL(0, stack_count(&stack));

        stack_deinit(&stack);
}

extern void test_pop_multiple_items(void)
{
        s32 items[5] = {1, 2, 3, 4, 5};
        s32 out[5];
        s32 ret;
        Stack stack;

        ret = stack_init(&stack, sizeof(s32), 2);
        TEST_ASSERT(ret == 0);

        stack_push(&stack, 5, items);

        /* Popped items keep the order they were pushed in */
        ret = stack_pop(&stack, 3, out);
        TEST_ASSERT_EQUAL(3, ret);
        TEST_ASSERT_EQUAL_INT32_ARRAY(&items[2], out, 3);

        /* Asking for more than is left pops what is there */
        ret = stack_pop(&stack, 10, out);
        TEST_ASSERT_EQUAL(2, ret);
        TEST_ASSERT_EQUAL_INT32_ARRAY(items, out, 2);

        TEST_ASSERT_EQUAL(0, stack_pop(&stack, 1, out));

        /* NULL output just discards */
        stack_push(&stack, 5, items);
        TEST_ASSERT_EQUAL(2, stack_pop(&stack, 2, NULL));
        TEST_ASSERT_EQUAL(3, stack_count(&stack));

        stack_deinit(&stack);
}

extern void test_get_items(void)
{
        s32 items[5] = {1, 2, 3, 4, 5};
        s32 out[3];
        Stack stack;

        TEST_ASSERT_EQUAL(0, stack_init(&stack, sizeof(s32), 8));
        stack_push(&stack, 5, items);

        TEST_ASSERT_EQUAL(0, stack_get(&stack, 1, 3, out));
        TEST_ASSERT_EQUAL_INT32_ARRAY(&items[1], out, 3);
        TEST_ASSERT_EQUAL(5, stack_count(&stack));

        TEST_ASSERT_EQUAL(-1, stack_get(&stack, 3, 3, out));
        TEST_ASSERT_EQUAL(-1, stack_get(&stack, -1, 1, out));

        stack_deinit(&stack);
}

extern void test_clear_stack(void)
{
        s32 ret;
        Stack stack;
        s32 i;

        ret = stack_init(&stack, sizeof(int), 1000);
        TEST_ASSERT(ret == 0);

        for(i = 0; i < 1000; i++) {
                stack_push(&stack, 1, &i);
        }

        stack_clear(&stack);
        TEST_ASSERT_EQUAL(0, stack_count(&stack));
        TEST_ASSERT_EQUAL(1000, stack.alloc);

        /* The stack is usable again after clearing */
        i = 42;
        stack_push(&stack, 1, &i);
        i = 0;
        stack_pop(&stack, 1, &i);
        TEST_ASSERT_EQUAL(42, i);

        stack_deinit(&stack);
}
