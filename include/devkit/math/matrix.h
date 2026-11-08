#ifndef VASALL_DEVKIT_MATRIX_H
#define VASALL_DEVKIT_MATRIX_H

#include <devkit/scope.h>
#include <devkit/types.h>

#include <devkit/math/vector.h>

/****************************** MATRIX 2x2 ************************************/

/*
 * Column-major 2×2 matrix layout:
 *
 *   v0   v1
 * | m00  m10 |
 * | m01  m11 |
 *
 * data[4] = {
 *     m00, m01,  // v0
 *     m10, m11,  // v1
 * };
 */
typedef struct Matrix2 {
        f64 data[4];
} Matrix2;

PUB Matrix2 mat2(Vector2 v0, Vector2 v1);
PUB Matrix2 mat2_zero(void);
PUB Matrix2 mat2_identity(void);
PUB Matrix2 mat2_set(f64 value);

/* ret_vec = m[col] */
PUB Vector2 mat2_col(Matrix2 m, s32 col);

/* ret = m[col][row] */
PUB f64 mat2_at(Matrix2 m, s32 col, s32 row);

/* m_ret = m1 + m2 */
PUB Matrix2 mat2_add(Matrix2 m1, Matrix2 m2);

/* m_ret = m1 - m2 */
PUB Matrix2 mat2_sub(Matrix2 m1, Matrix2 m2);

/* m_ret = m * scalar */
PUB Matrix2 mat2_scale(Matrix2 m, f64 scalar);

/* m_ret = m1 * m2 */
PUB Matrix2 mat2_mul(Matrix2 m1, Matrix2 m2);

/* m_ret = transpose(m) */
PUB Matrix2 mat2_trans(Matrix2 m);

/* m_ret = determinant(m) */
PUB f64 mat2_det(Matrix2 m);

/* m_ret = inverse(m) */
PUB Matrix2 mat2_inv(Matrix2 m);

/* ret_v = m * v */
PUB Vector2 mat2_xfm(Matrix2 m, Vector2 v);

/****************************** MATRIX 3x3 ************************************/

/*
 * Column-major 3×3 matrix layout:
 *
 *   v0   v1   v2
 * | m00  m10  m20 |
 * | m01  m11  m21 |
 * | m02  m12  m22 |
 *
 * data[9] = {
 *     m00, m01, m02,  // v0
 *     m10, m11, m12,  // v1
 *     m20, m21, m22,  // v2
 * };
 */
typedef struct Matrix3 {
        f64 data[9];
} Matrix3;

PUB Matrix3 mat3(Vector3 v0, Vector3 v1, Vector3 v2);
PUB Matrix3 mat3_zero(void);
PUB Matrix3 mat3_identity(void);
PUB Matrix3 mat3_set(f64 value);

/* ret_vec = m[col] */
PUB Vector3 mat3_col(Matrix3 m, s32 col);

/* ret = m[col][row] */
PUB f64 mat3_at(Matrix3 m, s32 col, s32 row);

/* m_ret = m1 + m2 */
PUB Matrix3 mat3_add(Matrix3 m1, Matrix3 m2);

/* m_ret = m1 - m2 */
PUB Matrix3 mat3_sub(Matrix3 m1, Matrix3 m2);

/* m_ret = m * scalar */
PUB Matrix3 mat3_scale(Matrix3 m, f64 scalar);

/* m_ret = m1 * m2 */
PUB Matrix3 mat3_mul(Matrix3 m1, Matrix3 m2);

/* m_ret = transpose(m) */
PUB Matrix3 mat3_trans(Matrix3 m);

/* m_ret = determinant(m) */
PUB f64 mat3_det(Matrix3 m);

/* m_ret = inverse(m) */
PUB Matrix3 mat3_inv(Matrix3 m);

/* ret_v = m * v */
PUB Vector3 mat3_xfm(Matrix3 m, Vector3 v);

/****************************** MATRIX 4x4 ************************************/

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

#endif /* VASALL_DEVKIT_MATRIX_H */
