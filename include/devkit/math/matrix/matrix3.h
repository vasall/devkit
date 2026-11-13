#ifndef VASALL_DEVKIT_MATRIX3_H
#define VASALL_DEVKIT_MATRIX3_H

#include <devkit/scope.h>
#include <devkit/types.h>

#include <devkit/math/vector/vector3.h>

/**
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

#endif /* VASALL_DEVKIT_MATRIX3_H */
