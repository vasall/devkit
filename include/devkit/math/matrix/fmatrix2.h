#ifndef VASALL_DEVKIT_FMATRIX2_H
#define VASALL_DEVKIT_FMATRIX2_H

#include <devkit/scope.h>
#include <devkit/types.h>

#include <devkit/math/matrix/matrix2.h>

#include <devkit/math/vector/fvector2.h>

/**
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
typedef struct FMatrix2 {
        f32 data[4];
} FMatrix2;

PUB FMatrix2 fmat2(FVector2 v0, FVector2 v1);
PUB FMatrix2 fmat2_zero(void);
PUB FMatrix2 fmat2_identity(void);
PUB FMatrix2 fmat2_set(f32 value);

/* ret_vec = m[col] */
PUB FVector2 fmat2_col(FMatrix2 m, s32 col);

/* ret = m[col][row] */
PUB f32 fmat2_at(FMatrix2 m, s32 col, s32 row);

/* m_ret = m1 + m2 */
PUB FMatrix2 fmat2_add(FMatrix2 m1, FMatrix2 m2);

/* m_ret = m1 - m2 */
PUB FMatrix2 fmat2_sub(FMatrix2 m1, FMatrix2 m2);

/* m_ret = m * scalar */
PUB FMatrix2 fmat2_scale(FMatrix2 m, f32 scalar);

/* m_ret = m1 * m2 */
PUB FMatrix2 fmat2_mul(FMatrix2 m1, FMatrix2 m2);

/* m_ret = transpose(m) */
PUB FMatrix2 fmat2_trans(FMatrix2 m);

/* m_ret = determinant(m) */
PUB f32 fmat2_det(FMatrix2 m);

/* m_ret = inverse(m) */
PUB FMatrix2 fmat2_inv(FMatrix2 m);

/* ret_v = m * v */
PUB FVector2 fmat2_xfm(FMatrix2 m, FVector2 v);

/* Convert between f64 and f32. Converting to f32 loses precision */
PUB FMatrix2 fmat2_from_mat2(Matrix2 m);
PUB Matrix2 mat2_from_fmat2(FMatrix2 m);

#endif /* VASALL_DEVKIT_FMATRIX2_H */
