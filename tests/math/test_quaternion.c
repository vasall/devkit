#include "unity.h"

#include <devkit/math/quaternion.h>

#include <math.h>

#define EPS 1e-9
#define PI  3.14159265358979323846

/* Unity is built without double support, so compare by hand */
#define ASSERT_NEAR(expected, actual) \
        TEST_ASSERT_TRUE(fabs((expected) - (actual)) < EPS)

/******************************************************************************
 *
 * 				TEST CASES
 *
 ******************************************************************************/

extern void test_identity_rotation(void);
extern void test_axis_angle_rotates_vector(void);
extern void test_mul_composes_rotations(void);
extern void test_inv(void);
extern void test_to_mat4_matches_mat4_rotation(void);
extern void test_euler_matches_matrix_order(void);
extern void test_from_mat3_roundtrip(void);
extern void test_slerp(void);
extern void test_slerp_shortest_path(void);

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

        RUN_TEST(test_identity_rotation);
        RUN_TEST(test_axis_angle_rotates_vector);
        RUN_TEST(test_mul_composes_rotations);
        RUN_TEST(test_inv);
        RUN_TEST(test_to_mat4_matches_mat4_rotation);
        RUN_TEST(test_euler_matches_matrix_order);
        RUN_TEST(test_from_mat3_roundtrip);
        RUN_TEST(test_slerp);
        RUN_TEST(test_slerp_shortest_path);

        return UNITY_END();
}

/******************************************************************************
 *
 * 				HELPERS
 *
 ******************************************************************************/

static void assert_vec3(Vector3 expected, Vector3 actual)
{
        ASSERT_NEAR(expected.x, actual.x);
        ASSERT_NEAR(expected.y, actual.y);
        ASSERT_NEAR(expected.z, actual.z);
}

/* q and -q are the same rotation */
static void assert_same_rotation(Quaternion expected, Quaternion actual)
{
        ASSERT_NEAR(1.0,
                                  fabs(quat_dot(expected, actual)));
}

static void assert_mat4(Matrix4 expected, Matrix4 actual)
{
        s32 i;
        for(i = 0; i < 16; i++) {
                ASSERT_NEAR(expected.data[i],
                                          actual.data[i]);
        }
}

/******************************************************************************
 *
 * 				TEST FUNCTIONS
 *
 ******************************************************************************/

extern void test_identity_rotation(void)
{
        Vector3 v = vec3(1, 2, 3);
        assert_vec3(v, quat_rotate(quat_identity(), v));
}

extern void test_axis_angle_rotates_vector(void)
{
        /* 90° around z: x -> y */
        Quaternion q = quat_axis_angle(vec3(0, 0, 5), PI / 2);

        ASSERT_NEAR(1.0, quat_mag(q));
        assert_vec3(vec3(0, 1, 0), quat_rotate(q, vec3(1, 0, 0)));

        /* 120° around (1,1,1): x -> y -> z */
        q = quat_axis_angle(vec3(1, 1, 1), 2 * PI / 3);
        assert_vec3(vec3(0, 1, 0), quat_rotate(q, vec3(1, 0, 0)));
        assert_vec3(vec3(0, 0, 1), quat_rotate(q, vec3(0, 1, 0)));
}

extern void test_mul_composes_rotations(void)
{
        Quaternion qx = quat_axis_angle(vec3(1, 0, 0), PI / 2);
        Quaternion qz = quat_axis_angle(vec3(0, 0, 1), PI / 2);
        Vector3 v = vec3(0, 1, 0);

        /* qz * qx applies qx first */
        assert_vec3(quat_rotate(qz, quat_rotate(qx, v)),
                    quat_rotate(quat_mul(qz, qx), v));
}

extern void test_inv(void)
{
        Quaternion q = quat(1, 2, 3, 4);
        Quaternion r = quat_mul(q, quat_inv(q));

        ASSERT_NEAR(1.0, r.w);
        ASSERT_NEAR(0.0, r.x);
        ASSERT_NEAR(0.0, r.y);
        ASSERT_NEAR(0.0, r.z);
}

extern void test_to_mat4_matches_mat4_rotation(void)
{
        f64 a = 0.7;

        assert_mat4(mat4_rotation_x(a),
                    quat_to_mat4(quat_axis_angle(vec3(1, 0, 0), a)));
        assert_mat4(mat4_rotation_y(a),
                    quat_to_mat4(quat_axis_angle(vec3(0, 1, 0), a)));
        assert_mat4(mat4_rotation_z(a),
                    quat_to_mat4(quat_axis_angle(vec3(0, 0, 1), a)));
}

extern void test_euler_matches_matrix_order(void)
{
        f64 x = 0.3, y = -1.1, z = 2.4;
        Matrix4 expected = mat4_mul(mat4_rotation_z(z),
                                    mat4_mul(mat4_rotation_y(y),
                                             mat4_rotation_x(x)));

        assert_mat4(expected, quat_to_mat4(quat_euler(x, y, z)));
}

extern void test_from_mat3_roundtrip(void)
{
        /* Angles chosen to hit each branch of quat_from_mat3 */
        Quaternion qs[4];
        s32 i;

        qs[0] = quat_axis_angle(vec3(1, 2, 3), 0.5);
        qs[1] = quat_axis_angle(vec3(1, 0, 0), 3.0);
        qs[2] = quat_axis_angle(vec3(0, 1, 0), 3.0);
        qs[3] = quat_axis_angle(vec3(0, 0, 1), 3.0);

        for(i = 0; i < 4; i++) {
                assert_same_rotation(qs[i],
                                     quat_from_mat3(quat_to_mat3(qs[i])));
        }
}

extern void test_slerp(void)
{
        Quaternion q1 = quat_identity();
        Quaternion q2 = quat_axis_angle(vec3(0, 0, 1), PI / 2);

        assert_same_rotation(q1, quat_slerp(q1, q2, 0.0));
        assert_same_rotation(q2, quat_slerp(q1, q2, 1.0));
        assert_same_rotation(quat_axis_angle(vec3(0, 0, 1), PI / 4),
                             quat_slerp(q1, q2, 0.5));
}

extern void test_slerp_shortest_path(void)
{
        Quaternion q1 = quat_identity();
        Quaternion q2 = quat_scale(quat_axis_angle(vec3(0, 0, 1), PI / 2),
                                   -1.0);

        assert_same_rotation(quat_axis_angle(vec3(0, 0, 1), PI / 4),
                             quat_slerp(q1, q2, 0.5));
}
