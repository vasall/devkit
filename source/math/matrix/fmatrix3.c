#include <devkit/math/matrix/fmatrix3.h>

#include <string.h>
#include <math.h>

PUB FMatrix3 fmat3(FVector3 v0, FVector3 v1, FVector3 v2)
{
        FMatrix3 m;

        m.data[0] = v0.x;
        m.data[1] = v0.y;
        m.data[2] = v0.z;

        m.data[3] = v1.x;
        m.data[4] = v1.y;
        m.data[5] = v1.z;

        m.data[6] = v2.x;
        m.data[7] = v2.y;
        m.data[8] = v2.z;

        return m;
}

PUB FMatrix3 fmat3_zero(void)
{
        FMatrix3 m;
        memset(m.data, 0, sizeof(FMatrix3));
        return m;
}

PUB FMatrix3 fmat3_identity(void)
{
        FMatrix3 m;
        memset(m.data, 0, sizeof(FMatrix3));
        m.data[0] = 1;
        m.data[4] = 1;
        m.data[8] = 1;
        return m;
}

PUB FMatrix3 fmat3_set(f32 value)
{
        FMatrix3 m;
        s32 i;

        for(i = 0; i < 9; i++) {
                m.data[i] = value;
        }

        return m;
}

PUB FVector3 fmat3_col(FMatrix3 m, s32 col)
{
        FVector3 v;
        v.x = m.data[col * 3 + 0];
        v.y = m.data[col * 3 + 1];
        v.z = m.data[col * 3 + 2];
        return v;
}

PUB f32 fmat3_at(FMatrix3 m, s32 col, s32 row)
{
        return m.data[col * 3 + row];
}

PUB FMatrix3 fmat3_add(FMatrix3 m1, FMatrix3 m2)
{
        FMatrix3 m;
        s32 i;

        for(i = 0; i < 9; i++) {
                m.data[i] = m1.data[i] + m2.data[i];
        }

        return m;
}

PUB FMatrix3 fmat3_sub(FMatrix3 m1, FMatrix3 m2)
{
        FMatrix3 m;
        s32 i;

        for(i = 0; i < 9; i++) {
                m.data[i] = m1.data[i] - m2.data[i];
        }

        return m;
}

PUB FMatrix3 fmat3_scale(FMatrix3 m, f32 scalar)
{
        FMatrix3 res;
        s32 i;

        for(i = 0; i < 9; i++) {
                res.data[i] = m.data[i] * scalar;
        }

        return res;
}

PUB FMatrix3 fmat3_mul(FMatrix3 m1, FMatrix3 m2)
{
        FMatrix3 res;
        unsigned int row;
        unsigned int col;

        for(col = 0; col < 3; col++) {
                for(row = 0; row < 3; row++) {
                        res.data[row + col * 3] =
                        m1.data[row + 0 * 3] * m2.data[0 + col * 3] +
                        m1.data[row + 1 * 3] * m2.data[1 + col * 3] +
                        m1.data[row + 2 * 3] * m2.data[2 + col * 3];
                }
        }

        return res;
}

PUB FMatrix3 fmat3_trans(FMatrix3 m)
{
        FMatrix3 res;

        res.data[0] = m.data[0];
        res.data[1] = m.data[3];
        res.data[2] = m.data[6];

        res.data[3] = m.data[1];
        res.data[4] = m.data[4];
        res.data[5] = m.data[7];

        res.data[6] = m.data[2];
        res.data[7] = m.data[5];
        res.data[8] = m.data[8];

        return res;
}

PUB f32 fmat3_det(FMatrix3 m)
{
        f32 m00 = m.data[0];
        f32 m10 = m.data[1];
        f32 m20 = m.data[2];

        f32 m01 = m.data[3];
        f32 m11 = m.data[4];
        f32 m21 = m.data[5];

        f32 m02 = m.data[6];
        f32 m12 = m.data[7];
        f32 m22 = m.data[8];

        return
            m00 * (m11 * m22 - m21 * m12)
          - m01 * (m10 * m22 - m20 * m12)
          + m02 * (m10 * m21 - m20 * m11);
}

PUB FMatrix3 fmat3_inv(FMatrix3 m)
{
        FMatrix3 res;
        f32 det;

        f32 m00 = m.data[0];
        f32 m10 = m.data[1];
        f32 m20 = m.data[2];

        f32 m01 = m.data[3];
        f32 m11 = m.data[4];
        f32 m21 = m.data[5];

        f32 m02 = m.data[6];
        f32 m12 = m.data[7];
        f32 m22 = m.data[8];

        det = fmat3_det(m);

        res.data[0] =  (m11 * m22 - m21 * m12) / det;
        res.data[1] = -(m10 * m22 - m20 * m12) / det;
        res.data[2] =  (m10 * m21 - m20 * m11) / det;

        res.data[3] = -(m01 * m22 - m21 * m02) / det;
        res.data[4] =  (m00 * m22 - m20 * m02) / det;
        res.data[5] = -(m00 * m21 - m20 * m01) / det;

        res.data[6] =  (m01 * m12 - m11 * m02) / det;
        res.data[7] = -(m00 * m12 - m10 * m02) / det;
        res.data[8] =  (m00 * m11 - m10 * m01) / det;

        return res;
}

PUB FVector3 fmat3_xfm(FMatrix3 m, FVector3 v)
{
        FVector3 result;

        result.x =
            m.data[0] * v.x +
            m.data[3] * v.y +
            m.data[6] * v.z;

        result.y =
            m.data[1] * v.x +
            m.data[4] * v.y +
            m.data[7] * v.z;

        result.z =
            m.data[2] * v.x +
            m.data[5] * v.y +
            m.data[8] * v.z;

        return result;
}

PUB FMatrix3 fmat3_from_mat3(Matrix3 m)
{
        FMatrix3 res;
        s32 i;

        for(i = 0; i < 9; i++) {
                res.data[i] = (f32)m.data[i];
        }

        return res;
}

PUB Matrix3 mat3_from_fmat3(FMatrix3 m)
{
        Matrix3 res;
        s32 i;

        for(i = 0; i < 9; i++) {
                res.data[i] = m.data[i];
        }

        return res;
}
