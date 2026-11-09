#include <devkit/math/matrix/matrix3.h>

#include <string.h>
#include <math.h>

PUB Matrix3 mat3(Vector3 v0, Vector3 v1, Vector3 v2)
{
        Matrix3 m;

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

PUB Matrix3 mat3_zero(void)
{
        Matrix3 m;
        memset(m.data, 0, sizeof(Matrix3));
        return m;
}

PUB Matrix3 mat3_identity(void)
{
        Matrix3 m;
        memset(m.data, 0, sizeof(Matrix3));
        m.data[0] = 1;
        m.data[4] = 1;
        m.data[8] = 1;
        return m;
}

PUB Matrix3 mat3_set(f64 value)
{
        Matrix3 m;
        s32 i;

        for(i = 0; i < 9; i++) {
                m.data[i] = value;
        }

        return m;
}

PUB Vector3 mat3_col(Matrix3 m, s32 col)
{
        Vector3 v;
        v.x = m.data[col * 3 + 0];
        v.y = m.data[col * 3 + 1];
        v.z = m.data[col * 3 + 2];
        return v;
}

PUB f64 mat3_at(Matrix3 m, s32 col, s32 row)
{
        return m.data[col * 3 + row];
}

PUB Matrix3 mat3_add(Matrix3 m1, Matrix3 m2)
{
        Matrix3 m;
        s32 i;

        for(i = 0; i < 9; i++) {
                m.data[i] = m1.data[i] + m2.data[i];
        }

        return m;
}

PUB Matrix3 mat3_sub(Matrix3 m1, Matrix3 m2)
{
        Matrix3 m;
        s32 i;

        for(i = 0; i < 9; i++) {
                m.data[i] = m1.data[i] - m2.data[i];
        }

        return m;
}

PUB Matrix3 mat3_scale(Matrix3 m, f64 scalar)
{
        Matrix3 res;
        s32 i;

        for(i = 0; i < 9; i++) {
                res.data[i] = m.data[i] * scalar;
        }

        return res;
}

PUB Matrix3 mat3_mul(Matrix3 m1, Matrix3 m2)
{
        Matrix3 res;
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

PUB Matrix3 mat3_trans(Matrix3 m)
{
        Matrix3 res;

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

PUB f64 mat3_det(Matrix3 m)
{
        f64 m00 = m.data[0];
        f64 m10 = m.data[1];
        f64 m20 = m.data[2];

        f64 m01 = m.data[3];
        f64 m11 = m.data[4];
        f64 m21 = m.data[5];

        f64 m02 = m.data[6];
        f64 m12 = m.data[7];
        f64 m22 = m.data[8];

        return
            m00 * (m11 * m22 - m21 * m12)
          - m01 * (m10 * m22 - m20 * m12)
          + m02 * (m10 * m21 - m20 * m11);
}

PUB Matrix3 mat3_inv(Matrix3 m)
{
        Matrix3 res;
        f64 det;

        f64 m00 = m.data[0];
        f64 m10 = m.data[1];
        f64 m20 = m.data[2];

        f64 m01 = m.data[3];
        f64 m11 = m.data[4];
        f64 m21 = m.data[5];

        f64 m02 = m.data[6];
        f64 m12 = m.data[7];
        f64 m22 = m.data[8];

        det = mat3_det(m);

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

PUB Vector3 mat3_xfm(Matrix3 m, Vector3 v)
{
        Vector3 result;

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
