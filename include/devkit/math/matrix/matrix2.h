#ifndef VASALL_DEVKIT_MATRIX2_H
#define VASALL_DEVKIT_MATRIX2_H

#include <devkit/scope.h>
#include <devkit/types.h>

#include <devkit/math/vector/vector2.h>

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

#endif /* VASALL_DEVKIT_MATRIX2_H */
