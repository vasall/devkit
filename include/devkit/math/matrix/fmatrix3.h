#ifndef VASALL_DEVKIT_FMATRIX3_H
#define VASALL_DEVKIT_FMATRIX3_H

#include <devkit/scope.h>
#include <devkit/types.h>

#include <devkit/math/matrix/matrix3.h>

#include <devkit/math/vector/fvector3.h>

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
typedef struct FMatrix3 {
        f32 data[9];
} FMatrix3;

PUB FMatrix3 fmat3(FVector3 v0, FVector3 v1, FVector3 v2);
PUB FMatrix3 fmat3_zero(void);
PUB FMatrix3 fmat3_identity(void);
PUB FMatrix3 fmat3_set(f32 value);

/* ret_vec = m[col] */
PUB FVector3 fmat3_col(FMatrix3 m, s32 col);

/* ret = m[col][row] */
PUB f32 fmat3_at(FMatrix3 m, s32 col, s32 row);

/* m_ret = m1 + m2 */
PUB FMatrix3 fmat3_add(FMatrix3 m1, FMatrix3 m2);

/* m_ret = m1 - m2 */
PUB FMatrix3 fmat3_sub(FMatrix3 m1, FMatrix3 m2);

/* m_ret = m * scalar */
PUB FMatrix3 fmat3_scale(FMatrix3 m, f32 scalar);

/* m_ret = m1 * m2 */
PUB FMatrix3 fmat3_mul(FMatrix3 m1, FMatrix3 m2);

/* m_ret = transpose(m) */
PUB FMatrix3 fmat3_trans(FMatrix3 m);

/* m_ret = determinant(m) */
PUB f32 fmat3_det(FMatrix3 m);

/* m_ret = inverse(m) */
PUB FMatrix3 fmat3_inv(FMatrix3 m);

/* ret_v = m * v */
PUB FVector3 fmat3_xfm(FMatrix3 m, FVector3 v);

/* Convert between f64 and f32. Converting to f32 loses precision */
PUB FMatrix3 fmat3_from_mat3(Matrix3 m);
PUB Matrix3 mat3_from_fmat3(FMatrix3 m);

#endif /* VASALL_DEVKIT_FMATRIX3_H */
