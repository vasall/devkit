#ifndef VASALL_DEVKIT_FMATRIX4_H
#define VASALL_DEVKIT_FMATRIX4_H

#include <devkit/scope.h>
#include <devkit/types.h>

#include <devkit/math/matrix/matrix4.h>

#include <devkit/math/vector/fvector3.h>
#include <devkit/math/vector/fvector4.h>

/**
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
typedef struct FMatrix4 {
        f32 data[16];
} FMatrix4;

PUB FMatrix4 fmat4(FVector4 v0, FVector4 v1, FVector4 v2, FVector4 v3);
PUB FMatrix4 fmat4_zero(void);
PUB FMatrix4 fmat4_identity(void);
PUB FMatrix4 fmat4_set(f32 value);

/* ret_vec = m[col] */
PUB FVector4 fmat4_col(FMatrix4 m, s32 col);

/* ret = m[col][row] */
PUB f32 fmat4_at(FMatrix4 mat, s32 col, s32 row);

/* ret_m = m1 + m2 */
PUB FMatrix4 fmat4_add(FMatrix4 m1, FMatrix4 m2);

/* ret_m = m1 - m2 */
PUB FMatrix4 fmat4_sub(FMatrix4 m1, FMatrix4 m2);

/* ret_m = m * scalar */
PUB FMatrix4 fmat4_scale(FMatrix4 m, f32 scalar);

/* ret_m = m1 * m2 */
PUB FMatrix4 fmat4_mul(FMatrix4 m1, FMatrix4 m2);

/* ret_m = transpose(m) */
PUB FMatrix4 fmat4_trans(FMatrix4 m);

/* ret_m = determinant(m) */
PUB f32 fmat4_det(FMatrix4 m);

/* ret_m = inverse(m) */
PUB FMatrix4 fmat4_inv(FMatrix4 m);

/* ret_v = m * v */
PUB FVector4 fmat4_xfm(FMatrix4 m, FVector4 v);

PUB FMatrix4 fmat4_translation(FVector4 v);
PUB FMatrix4 fmat4_scaling(f32 scalar);

PUB FMatrix4 fmat4_rotation(FVector3 axis, f32 rad);
PUB FMatrix4 fmat4_rotation_x(f32 rad);
PUB FMatrix4 fmat4_rotation_y(f32 rad);
PUB FMatrix4 fmat4_rotation_z(f32 rad);

/* Convert between f64 and f32. Converting to f32 loses precision */
PUB FMatrix4 fmat4_from_mat4(Matrix4 m);
PUB Matrix4 mat4_from_fmat4(FMatrix4 m);

#endif /* VASALL_DEVKIT_FMATRIX4_H */
