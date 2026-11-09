#ifndef VASALL_DEVKIT_MATRIX4_H
#define VASALL_DEVKIT_MATRIX4_H

#include <devkit/scope.h>
#include <devkit/types.h>

#include <devkit/math/vector/vector3.h>
#include <devkit/math/vector/vector4.h>

/*
 * Column-major 4×4 matrix layout:
 *
 *   v0   v1   v2   v3
 * | m00  m10  m20  m30 |
 * | m01  m11  m21  m31 |
 * | m02  m12  m22  m32 |
 * | m03  m13  m23  m33 |
 *
 * data[16] = {
 *     m00, m01, m02, m03,  // v0
 *     m10, m11, m12, m13,  // v1
 *     m20, m21, m22, m23,  // v2
 *     m30, m31, m32, m33,  // v3
 * };
 */
typedef struct Matrix4 {
        f64 data[16];
} Matrix4;

PUB Matrix4 mat4(Vector4 v0, Vector4 v1, Vector4 v2, Vector4 v3);
PUB Matrix4 mat4_zero(void);
PUB Matrix4 mat4_identity(void);
PUB Matrix4 mat4_set(f64 value);

/* ret_vec = m[col] */
PUB Vector4 mat4_col(Matrix4 m, s32 col);

/* ret = m[col][row] */
PUB f64 mat4_at(Matrix4 mat, s32 col, s32 row);

/* ret_m = m1 + m2 */
PUB Matrix4 mat4_add(Matrix4 m1, Matrix4 m2);

/* ret_m = m1 - m2 */
PUB Matrix4 mat4_sub(Matrix4 m1, Matrix4 m2);

/* ret_m = m * scalar */
PUB Matrix4 mat4_scale(Matrix4 m, f64 scalar);

/* ret_m = m1 * m2 */
PUB Matrix4 mat4_mul(Matrix4 m1, Matrix4 m2);

/* ret_m = transpose(m) */
PUB Matrix4 mat4_trans(Matrix4 m);

/* ret_m = determinant(m) */
PUB f64 mat4_det(Matrix4 m);

/* ret_m = inverse(m) */
PUB Matrix4 mat4_inv(Matrix4 m);

/* ret_v = m * v */
PUB Vector4 mat4_xfm(Matrix4 m, Vector4 v);

PUB Matrix4 mat4_translation(Vector4 v);
PUB Matrix4 mat4_scaling(f64 scalar);

PUB Matrix4 mat4_rotation(Vector3 axis, f64 rad);
PUB Matrix4 mat4_rotation_x(f64 rad);
PUB Matrix4 mat4_rotation_y(f64 rad);
PUB Matrix4 mat4_rotation_z(f64 rad);

#endif /* VASALL_DEVKIT_MATRIX4_H */
