#include "unity.h"

#include <devkit/math/vector.h>

#include <math.h>

#define EPS 1e-9

/* Unity is built without double support, so compare by hand */
#define ASSERT_NEAR(expected, actual) \
        TEST_ASSERT_TRUE(fabs((expected) - (actual)) < EPS)

/******************************************************************************
 *
 * 				TEST CASES
 *
 ******************************************************************************/

extern void test_vec2_basic(void);
extern void test_vec2_dot(void);
extern void test_vec2_norm(void);
extern void test_vec2_clamp(void);
extern void test_vec2_lerp(void);

extern void test_vec3_basic(void);
extern void test_vec3_dot_cross(void);
extern void test_vec3_norm(void);
extern void test_vec3_clamp(void);
extern void test_vec3_lerp(void);

extern void test_vec4_basic(void);
extern void test_vec4_scale(void);
extern void test_vec4_dot(void);
extern void test_vec4_norm(void);
extern void test_vec4_clamp(void);
extern void test_vec4_lerp(void);

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

        RUN_TEST(test_vec2_basic);
        RUN_TEST(test_vec2_dot);
        RUN_TEST(test_vec2_norm);
        RUN_TEST(test_vec2_clamp);
        RUN_TEST(test_vec2_lerp);

        RUN_TEST(test_vec3_basic);
        RUN_TEST(test_vec3_dot_cross);
        RUN_TEST(test_vec3_norm);
        RUN_TEST(test_vec3_clamp);
        RUN_TEST(test_vec3_lerp);

        RUN_TEST(test_vec4_basic);
        RUN_TEST(test_vec4_scale);
        RUN_TEST(test_vec4_dot);
        RUN_TEST(test_vec4_norm);
        RUN_TEST(test_vec4_clamp);
        RUN_TEST(test_vec4_lerp);

        return UNITY_END();
}

/******************************************************************************
 *
 * 				HELPERS
 *
 ******************************************************************************/

static void assert_vec2(Vector2 e, Vector2 a)
{
        ASSERT_NEAR(e.x, a.x);
        ASSERT_NEAR(e.y, a.y);
}

static void assert_vec3(Vector3 e, Vector3 a)
{
        ASSERT_NEAR(e.x, a.x);
        ASSERT_NEAR(e.y, a.y);
        ASSERT_NEAR(e.z, a.z);
}

static void assert_vec4(Vector4 e, Vector4 a)
{
        ASSERT_NEAR(e.x, a.x);
        ASSERT_NEAR(e.y, a.y);
        ASSERT_NEAR(e.z, a.z);
        ASSERT_NEAR(e.w, a.w);
}

/******************************************************************************
 *
 * 				TEST FUNCTIONS
 *
 ******************************************************************************/

/******************************** VECTOR2 *************************************/

extern void test_vec2_basic(void)
{
        Vector2 a = vec2(1, 2);
        Vector2 b = vec2(3, -5);

        assert_vec2(vec2(0, 0), vec2_zero());
        assert_vec2(vec2(7, 7), vec2_set(7));
        assert_vec2(vec2(4, -3), vec2_add(a, b));
        assert_vec2(vec2(-2, 7), vec2_sub(a, b));
        assert_vec2(vec2(3, 6), vec2_scale(a, 3));
        ASSERT_NEAR(5.0, vec2_mag(vec2(3, 4)));
        ASSERT_NEAR(25.0, vec2_mag_sqr(vec2(3, 4)));
}

extern void test_vec2_dot(void)
{
        ASSERT_NEAR(0.0, vec2_dot(vec2(1, 0), vec2(0, 1)));
        ASSERT_NEAR(-7.0, vec2_dot(vec2(1, 2), vec2(3, -5)));
}

extern void test_vec2_norm(void)
{
        assert_vec2(vec2(0.6, 0.8), vec2_norm(vec2(3, 4)));
        assert_vec2(vec2_zero(), vec2_norm(vec2_zero()));
}

extern void test_vec2_clamp(void)
{
        assert_vec2(vec2(1.2, 1.6), vec2_clamp(vec2(3, 4), 0, 2));
        assert_vec2(vec2(6, 8), vec2_clamp(vec2(3, 4), 10, 20));
        assert_vec2(vec2(3, 4), vec2_clamp(vec2(3, 4), 1, 10));
        assert_vec2(vec2_zero(), vec2_clamp(vec2_zero(), 1, 2));
}

extern void test_vec2_lerp(void)
{
        Vector2 a = vec2(1, 2);
        Vector2 b = vec2(3, -6);

        assert_vec2(a, vec2_lerp(a, b, 0));
        assert_vec2(b, vec2_lerp(a, b, 1));
        assert_vec2(vec2(2, -2), vec2_lerp(a, b, 0.5));
        assert_vec2(a, vec2_lerp(a, a, 0.5));
}

/******************************** VECTOR3 *************************************/

extern void test_vec3_basic(void)
{
        Vector3 a = vec3(1, 2, 3);
        Vector3 b = vec3(-4, 5, 0.5);

        assert_vec3(vec3(0, 0, 0), vec3_zero());
        assert_vec3(vec3(2, 2, 2), vec3_set(2));
        assert_vec3(vec3(-3, 7, 3.5), vec3_add(a, b));
        assert_vec3(vec3(5, -3, 2.5), vec3_sub(a, b));
        assert_vec3(vec3(-1, -2, -3), vec3_scale(a, -1));
        ASSERT_NEAR(3.0, vec3_mag(vec3(1, 2, 2)));
        ASSERT_NEAR(9.0, vec3_mag_sqr(vec3(1, 2, 2)));
}

extern void test_vec3_dot_cross(void)
{
        ASSERT_NEAR(7.5, vec3_dot(vec3(1, 2, 3), vec3(-4, 5, 0.5)));
        assert_vec3(vec3(0, 0, 1), vec3_cross(vec3(1, 0, 0), vec3(0, 1, 0)));
        assert_vec3(vec3(1, 0, 0), vec3_cross(vec3(0, 1, 0), vec3(0, 0, 1)));
        assert_vec3(vec3(0, 1, 0), vec3_cross(vec3(0, 0, 1), vec3(1, 0, 0)));
}

extern void test_vec3_norm(void)
{
        assert_vec3(vec3(1.0 / 3, 2.0 / 3, 2.0 / 3), vec3_norm(vec3(1, 2, 2)));
        assert_vec3(vec3_zero(), vec3_norm(vec3_zero()));
}

extern void test_vec3_clamp(void)
{
        assert_vec3(vec3(0.5, 1, 1), vec3_clamp(vec3(1, 2, 2), 0, 1.5));
        assert_vec3(vec3(2, 4, 4), vec3_clamp(vec3(1, 2, 2), 6, 10));
        assert_vec3(vec3_zero(), vec3_clamp(vec3_zero(), 1, 2));
}

extern void test_vec3_lerp(void)
{
        Vector3 a = vec3(0, 0, 0);
        Vector3 b = vec3(4, -8, 2);

        assert_vec3(a, vec3_lerp(a, b, 0));
        assert_vec3(b, vec3_lerp(a, b, 1));
        assert_vec3(vec3(1, -2, 0.5), vec3_lerp(a, b, 0.25));
}

/******************************** VECTOR4 *************************************/

extern void test_vec4_basic(void)
{
        Vector4 a = vec4(1, 2, 3, 4);
        Vector4 b = vec4(4, 3, 2, 1);

        assert_vec4(vec4(0, 0, 0, 0), vec4_zero());
        assert_vec4(vec4(3, 3, 3, 3), vec4_set(3));
        assert_vec4(vec4(5, 5, 5, 5), vec4_add(a, b));
        assert_vec4(vec4(-3, -1, 1, 3), vec4_sub(a, b));
        ASSERT_NEAR(2.0, vec4_mag(vec4(1, 1, 1, 1)));
        ASSERT_NEAR(4.0, vec4_mag_sqr(vec4(1, 1, 1, 1)));
}

extern void test_vec4_scale(void)
{
        assert_vec4(vec4(2, 4, 6, 8), vec4_scale(vec4(1, 2, 3, 4), 2));
}

extern void test_vec4_dot(void)
{
        ASSERT_NEAR(20.0, vec4_dot(vec4(1, 2, 3, 4), vec4(4, 3, 2, 1)));
}

extern void test_vec4_norm(void)
{
        assert_vec4(vec4(0.5, 0.5, 0.5, 0.5), vec4_norm(vec4(2, 2, 2, 2)));
        assert_vec4(vec4_zero(), vec4_norm(vec4_zero()));
}

extern void test_vec4_clamp(void)
{
        assert_vec4(vec4(0.5, 0.5, 0.5, 0.5),
                    vec4_clamp(vec4(2, 2, 2, 2), 0, 1));
        assert_vec4(vec4_zero(), vec4_clamp(vec4_zero(), 1, 2));
}

extern void test_vec4_lerp(void)
{
        Vector4 a = vec4(1, 1, 1, 1);
        Vector4 b = vec4(3, 5, -1, 1);

        assert_vec4(a, vec4_lerp(a, b, 0));
        assert_vec4(b, vec4_lerp(a, b, 1));
        assert_vec4(vec4(2, 3, 0, 1), vec4_lerp(a, b, 0.5));
}
