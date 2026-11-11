#include "unity.h"

#include <devkit/memory/hashmap.h>

/******************************************************************************
 *
 * 				TEST CASES
 *
 ******************************************************************************/

extern void test_init_deinit(void);
extern void test_init_invalid(void);
extern void test_set_get(void);
extern void test_overwrite(void);
extern void test_key_zero_rejected(void);
extern void test_grow_keeps_entries(void);
extern void test_remove_keeps_probe_runs(void);
extern void test_clear(void);
extern void test_mixed_against_reference(void);

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
        RUN_TEST(test_set_get);
        RUN_TEST(test_overwrite);
        RUN_TEST(test_key_zero_rejected);
        RUN_TEST(test_grow_keeps_entries);
        RUN_TEST(test_remove_keeps_probe_runs);
        RUN_TEST(test_clear);
        RUN_TEST(test_mixed_against_reference);

        return UNITY_END();
}

/******************************************************************************
 *
 * 				TEST FUNCTIONS
 *
 ******************************************************************************/

extern void test_init_deinit(void)
{
        HashMap map;

        TEST_ASSERT_EQUAL(0, hashmap_init(&map, 10));
        TEST_ASSERT_NOT_NULL(map.keys);
        TEST_ASSERT_TRUE(map.capacity >= 20);
        TEST_ASSERT_EQUAL(0, hashmap_count(&map));

        hashmap_deinit(&map);
        TEST_ASSERT_NULL(map.keys);
        TEST_ASSERT_EQUAL(0, map.capacity);
}

extern void test_init_invalid(void)
{
        HashMap map;

        TEST_ASSERT_EQUAL(-1, hashmap_init(NULL, 10));
        TEST_ASSERT_EQUAL(-1, hashmap_init(&map, -1));
}

extern void test_set_get(void)
{
        HashMap map;
        u64 v = 0;

        hashmap_init(&map, 4);
        TEST_ASSERT_EQUAL(0, hashmap_set(&map, 42, 7));
        TEST_ASSERT_EQUAL(1, hashmap_get(&map, 42, &v));
        TEST_ASSERT_EQUAL(7, (s32)v);
        TEST_ASSERT_EQUAL(1, hashmap_get(&map, 42, NULL));
        TEST_ASSERT_EQUAL(0, hashmap_get(&map, 43, &v));
        hashmap_deinit(&map);
}

extern void test_overwrite(void)
{
        HashMap map;
        u64 v = 0;

        hashmap_init(&map, 4);
        hashmap_set(&map, 5, 1);
        hashmap_set(&map, 5, 2);
        TEST_ASSERT_EQUAL(1, hashmap_count(&map));
        hashmap_get(&map, 5, &v);
        TEST_ASSERT_EQUAL(2, (s32)v);
        hashmap_deinit(&map);
}

extern void test_key_zero_rejected(void)
{
        HashMap map;

        hashmap_init(&map, 4);
        TEST_ASSERT_EQUAL(-1, hashmap_set(&map, 0, 1));
        TEST_ASSERT_EQUAL(0, hashmap_get(&map, 0, NULL));
        TEST_ASSERT_EQUAL(0, hashmap_remove(&map, 0));
        TEST_ASSERT_EQUAL(0, hashmap_count(&map));
        hashmap_deinit(&map);
}

extern void test_grow_keeps_entries(void)
{
        HashMap map;
        u64 v;
        u64 i;

        hashmap_init(&map, 1);
        for(i = 1; i <= 1000; i++)
                TEST_ASSERT_EQUAL(0, hashmap_set(&map, i * 7919, i));

        TEST_ASSERT_EQUAL(1000, hashmap_count(&map));
        TEST_ASSERT_TRUE(map.count * 10 <= map.capacity * 7);
        for(i = 1; i <= 1000; i++) {
                TEST_ASSERT_EQUAL(1, hashmap_get(&map, i * 7919, &v));
                TEST_ASSERT_TRUE(v == i);
        }
        hashmap_deinit(&map);
}

extern void test_remove_keeps_probe_runs(void)
{
        HashMap map;
        u64 v;
        u64 i;

        hashmap_init(&map, 4);
        for(i = 1; i <= 1000; i++)
                hashmap_set(&map, i * 7919, i);

        for(i = 1; i <= 1000; i += 2)
                TEST_ASSERT_EQUAL(1, hashmap_remove(&map, i * 7919));
        TEST_ASSERT_EQUAL(500, hashmap_count(&map));
        TEST_ASSERT_EQUAL(0, hashmap_remove(&map, 7919));

        /* The rest must still be found after the backward shifts */
        for(i = 2; i <= 1000; i += 2) {
                TEST_ASSERT_EQUAL(1, hashmap_get(&map, i * 7919, &v));
                TEST_ASSERT_TRUE(v == i);
        }
        for(i = 1; i <= 1000; i += 2)
                TEST_ASSERT_EQUAL(0, hashmap_get(&map, i * 7919, NULL));
        hashmap_deinit(&map);
}

extern void test_clear(void)
{
        HashMap map;
        s32 cap;

        hashmap_init(&map, 4);
        hashmap_set(&map, 1, 1);
        hashmap_set(&map, 2, 2);
        cap = map.capacity;

        hashmap_clear(&map);
        TEST_ASSERT_EQUAL(0, hashmap_count(&map));
        TEST_ASSERT_EQUAL(cap, map.capacity);
        TEST_ASSERT_EQUAL(0, hashmap_get(&map, 1, NULL));
        TEST_ASSERT_EQUAL(0, hashmap_set(&map, 1, 3));
        hashmap_deinit(&map);
}

/* Random sets and removes, checked against a plain array */
extern void test_mixed_against_reference(void)
{
        HashMap map;
        u64 ref[64];
        u64 v;
        u32 seed = 12345;
        s32 count = 0;
        s32 step;
        s32 k;

        hashmap_init(&map, 4);
        for(k = 0; k < 64; k++) ref[k] = 0;

        for(step = 0; step < 5000; step++) {
                seed = seed * 1103515245u + 12345u;
                k = (s32)((seed >> 16) % 64);

                if((seed >> 8) & 1) {
                        if(ref[k] == 0) count++;
                        ref[k] = (u64)step + 1;
                        hashmap_set(&map, (u64)k + 1, ref[k]);
                } else {
                        if(ref[k] != 0) count--;
                        ref[k] = 0;
                        hashmap_remove(&map, (u64)k + 1);
                }
        }

        TEST_ASSERT_EQUAL(count, hashmap_count(&map));
        for(k = 0; k < 64; k++) {
                if(ref[k] == 0) {
                        TEST_ASSERT_EQUAL(0, hashmap_get(&map, (u64)k + 1,
                                                NULL));
                } else {
                        TEST_ASSERT_EQUAL(1, hashmap_get(&map, (u64)k + 1,
                                                &v));
                        TEST_ASSERT_TRUE(v == ref[k]);
                }
        }
        hashmap_deinit(&map);
}
