#include <devkit/math/matrix.h>

#include <string.h>
#include <math.h>

PUB Matrix2 mat2(Vector2 v0, Vector2 v1)
{
        Matrix2 m;

        m.data[0] = v0.x;
        m.data[1] = v0.y;

        m.data[2] = v1.x;
        m.data[3] = v1.y;

        return m;
}

PUB Matrix2 mat2_zero(void)
{
        Matrix2 m;
        memset(m.data, 0, sizeof(Matrix2));
        return m;
}

PUB Matrix2 mat2_identity(void)
{
        Matrix2 m;
        memset(m.data, 0, sizeof(Matrix2));
        m.data[0] = 1;
        m.data[3] = 1;
        return m;
}

PUB Matrix2 mat2_set(f64 value)
{
        Matrix2 m;
        s32 i;

        for(i = 0; i < 4; i++) {
                m.data[i] = value;
        }

        return m;

}

PUB Vector2 mat2_col(Matrix2 m, s32 col)
{
        Vector2 v;
        v.x = m.data[col * 2];
        v.y = m.data[col * 2 + 1];
        return v;
}

PUB f64 mat2_at(Matrix2 m, s32 col, s32 row)
{
        return m.data[col * 2 + row];
}

PUB Matrix2 mat2_add(Matrix2 m1, Matrix2 m2)
{
        Matrix2 m;
        s32 i;

        for(i = 0; i < 4; i++) {
                m.data[i] = m1.data[i] + m2.data[i];
        }

        return m;
}

PUB Matrix2 mat2_sub(Matrix2 m1, Matrix2 m2)
{
        Matrix2 m;
        s32 i;

        for(i = 0; i < 4; i++) {
                m.data[i] = m1.data[i] - m2.data[i];
        }

        return m;
}

PUB Matrix2 mat2_scale(Matrix2 m, f64 scalar)
{
        Matrix2 ret;
        s32 i;

        for(i = 0; i < 4; i++) {
                ret.data[i] = m.data[i] * scalar;
        }

        return ret;
}

PUB Matrix2 mat2_mul(Matrix2 m1, Matrix2 m2)
{
        Matrix2 ret;
        s32 row;
        s32 col;

        for(col = 0; col < 2; ++col) {
                for(row = 0; row < 2; ++row) {
                        ret.data[row + col * 2] =
                            m1.data[row + 0 * 2] * m2.data[0 + col * 2] +
                            m1.data[row + 1 * 2] * m2.data[1 + col * 2];
                }
        }

        return ret;
}

PUB Matrix2 mat2_trans(Matrix2 m)
{
        Matrix2 res;

        res.data[0] = m.data[0];
        res.data[1] = m.data[2];
        res.data[2] = m.data[1];
        res.data[3] = m.data[3];

        return res;
}

PUB f64 mat2_det(Matrix2 m)
{
        return m.data[0] * m.data[3] - m.data[2] * m.data[1];
}

PUB Matrix2 mat2_inv(Matrix2 m)
{
        f64 det;
        Matrix2 result;

        det = m.data[0] * m.data[3] - m.data[2] * m.data[1];

        result.data[0] =  m.data[3] / det;
        result.data[1] = -m.data[1] / det;
        result.data[2] = -m.data[2] / det;
        result.data[3] =  m.data[0] / det;

        return result;
}

PUB Vector2 mat2_xfm(Matrix2 m, Vector2 v)
{
        Vector2 res;

        res.x = m.data[0] * v.x + m.data[2] * v.y;
        res.y = m.data[1] * v.x + m.data[3] * v.y;

        return res;
}

/****************************** MATRIX 3x3 ************************************/

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

/****************************** MATRIX 4x4 ************************************/

PUB Matrix4 mat4(Vector4 v0, Vector4 v1, Vector4 v2, Vector4 v3)
{
        Matrix4 m;

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

PUB Matrix4 mat4_zero(void)
{
        Matrix4 m;
        memset(m.data, 0, sizeof(Matrix4));
        return m;
}

PUB Matrix4 mat4_identity(void)
{
        Matrix4 m = mat4_zero();
        m.data[ 0] = 1;
        m.data[ 5] = 1;
        m.data[10] = 1;
        m.data[15] = 1;
        return m;
}

PUB Matrix4 mat4_set(f64 value)
{
        Matrix4 m;
        s32 i;

        for(i = 0; i < 16; i++) {
                m.data[i] = value;
        }

        return m;
}

PUB Vector4 mat4_col(Matrix4 m, s32 col)
{
        Vector4 v;
        v.x = m.data[col * 4 + 0];
        v.y = m.data[col * 4 + 1];
        v.z = m.data[col * 4 + 2];
        v.w = m.data[col * 4 + 3];
        return v;
}

PUB f64 mat4_at(Matrix4 mat, s32 col, s32 row)
{
        return mat.data[col * 4 + row];
}

PUB Matrix4 mat4_add(Matrix4 m1, Matrix4 m2)
{
        Matrix4 m;
        s32 i;

        for(i = 0; i < 16; i++) {
                m.data[i] = m1.data[i] + m2.data[i];
        }

        return m;
}

PUB Matrix4 mat4_sub(Matrix4 m1, Matrix4 m2)
{
        Matrix4 m;
        s32 i;

        for(i = 0; i < 16; i++) {
                m.data[i] = m1.data[i] - m2.data[i];
        }

        return m;
}

PUB Matrix4 mat4_scale(Matrix4 m, f64 scalar)
{
        Matrix4 res;
        s32 i;

        for(i = 0; i < 16; i++) {
                res.data[i] = m.data[i] * scalar;
        }

        return res;
}

PUB Matrix4 mat4_mul(Matrix4 m1, Matrix4 m2)
{
        Matrix4 result;
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

PUB Matrix4 mat4_trans(Matrix4 m)
{
        Matrix4 result;

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

PUB f64 mat4_det(Matrix4 m)
{
        Matrix3 minor;
        f64 d0;
        f64 d1;
        f64 d2;
        f64 d3;

        minor = mat3(
            vec3(m.data[5],  m.data[6],  m.data[7]),
            vec3(m.data[9],  m.data[10], m.data[11]),
            vec3(m.data[13], m.data[14], m.data[15])
        );
        d0 = mat3_det(minor);

        minor = mat3(
            vec3(m.data[4],  m.data[6],  m.data[7]),
            vec3(m.data[8],  m.data[10], m.data[11]),
            vec3(m.data[12], m.data[14], m.data[15])
        );
        d1 = mat3_det(minor);

        minor = mat3(
            vec3(m.data[4],  m.data[5],  m.data[7]),
            vec3(m.data[8],  m.data[9],  m.data[11]),
            vec3(m.data[12], m.data[13], m.data[15])
        );
        d2 = mat3_det(minor);

        minor = mat3(
            vec3(m.data[4],  m.data[5],  m.data[6]),
            vec3(m.data[8],  m.data[9],  m.data[10]),
            vec3(m.data[12], m.data[13], m.data[14])
        );
        d3 = mat3_det(minor);

        /* Expansion along column 0: each minor drops column 0 and row i */
        return
            m.data[0] * d0 -
            m.data[1] * d1 +
            m.data[2] * d2 -
            m.data[3] * d3;
}

PUB Matrix4 mat4_inv(Matrix4 m)
{
        Matrix4 cof;
        Matrix4 adj;
        Matrix4 result;

        f64 det;
        s32 row;
        s32 col;

        det = mat4_det(m);

        for(col = 0; col < 4; col++) {
                for(row = 0; row < 4; row++) {
                        Matrix3 minor;
                        f64 values[9];
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
                            mat3_det(minor);
                }
        }

        adj = mat4_trans(cof);

        for(row = 0; row < 16; row++) {
                result.data[row] = adj.data[row] / det;
        }

        return result;
}

PUB Vector4 mat4_xfm(Matrix4 m, Vector4 v)
{
        Vector4 result;

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

PUB Matrix4 mat4_translation(Vector4 v)
{
        Matrix4 m = mat4_identity();
        m.data[12] = v.x;
        m.data[13] = v.y;
        m.data[14] = v.z;
        m.data[15] = v.w;
        return m;
}

PUB Matrix4 mat4_scaling(f64 scalar)
{
        Matrix4 m = mat4_zero();
        m.data[ 0] = scalar;
        m.data[ 5] = scalar;
        m.data[10] = scalar;
        m.data[15] = 1;
        return m;
}

PUB Matrix4 mat4_rotation(Vector3 axis, f64 rad)
{
        f64 icos = (1.0f - (f64)cos(rad));
        f64 rcos = (f64)cos(rad);
        f64 rsin = (f64)sin(rad);

        Matrix4 m = mat4_identity();
        Vector3 unit = vec3_norm(axis);

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

PUB Matrix4 mat4_rotation_x(f64 rad)
{
        Matrix4 m = mat4_identity();
        m.data[ 5] =  (f64)cos(rad);
        m.data[ 6] =  (f64)sin(rad);
        m.data[ 9] = -(f64)sin(rad);
        m.data[10] =  (f64)cos(rad);
        return m;
}

PUB Matrix4 mat4_rotation_y(f64 rad)
{
        Matrix4 m = mat4_identity();
        m.data[ 0] =  (f64)cos(rad);
        m.data[ 2] = -(f64)sin(rad);
        m.data[ 8] =  (f64)sin(rad);
        m.data[10] =  (f64)cos(rad);
        return m;
}

PUB Matrix4 mat4_rotation_z(f64 rad)
{
        Matrix4 m = mat4_identity();
        m.data[ 0] =  (f64)cos(rad);
        m.data[ 1] =  (f64)sin(rad);
        m.data[ 4] = -(f64)sin(rad);
        m.data[ 5] =  (f64)cos(rad);
        return m;
}
