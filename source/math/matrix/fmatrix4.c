#include <devkit/math/matrix/fmatrix4.h>
#include <devkit/math/matrix/fmatrix3.h>

#include <string.h>
#include <math.h>

PUB FMatrix4 fmat4(FVector4 v0, FVector4 v1, FVector4 v2, FVector4 v3)
{
        FMatrix4 m;

        m.data[0] = v0.x;
        m.data[1] = v0.y;
        m.data[2] = v0.z;
        m.data[3] = v0.w;

        m.data[4] = v1.x;
        m.data[5] = v1.y;
        m.data[6] = v1.z;
        m.data[7] = v1.w;

        m.data[8] = v2.x;
        m.data[9] = v2.y;
        m.data[10] = v2.z;
        m.data[11] = v2.w;

        m.data[12] = v3.x;
        m.data[13] = v3.y;
        m.data[14] = v3.z;
        m.data[15] = v3.w;

        return m;
}

PUB FMatrix4 fmat4_zero(void)
{
        FMatrix4 m;
        memset(m.data, 0, sizeof(FMatrix4));
        return m;
}

PUB FMatrix4 fmat4_identity(void)
{
        FMatrix4 m = fmat4_zero();
        m.data[ 0] = 1;
        m.data[ 5] = 1;
        m.data[10] = 1;
        m.data[15] = 1;
        return m;
}

PUB FMatrix4 fmat4_set(f32 value)
{
        FMatrix4 m;
        s32 i;

        for(i = 0; i < 16; i++) {
                m.data[i] = value;
        }

        return m;
}

PUB FVector4 fmat4_col(FMatrix4 m, s32 col)
{
        FVector4 v;
        v.x = m.data[col * 4 + 0];
        v.y = m.data[col * 4 + 1];
        v.z = m.data[col * 4 + 2];
        v.w = m.data[col * 4 + 3];
        return v;
}

PUB f32 fmat4_at(FMatrix4 mat, s32 col, s32 row)
{
        return mat.data[col * 4 + row];
}

PUB FMatrix4 fmat4_add(FMatrix4 m1, FMatrix4 m2)
{
        FMatrix4 m;
        s32 i;

        for(i = 0; i < 16; i++) {
                m.data[i] = m1.data[i] + m2.data[i];
        }

        return m;
}

PUB FMatrix4 fmat4_sub(FMatrix4 m1, FMatrix4 m2)
{
        FMatrix4 m;
        s32 i;

        for(i = 0; i < 16; i++) {
                m.data[i] = m1.data[i] - m2.data[i];
        }

        return m;
}

PUB FMatrix4 fmat4_scale(FMatrix4 m, f32 scalar)
{
        FMatrix4 res;
        s32 i;

        for(i = 0; i < 16; i++) {
                res.data[i] = m.data[i] * scalar;
        }

        return res;
}

PUB FMatrix4 fmat4_mul(FMatrix4 m1, FMatrix4 m2)
{
        FMatrix4 result;
        s32 row;
        s32 col;

        for (col = 0; col < 4; ++col)
        {
                for (row = 0; row < 4; ++row)
                {
                        result.data[row + col * 4] =
                            m1.data[row + 0 * 4] * m2.data[0 + col * 4] +
                            m1.data[row + 1 * 4] * m2.data[1 + col * 4] +
                            m1.data[row + 2 * 4] * m2.data[2 + col * 4] +
                            m1.data[row + 3 * 4] * m2.data[3 + col * 4];
                }
        }

        return result;
}

PUB FMatrix4 fmat4_trans(FMatrix4 m)
{
        FMatrix4 result;

        result.data[ 0] = m.data[ 0];
        result.data[ 1] = m.data[ 4];
        result.data[ 2] = m.data[ 8];
        result.data[ 3] = m.data[12];

        result.data[ 4] = m.data[ 1];
        result.data[ 5] = m.data[ 5];
        result.data[ 6] = m.data[ 9];
        result.data[ 7] = m.data[13];

        result.data[ 8] = m.data[ 2];
        result.data[ 9] = m.data[ 6];
        result.data[10] = m.data[10];
        result.data[11] = m.data[14];

        result.data[12] = m.data[ 3];
        result.data[13] = m.data[ 7];
        result.data[14] = m.data[11];
        result.data[15] = m.data[15];

        return result;
}

PUB f32 fmat4_det(FMatrix4 m)
{
        FMatrix3 minor;
        f32 d0;
        f32 d1;
        f32 d2;
        f32 d3;

        minor = fmat3(
            fvec3(m.data[5],  m.data[6],  m.data[7]),
            fvec3(m.data[9],  m.data[10], m.data[11]),
            fvec3(m.data[13], m.data[14], m.data[15])
        );
        d0 = fmat3_det(minor);

        minor = fmat3(
            fvec3(m.data[4],  m.data[6],  m.data[7]),
            fvec3(m.data[8],  m.data[10], m.data[11]),
            fvec3(m.data[12], m.data[14], m.data[15])
        );
        d1 = fmat3_det(minor);

        minor = fmat3(
            fvec3(m.data[4],  m.data[5],  m.data[7]),
            fvec3(m.data[8],  m.data[9],  m.data[11]),
            fvec3(m.data[12], m.data[13], m.data[15])
        );
        d2 = fmat3_det(minor);

        minor = fmat3(
            fvec3(m.data[4],  m.data[5],  m.data[6]),
            fvec3(m.data[8],  m.data[9],  m.data[10]),
            fvec3(m.data[12], m.data[13], m.data[14])
        );
        d3 = fmat3_det(minor);

        /* Expansion along column 0: each minor drops column 0 and row i */
        return
            m.data[0] * d0 -
            m.data[1] * d1 +
            m.data[2] * d2 -
            m.data[3] * d3;
}

PUB FMatrix4 fmat4_inv(FMatrix4 m)
{
        FMatrix4 cof;
        FMatrix4 adj;
        FMatrix4 result;

        f32 det;
        s32 row;
        s32 col;

        det = fmat4_det(m);

        for(col = 0; col < 4; col++) {
                for(row = 0; row < 4; row++) {
                        FMatrix3 minor;
                        f32 values[9];
                        s32 mcol;
                        s32 mrow;
                        s32 index;

                        index = 0;

                        for(mcol = 0; mcol < 4; mcol++) {
                                if(mcol == col) {
                                        continue;
                                }

                                for(mrow = 0; mrow < 4; mrow++) {
                                        if(mrow == row) {
                                                continue;
                                        }

                                        values[index++] =
                                            m.data[mrow + mcol * 4];
                                }
                        }

                        minor.data[0] = values[0];
                        minor.data[1] = values[1];
                        minor.data[2] = values[2];
                        minor.data[3] = values[3];
                        minor.data[4] = values[4];
                        minor.data[5] = values[5];
                        minor.data[6] = values[6];
                        minor.data[7] = values[7];
                        minor.data[8] = values[8];

                        cof.data[row + col * 4] =
                            (((row + col) & 1) ? -1.0f : 1.0f) *
                            fmat3_det(minor);
                }
        }

        adj = fmat4_trans(cof);

        for(row = 0; row < 16; row++) {
                result.data[row] = adj.data[row] / det;
        }

        return result;
}

PUB FVector4 fmat4_xfm(FMatrix4 m, FVector4 v)
{
        FVector4 result;

        result.x =
            m.data[0]  * v.x +
            m.data[4]  * v.y +
            m.data[8]  * v.z +
            m.data[12] * v.w;

        result.y =
            m.data[1]  * v.x +
            m.data[5]  * v.y +
            m.data[9]  * v.z +
            m.data[13] * v.w;

        result.z =
            m.data[2]  * v.x +
            m.data[6]  * v.y +
            m.data[10] * v.z +
            m.data[14] * v.w;

        result.w =
            m.data[3]  * v.x +
            m.data[7]  * v.y +
            m.data[11] * v.z +
            m.data[15] * v.w;

        return result;
}

PUB FMatrix4 fmat4_translation(FVector4 v)
{
        FMatrix4 m = fmat4_identity();
        m.data[12] = v.x;
        m.data[13] = v.y;
        m.data[14] = v.z;
        m.data[15] = v.w;
        return m;
}

PUB FMatrix4 fmat4_scaling(f32 scalar)
{
        FMatrix4 m = fmat4_zero();
        m.data[ 0] = scalar;
        m.data[ 5] = scalar;
        m.data[10] = scalar;
        m.data[15] = 1;
        return m;
}

PUB FMatrix4 fmat4_rotation(FVector3 axis, f32 rad)
{
        f32 icos = (1.0f - (f32)cos(rad));
        f32 rcos = (f32)cos(rad);
        f32 rsin = (f32)sin(rad);

        FMatrix4 m = fmat4_identity();
        FVector3 unit = fvec3_norm(axis);

        m.data[ 0] = unit.x * unit.x * icos + rcos;
        m.data[ 1] = unit.x * unit.y * icos + unit.z * rsin;
        m.data[ 2] = unit.x * unit.z * icos - unit.y * rsin;

        m.data[ 4] = unit.x * unit.y * icos - unit.z * rsin;
        m.data[ 5] = unit.y * unit.y * icos + rcos;
        m.data[ 6] = unit.y * unit.z * icos + unit.x * rsin;

        m.data[ 8] = unit.x * unit.z * icos + unit.y * rsin;
        m.data[ 9] = unit.y * unit.z * icos - unit.x * rsin;
        m.data[10] = unit.z * unit.z * icos + rcos;

        return m;
}

PUB FMatrix4 fmat4_rotation_x(f32 rad)
{
        FMatrix4 m = fmat4_identity();
        m.data[ 5] =  (f32)cos(rad);
        m.data[ 6] =  (f32)sin(rad);
        m.data[ 9] = -(f32)sin(rad);
        m.data[10] =  (f32)cos(rad);
        return m;
}

PUB FMatrix4 fmat4_rotation_y(f32 rad)
{
        FMatrix4 m = fmat4_identity();
        m.data[ 0] =  (f32)cos(rad);
        m.data[ 2] = -(f32)sin(rad);
        m.data[ 8] =  (f32)sin(rad);
        m.data[10] =  (f32)cos(rad);
        return m;
}

PUB FMatrix4 fmat4_rotation_z(f32 rad)
{
        FMatrix4 m = fmat4_identity();
        m.data[ 0] =  (f32)cos(rad);
        m.data[ 1] =  (f32)sin(rad);
        m.data[ 4] = -(f32)sin(rad);
        m.data[ 5] =  (f32)cos(rad);
        return m;
}

PUB FMatrix4 fmat4_from_mat4(Matrix4 m)
{
        FMatrix4 res;
        s32 i;

        for(i = 0; i < 16; i++) {
                res.data[i] = (f32)m.data[i];
        }

        return res;
}

PUB Matrix4 mat4_from_fmat4(FMatrix4 m)
{
        Matrix4 res;
        s32 i;

        for(i = 0; i < 16; i++) {
                res.data[i] = m.data[i];
        }

        return res;
}
