#include "unity.h"

#include <devkit/memory/utf8.h>

/******************************************************************************
 *
 * 				  TEST CASES
 *
 ******************************************************************************/

extern void test_decode_valid(void);
extern void test_decode_invalid(void);
extern void test_encode(void);
extern void test_encode_decode_roundtrip(void);
extern void test_count_validate(void);

/******************************************************************************
 *
 * 				  TEST RUNNER
 *
 ******************************************************************************/

extern void setUp(void) {}
extern void tearDown(void) {}

int main(void)
{
        UNITY_BEGIN();

        RUN_TEST(test_decode_valid);
        RUN_TEST(test_decode_invalid);
        RUN_TEST(test_encode);
        RUN_TEST(test_encode_decode_roundtrip);
        RUN_TEST(test_count_validate);

        return UNITY_END();
}

/******************************************************************************
 *
 * 				    HELPERS
 *
 ******************************************************************************/

/* "aä€😀": 1, 2, 3 and 4 byte codepoints, 10 bytes in total */
static const char MIXED[] = "a\xC3\xA4\xE2\x82\xAC\xF0\x9F\x98\x80";

/******************************************************************************
 *
 * 				 TEST FUNCTIONS
 *
 ******************************************************************************/

extern void test_decode_valid(void)
{
        u32 cp;

        TEST_ASSERT_EQUAL(1, utf8_decode("A", 1, &cp));
        TEST_ASSERT_EQUAL_HEX32(0x41, cp);

        TEST_ASSERT_EQUAL(2, utf8_decode("\xC3\xA4", 2, &cp));
        TEST_ASSERT_EQUAL_HEX32(0xE4, cp);

        TEST_ASSERT_EQUAL(3, utf8_decode("\xE2\x82\xAC", 3, &cp));
        TEST_ASSERT_EQUAL_HEX32(0x20AC, cp);

        TEST_ASSERT_EQUAL(4, utf8_decode("\xF0\x9F\x98\x80", 4, &cp));
        TEST_ASSERT_EQUAL_HEX32(0x1F600, cp);

        /* Boundaries */
        TEST_ASSERT_EQUAL(2, utf8_decode("\xC2\x80", 2, &cp));
        TEST_ASSERT_EQUAL_HEX32(0x80, cp);
        TEST_ASSERT_EQUAL(3, utf8_decode("\xEF\xBF\xBF", 3, &cp));
        TEST_ASSERT_EQUAL_HEX32(0xFFFF, cp);
        TEST_ASSERT_EQUAL(4, utf8_decode("\xF4\x8F\xBF\xBF", 4, &cp));
        TEST_ASSERT_EQUAL_HEX32(0x10FFFF, cp);
}

extern void test_decode_invalid(void)
{
        u32 cp;

        /* Lone continuation byte */
        TEST_ASSERT_EQUAL(-1, utf8_decode("\x80", 1, &cp));
        /* Overlong encodings */
        TEST_ASSERT_EQUAL(-1, utf8_decode("\xC0\xAF", 2, &cp));
        TEST_ASSERT_EQUAL(-1, utf8_decode("\xC1\xBF", 2, &cp));
        TEST_ASSERT_EQUAL(-1, utf8_decode("\xE0\x9F\xBF", 3, &cp));
        TEST_ASSERT_EQUAL(-1, utf8_decode("\xF0\x8F\xBF\xBF", 4, &cp));
        /* Surrogate U+D800 */
        TEST_ASSERT_EQUAL(-1, utf8_decode("\xED\xA0\x80", 3, &cp));
        /* Above U+10FFFF */
        TEST_ASSERT_EQUAL(-1, utf8_decode("\xF4\x90\x80\x80", 4, &cp));
        TEST_ASSERT_EQUAL(-1, utf8_decode("\xF5\x80\x80\x80", 4, &cp));
        /* Truncated */
        TEST_ASSERT_EQUAL(-1, utf8_decode("\xE2\x82", 2, &cp));
        /* Missing continuation */
        TEST_ASSERT_EQUAL(-1, utf8_decode("\xE2\x41\x41", 3, &cp));
        /* Empty */
        TEST_ASSERT_EQUAL(-1, utf8_decode("", 0, &cp));
}

extern void test_encode(void)
{
        char b[UTF8_MAX_BYTES];

        TEST_ASSERT_EQUAL(1, utf8_encode(0x41, b));
        TEST_ASSERT_EQUAL_MEMORY("A", b, 1);
        TEST_ASSERT_EQUAL(2, utf8_encode(0xE4, b));
        TEST_ASSERT_EQUAL_MEMORY("\xC3\xA4", b, 2);
        TEST_ASSERT_EQUAL(3, utf8_encode(0x20AC, b));
        TEST_ASSERT_EQUAL_MEMORY("\xE2\x82\xAC", b, 3);
        TEST_ASSERT_EQUAL(4, utf8_encode(0x1F600, b));
        TEST_ASSERT_EQUAL_MEMORY("\xF0\x9F\x98\x80", b, 4);

        TEST_ASSERT_EQUAL(-1, utf8_encode(0xD800, b));
        TEST_ASSERT_EQUAL(-1, utf8_encode(0xDFFF, b));
        TEST_ASSERT_EQUAL(-1, utf8_encode(0x110000, b));
}

extern void test_encode_decode_roundtrip(void)
{
        char b[UTF8_MAX_BYTES];
        u32 cp;
        u32 back;
        s32 len;

        /* Every valid codepoint must survive encode + decode */
        for(cp = 0; cp <= 0x10FFFF; cp++) {
                len = utf8_encode(cp, b);

                if(cp >= 0xD800 && cp <= 0xDFFF) {
                        TEST_ASSERT_EQUAL(-1, len);
                        continue;
                }

                TEST_ASSERT_TRUE(len > 0);
                TEST_ASSERT_EQUAL(len, utf8_decode(b, len, &back));
                TEST_ASSERT_EQUAL_HEX32(cp, back);
        }
}

extern void test_count_validate(void)
{
        TEST_ASSERT_EQUAL(4, utf8_count(MIXED, -1));
        TEST_ASSERT_EQUAL(0, utf8_count("", -1));
        TEST_ASSERT_EQUAL(0, utf8_validate(MIXED, -1));
        /* Cut inside the last codepoint */
        TEST_ASSERT_EQUAL(-1, utf8_count(MIXED, 9));
        TEST_ASSERT_EQUAL(-1, utf8_validate("ab\xFF", -1));
}
