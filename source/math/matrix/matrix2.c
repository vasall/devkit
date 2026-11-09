#include <devkit/math/matrix/matrix2.h>

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
