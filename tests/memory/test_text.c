#include "unity.h"

#include <devkit/memory/text.h>

#include <string.h>

/******************************************************************************
 *
 * 				TEST CASES
 *
 ******************************************************************************/

extern void test_init_deinit(void);
extern void test_init_invalid(void);
extern void test_merge(void);
extern void test_offset_get(void);
extern void test_next(void);
extern void test_append(void);
extern void test_insert(void);
extern void test_remove(void);
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
        RUN_TEST(test_merge);
        RUN_TEST(test_offset_get);
        RUN_TEST(test_next);
        RUN_TEST(test_append);
        RUN_TEST(test_insert);
        RUN_TEST(test_remove);
        RUN_TEST(test_clear);

        return UNITY_END();
}

/******************************************************************************
 *
 * 				HELPERS
 *
 ******************************************************************************/

/* "aä€😀": 1, 2, 3 and 4 byte codepoints, 10 bytes in total */
static const char MIXED[] = "a\xC3\xA4\xE2\x82\xAC\xF0\x9F\x98\x80";

static void assert_text(Text *txt, const char *expected)
{
        TEST_ASSERT_EQUAL((s32)strlen(expected), txt->length);
        TEST_ASSERT_EQUAL_STRING(expected, text_cstr(txt));
        TEST_ASSERT_TRUE(txt->length < txt->capacity);
}

/******************************************************************************
 *
 * 				TEST FUNCTIONS
 *
 ******************************************************************************/

extern void test_init_deinit(void)
{
        Text txt;

        /* Preallocate only */
        TEST_ASSERT_EQUAL(0, text_init(&txt, 16, NULL));
        assert_text(&txt, "");
        TEST_ASSERT_EQUAL(17, txt.capacity);
        text_deinit(&txt);
        TEST_ASSERT_NULL(txt.buffer);

        /* Copy a '\0'-terminated buffer */
        TEST_ASSERT_EQUAL(0, text_init(&txt, -1, MIXED));
        assert_text(&txt, MIXED);
        TEST_ASSERT_EQUAL(4, text_count(&txt));
        text_deinit(&txt);

        /* Copy only the first bytes */
        TEST_ASSERT_EQUAL(0, text_init(&txt, 3, MIXED));
        assert_text(&txt, "a\xC3\xA4");
        text_deinit(&txt);
}

extern void test_init_invalid(void)
{
        Text txt;

        TEST_ASSERT_EQUAL(-1, text_init(NULL, 4, NULL));
        TEST_ASSERT_EQUAL(-1, text_init(&txt, -1, NULL));
        TEST_ASSERT_EQUAL(-1, text_init(&txt, -1, "bad \xC0\xAF"));
        /* Cut inside a codepoint */
        TEST_ASSERT_EQUAL(-1, text_init(&txt, 2, MIXED));
}

extern void test_merge(void)
{
        Text a;
        Text b;
        Text out;

        TEST_ASSERT_EQUAL(0, text_init(&a, -1, "Gr\xC3\xBC"));
        TEST_ASSERT_EQUAL(0, text_init(&b, -1, "\xC3\x9F" "e"));
        TEST_ASSERT_EQUAL(0, text_merge(&out, a, b));
        assert_text(&out, "Gr\xC3\xBC\xC3\x9F" "e");
        TEST_ASSERT_EQUAL(5, text_count(&out));

        text_deinit(&a);
        text_deinit(&b);
        text_deinit(&out);
}

extern void test_offset_get(void)
{
        Text txt;
        u32 cp;

        TEST_ASSERT_EQUAL(0, text_init(&txt, -1, MIXED));

        TEST_ASSERT_EQUAL(0, text_offset(&txt, 0));
        TEST_ASSERT_EQUAL(1, text_offset(&txt, 1));
        TEST_ASSERT_EQUAL(3, text_offset(&txt, 2));
        TEST_ASSERT_EQUAL(6, text_offset(&txt, 3));
        TEST_ASSERT_EQUAL(10, text_offset(&txt, 4));    /* End */
        TEST_ASSERT_EQUAL(-1, text_offset(&txt, 5));
        TEST_ASSERT_EQUAL(-1, text_offset(&txt, -1));

        TEST_ASSERT_EQUAL(0, text_get(&txt, 2, &cp));
        TEST_ASSERT_EQUAL_HEX32(0x20AC, cp);
        TEST_ASSERT_EQUAL(0, text_get(&txt, 3, &cp));
        TEST_ASSERT_EQUAL_HEX32(0x1F600, cp);
        TEST_ASSERT_EQUAL(-1, text_get(&txt, 4, &cp));

        text_deinit(&txt);
}

extern void test_next(void)
{
        static const u32 expected[] = { 0x61, 0xE4, 0x20AC, 0x1F600 };
        Text txt;
        s32 off = 0;
        s32 i = 0;
        u32 cp;

        TEST_ASSERT_EQUAL(0, text_init(&txt, -1, MIXED));

        while(text_next(&txt, &off, &cp) == 0) {
                TEST_ASSERT_TRUE(i < 4);
                TEST_ASSERT_EQUAL_HEX32(expected[i], cp);
                i++;
        }

        TEST_ASSERT_EQUAL(4, i);
        TEST_ASSERT_EQUAL(10, off);

        text_deinit(&txt);
}

extern void test_append(void)
{
        Text txt;
        s32 i;

        /* Start tiny so appending has to grow the buffer several times */
        TEST_ASSERT_EQUAL(0, text_init(&txt, 0, NULL));

        TEST_ASSERT_EQUAL(0, text_append(&txt, "a", -1));
        TEST_ASSERT_EQUAL(0, text_append_cp(&txt, 0xE4));
        TEST_ASSERT_EQUAL(0, text_append(&txt, "\xE2\x82\xAC", 3));
        TEST_ASSERT_EQUAL(0, text_append_cp(&txt, 0x1F600));
        assert_text(&txt, MIXED);

        /* Invalid data is rejected and leaves the text unchanged */
        TEST_ASSERT_EQUAL(-1, text_append(&txt, "\xFF", -1));
        TEST_ASSERT_EQUAL(-1, text_append_cp(&txt, 0xD800));
        assert_text(&txt, MIXED);

        for(i = 0; i < 1000; i++) {
                TEST_ASSERT_EQUAL(0, text_append_cp(&txt, 0x20AC));
        }
        TEST_ASSERT_EQUAL(1004, text_count(&txt));
        TEST_ASSERT_EQUAL(10 + 3000, txt.length);

        text_deinit(&txt);
}

extern void test_insert(void)
{
        Text txt;

        TEST_ASSERT_EQUAL(0, text_init(&txt, -1, "a\xE2\x82\xAC"));

        /* Between the two codepoints */
        TEST_ASSERT_EQUAL(0, text_insert(&txt, 1, "\xC3\xA4", -1));
        assert_text(&txt, "a\xC3\xA4\xE2\x82\xAC");

        /* At the end */
        TEST_ASSERT_EQUAL(0, text_insert(&txt, 3, "\xF0\x9F\x98\x80", -1));
        assert_text(&txt, MIXED);

        /* At the front */
        TEST_ASSERT_EQUAL(0, text_insert(&txt, 0, ">", -1));
        TEST_ASSERT_EQUAL(5, text_count(&txt));

        TEST_ASSERT_EQUAL(-1, text_insert(&txt, 6, "x", -1));
        TEST_ASSERT_EQUAL(-1, text_insert(&txt, 0, "\xC3", -1));
        TEST_ASSERT_EQUAL(5, text_count(&txt));

        text_deinit(&txt);
}

extern void test_remove(void)
{
        Text txt;

        TEST_ASSERT_EQUAL(0, text_init(&txt, -1, MIXED));

        /* Remove the 2 byte and 3 byte codepoints in the middle */
        TEST_ASSERT_EQUAL(2, text_remove(&txt, 1, 2));
        assert_text(&txt, "a\xF0\x9F\x98\x80");

        /* More than available: removes up to the end */
        TEST_ASSERT_EQUAL(1, text_remove(&txt, 1, 10));
        assert_text(&txt, "a");

        /* At the end: nothing to remove */
        TEST_ASSERT_EQUAL(0, text_remove(&txt, 1, 1));
        TEST_ASSERT_EQUAL(-1, text_remove(&txt, 2, 1));

        TEST_ASSERT_EQUAL(1, text_remove(&txt, 0, 1));
        assert_text(&txt, "");

        text_deinit(&txt);
}

extern void test_clear(void)
{
        Text txt;
        s32 cap;

        TEST_ASSERT_EQUAL(0, text_init(&txt, -1, MIXED));
        cap = txt.capacity;

        text_clear(&txt);
        assert_text(&txt, "");
        TEST_ASSERT_EQUAL(0, text_count(&txt));
        TEST_ASSERT_EQUAL(cap, txt.capacity);

        TEST_ASSERT_EQUAL(0, text_append(&txt, "ok", -1));
        assert_text(&txt, "ok");

        text_deinit(&txt);
}
