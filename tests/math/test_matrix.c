#include "unity.h"

#include <devkit/math/matrix.h>

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

extern void test_mat2_det_inv(void);
extern void test_mat2_mul_xfm(void);
extern void test_mat3_det_inv(void);
extern void test_mat3_mul_xfm(void);
extern void test_mat4_scale(void);
extern void test_mat4_det(void);
extern void test_mat4_inv(void);
extern void test_mat4_mul_trans(void);
extern void test_mat4_translation_scaling(void);
extern void test_mat4_rotation_axes(void);
extern void test_mat4_rotation_arbitrary_axis(void);

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

        RUN_TEST(test_mat2_det_inv);
        RUN_TEST(test_mat2_mul_xfm);
        RUN_TEST(test_mat3_det_inv);
        RUN_TEST(test_mat3_mul_xfm);
        RUN_TEST(test_mat4_scale);
        RUN_TEST(test_mat4_det);
        RUN_TEST(test_mat4_inv);
        RUN_TEST(test_mat4_mul_trans);
        RUN_TEST(test_mat4_translation_scaling);
        RUN_TEST(test_mat4_rotation_axes);
        RUN_TEST(test_mat4_rotation_arbitrary_axis);

        return UNITY_END();
}

/******************************************************************************
 *
 * 				HELPERS
 *
 ******************************************************************************/

static void assert_data(const f64 *e, const f64 *a, s32 n)
{
        s32 i;
        for(i = 0; i < n; i++) {
                ASSERT_NEAR(e[i], a[i]);
        }
}

/* C89 can't take .data of a returned struct, so pass matrices by value */
static void assert_mat2(Matrix2 e, Matrix2 a) { assert_data(e.data, a.data, 4); }
static void assert_mat3(Matrix3 e, Matrix3 a) { assert_data(e.data, a.data, 9); }
static void assert_mat4(Matrix4 e, Matrix4 a) { assert_data(e.data, a.data, 16); }

static void assert_vec4(Vector4 e, Vector4 a)
{
        ASSERT_NEAR(e.x, a.x);
        ASSERT_NEAR(e.y, a.y);
        ASSERT_NEAR(e.z, a.z);
        ASSERT_NEAR(e.w, a.w);
}

/* Non-symmetric matrix with det = -32 (checked by hand) */
static Matrix4 sample_mat4(void)
{
        return mat4(vec4(2, 0, 1, 3),
                    vec4(1, 1, 0, 2),
                    vec4(0, 3, 1, 1),
                    vec4(4, 1, 2, 0));
}

/******************************************************************************
 *
 * 				TEST FUNCTIONS
 *
 ******************************************************************************/

extern void test_mat2_det_inv(void)
{
        Matrix2 m = mat2(vec2(4, 2), vec2(7, 6));
        Matrix2 id = mat2_identity();

        ASSERT_NEAR(10.0, mat2_det(m));
        assert_mat2(id, mat2_mul(m, mat2_inv(m)));
}

extern void test_mat2_mul_xfm(void)
{
        /* columns (1,3), (2,4) = rows [1 2; 3 4] */
        Matrix2 m = mat2(vec2(1, 3), vec2(2, 4));
        Vector2 v = mat2_xfm(m, vec2(5, 6));

        ASSERT_NEAR(17.0, v.x);
        ASSERT_NEAR(39.0, v.y);
        ASSERT_NEAR(3.0, mat2_at(m, 0, 1));
}

extern void test_mat3_det_inv(void)
{
        Matrix3 m = mat3(vec3(2, 0, 1), vec3(1, 3, 2), vec3(1, 1, 2));
        Matrix3 id = mat3_identity();

        ASSERT_NEAR(6.0, mat3_det(m));
        assert_mat3(id, mat3_mul(m, mat3_inv(m)));
        assert_mat3(id, mat3_mul(mat3_inv(m), m));
}

extern void test_mat3_mul_xfm(void)
{
        Matrix3 a = mat3(vec3(2, 0, 1), vec3(1, 3, 2), vec3(1, 1, 1));
        Matrix3 b = mat3(vec3(0, 1, 2), vec3(3, 0, 1), vec3(1, 1, 0));
        Vector3 v = vec3(1, -2, 3);
        Vector3 r1 = mat3_xfm(mat3_mul(a, b), v);
        Vector3 r2 = mat3_xfm(a, mat3_xfm(b, v));

        ASSERT_NEAR(r2.x, r1.x);
        ASSERT_NEAR(r2.y, r1.y);
        ASSERT_NEAR(r2.z, r1.z);
}

extern void test_mat4_scale(void)
{
        Matrix4 m = mat4_scale(mat4_set(1.5), 2);
        Matrix4 e = mat4_set(3);

        assert_mat4(e, m);
}

extern void test_mat4_det(void)
{
        /* swapping two rows of identity flips the sign */
        Matrix4 swap = mat4(vec4(0, 1, 0, 0), vec4(1, 0, 0, 0),
                            vec4(0, 0, 1, 0), vec4(0, 0, 0, 1));

        ASSERT_NEAR(-32.0, mat4_det(sample_mat4()));
        ASSERT_NEAR(-32.0, mat4_det(mat4_trans(sample_mat4())));
        ASSERT_NEAR(-1.0, mat4_det(swap));
        ASSERT_NEAR(1.0, mat4_det(mat4_identity()));
}

extern void test_mat4_inv(void)
{
        Matrix4 m = sample_mat4();
        Matrix4 id = mat4_identity();

        assert_mat4(id, mat4_mul(m, mat4_inv(m)));
        assert_mat4(id, mat4_mul(mat4_inv(m), m));
}

extern void test_mat4_mul_trans(void)
{
        Matrix4 a = sample_mat4();
        Matrix4 b = mat4_rotation_z(0.4);
        Vector4 v = vec4(1, 2, 3, 1);

        assert_vec4(mat4_xfm(a, mat4_xfm(b, v)), mat4_xfm(mat4_mul(a, b), v));
        assert_mat4(mat4_trans(mat4_mul(a, b)),
                    mat4_mul(mat4_trans(b), mat4_trans(a)));
}

extern void test_mat4_translation_scaling(void)
{
        Vector4 p = vec4(1, 2, 3, 1);

        assert_vec4(vec4(11, 22, 33, 1),
                    mat4_xfm(mat4_translation(vec4(10, 20, 30, 1)), p));
        assert_vec4(vec4(2, 4, 6, 1), mat4_xfm(mat4_scaling(2), p));
}

extern void test_mat4_rotation_axes(void)
{
        f64 a = 3.14159265358979323846 / 2;

        /* counter-clockwise: y -> z, z -> x, x -> y */
        assert_vec4(vec4(0, 0, 1, 1),
                    mat4_xfm(mat4_rotation_x(a), vec4(0, 1, 0, 1)));
        assert_vec4(vec4(1, 0, 0, 1),
                    mat4_xfm(mat4_rotation_y(a), vec4(0, 0, 1, 1)));
        assert_vec4(vec4(0, 1, 0, 1),
                    mat4_xfm(mat4_rotation_z(a), vec4(1, 0, 0, 1)));
}

extern void test_mat4_rotation_arbitrary_axis(void)
{
        f64 a = 0.9;

        assert_mat4(mat4_rotation_x(a),
                    mat4_rotation(vec3(2, 0, 0), a));
        assert_mat4(mat4_rotation_y(a),
                    mat4_rotation(vec3(0, 3, 0), a));
        assert_mat4(mat4_rotation_z(a),
                    mat4_rotation(vec3(0, 0, 1), a));

        /* 120° around (1,1,1): x -> y */
        assert_vec4(vec4(0, 1, 0, 1),
                    mat4_xfm(mat4_rotation(vec3(1, 1, 1),
                                           2 * 3.14159265358979323846 / 3),
                             vec4(1, 0, 0, 1)));
}
