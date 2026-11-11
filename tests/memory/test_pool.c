#include "unity.h"

#include <devkit/memory/pool.h>

/******************************************************************************
 *
 * 				TEST CASES
 *
 ******************************************************************************/

extern void test_init_invalid(void);
extern void test_add_get(void);
extern void test_remove_invalidates(void);
extern void test_slot_reuse(void);
extern void test_pointers_stable(void);
extern void test_iterate(void);
extern void test_zeroed_handle(void);

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

        RUN_TEST(test_init_invalid);
        RUN_TEST(test_add_get);
        RUN_TEST(test_remove_invalidates);
        RUN_TEST(test_slot_reuse);
        RUN_TEST(test_pointers_stable);
        RUN_TEST(test_iterate);
        RUN_TEST(test_zeroed_handle);

        return UNITY_END();
}

/******************************************************************************
 *
 * 				TEST FUNCTIONS
 *
 ******************************************************************************/

extern void test_init_invalid(void)
{
        Pool pool;

        TEST_ASSERT_EQUAL(-1, pool_init(NULL, sizeof(s32), 4));
        TEST_ASSERT_EQUAL(-1, pool_init(&pool, 0, 4));
        TEST_ASSERT_EQUAL(-1, pool_init(&pool, sizeof(s32), 0));
}

extern void test_add_get(void)
{
        Pool pool;
        PoolHandle a;
        PoolHandle b;
        s32 va = 11;
        s32 *pb;

        pool_init(&pool, sizeof(s32), 4);

        TEST_ASSERT_NOT_NULL(pool_add(&pool, &va, &a));
        pb = pool_add(&pool, NULL, &b);
        TEST_ASSERT_NOT_NULL(pb);
        TEST_ASSERT_EQUAL(0, *pb);

        TEST_ASSERT_TRUE(POOL_HANDLE_VALID(a));
        TEST_ASSERT_EQUAL(11, *(s32 *)pool_get(&pool, a));
        TEST_ASSERT_EQUAL_PTR(pb, pool_get(&pool, b));
        TEST_ASSERT_EQUAL(2, pool_count(&pool));

        pool_deinit(&pool);
}

extern void test_remove_invalidates(void)
{
        Pool pool;
        PoolHandle a;
        s32 v = 5;

        pool_init(&pool, sizeof(s32), 4);
        pool_add(&pool, &v, &a);

        TEST_ASSERT_EQUAL(0, pool_remove(&pool, a));
        TEST_ASSERT_NULL(pool_get(&pool, a));
        TEST_ASSERT_EQUAL(-1, pool_remove(&pool, a));
        TEST_ASSERT_EQUAL(0, pool_count(&pool));

        pool_deinit(&pool);
}

extern void test_slot_reuse(void)
{
        Pool pool;
        PoolHandle a;
        PoolHandle b;
        s32 v1 = 1;
        s32 v2 = 2;

        pool_init(&pool, sizeof(s32), 4);
        pool_add(&pool, &v1, &a);
        pool_remove(&pool, a);
        pool_add(&pool, &v2, &b);

        /* Same slot, new generation: the old handle must not reach it */
        TEST_ASSERT_EQUAL(a.index, b.index);
        TEST_ASSERT_NOT_EQUAL(a.generation, b.generation);
        TEST_ASSERT_NULL(pool_get(&pool, a));
        TEST_ASSERT_EQUAL(2, *(s32 *)pool_get(&pool, b));
        TEST_ASSERT_EQUAL(1, pool_slots(&pool));

        pool_deinit(&pool);
}

extern void test_pointers_stable(void)
{
        Pool pool;
        PoolHandle first;
        PoolHandle h;
        s32 *p;
        s32 v = 42;
        s32 i;

        pool_init(&pool, sizeof(s32), 2);
        p = pool_add(&pool, &v, &first);

        /* Many more items than fit into one chunk */
        for(i = 0; i < 100; i++) {
                TEST_ASSERT_NOT_NULL(pool_add(&pool, &i, &h));
        }

        TEST_ASSERT_EQUAL_PTR(p, pool_get(&pool, first));
        TEST_ASSERT_EQUAL(42, *p);
        TEST_ASSERT_EQUAL(99, *(s32 *)pool_get(&pool, h));

        pool_deinit(&pool);
}

extern void test_iterate(void)
{
        Pool pool;
        PoolHandle h[5];
        PoolHandle got;
        s32 sum = 0;
        s32 seen = 0;
        s32 i;

        pool_init(&pool, sizeof(s32), 2);
        for(i = 0; i < 5; i++) {
                pool_add(&pool, &i, &h[i]);
        }
        pool_remove(&pool, h[1]);
        pool_remove(&pool, h[3]);

        for(i = 0; i < pool_slots(&pool); i++) {
                s32 *it = pool_at(&pool, i, &got);

                if(it) {
                        TEST_ASSERT_EQUAL_PTR(it, pool_get(&pool, got));
                        sum += *it;
                        seen++;
                }
        }

        TEST_ASSERT_EQUAL(3, seen);
        TEST_ASSERT_EQUAL(0 + 2 + 4, sum);

        pool_deinit(&pool);
}

extern void test_zeroed_handle(void)
{
        Pool pool;
        PoolHandle h;
        PoolHandle zero = { 0, 0 };
        PoolHandle none = { POOL_HANDLE_NONE };
        s32 v = 7;

        pool_init(&pool, sizeof(s32), 4);
        pool_add(&pool, &v, &h);

        TEST_ASSERT_FALSE(POOL_HANDLE_VALID(zero));
        TEST_ASSERT_FALSE(POOL_HANDLE_VALID(none));
        TEST_ASSERT_NULL(pool_get(&pool, zero));
        TEST_ASSERT_NULL(pool_get(&pool, none));

        pool_deinit(&pool);
}
