#include <devkit/math/matrix/fmatrix2.h>

#include <string.h>
#include <math.h>

PUB FMatrix2 fmat2(FVector2 v0, FVector2 v1)
{
        FMatrix2 m;

        m.data[0] = v0.x;
        m.data[1] = v0.y;

        m.data[2] = v1.x;
        m.data[3] = v1.y;

        return m;
}

PUB FMatrix2 fmat2_zero(void)
{
        FMatrix2 m;
        memset(m.data, 0, sizeof(FMatrix2));
        return m;
}

PUB FMatrix2 fmat2_identity(void)
{
        FMatrix2 m;
        memset(m.data, 0, sizeof(FMatrix2));
        m.data[0] = 1;
        m.data[3] = 1;
        return m;
}

PUB FMatrix2 fmat2_set(f32 value)
{
        FMatrix2 m;
        s32 i;

        for(i = 0; i < 4; i++) {
                m.data[i] = value;
        }

        return m;

}

PUB FVector2 fmat2_col(FMatrix2 m, s32 col)
{
        FVector2 v;
        v.x = m.data[col * 2];
        v.y = m.data[col * 2 + 1];
        return v;
}

PUB f32 fmat2_at(FMatrix2 m, s32 col, s32 row)
{
        return m.data[col * 2 + row];
}

PUB FMatrix2 fmat2_add(FMatrix2 m1, FMatrix2 m2)
{
        FMatrix2 m;
        s32 i;

        for(i = 0; i < 4; i++) {
                m.data[i] = m1.data[i] + m2.data[i];
        }

        return m;
}

PUB FMatrix2 fmat2_sub(FMatrix2 m1, FMatrix2 m2)
{
        FMatrix2 m;
        s32 i;

        for(i = 0; i < 4; i++) {
                m.data[i] = m1.data[i] - m2.data[i];
        }

        return m;
}

PUB FMatrix2 fmat2_scale(FMatrix2 m, f32 scalar)
{
        FMatrix2 ret;
        s32 i;

        for(i = 0; i < 4; i++) {
                ret.data[i] = m.data[i] * scalar;
        }

        return ret;
}

PUB FMatrix2 fmat2_mul(FMatrix2 m1, FMatrix2 m2)
{
        FMatrix2 ret;
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

PUB FMatrix2 fmat2_trans(FMatrix2 m)
{
        FMatrix2 res;

        res.data[0] = m.data[0];
        res.data[1] = m.data[2];
        res.data[2] = m.data[1];
        res.data[3] = m.data[3];

        return res;
}

PUB f32 fmat2_det(FMatrix2 m)
{
        return m.data[0] * m.data[3] - m.data[2] * m.data[1];
}

PUB FMatrix2 fmat2_inv(FMatrix2 m)
{
        f32 det;
        FMatrix2 result;

        det = m.data[0] * m.data[3] - m.data[2] * m.data[1];

        result.data[0] =  m.data[3] / det;
        result.data[1] = -m.data[1] / det;
        result.data[2] = -m.data[2] / det;
        result.data[3] =  m.data[0] / det;

        return result;
}

PUB FVector2 fmat2_xfm(FMatrix2 m, FVector2 v)
{
        FVector2 res;

        res.x = m.data[0] * v.x + m.data[2] * v.y;
        res.y = m.data[1] * v.x + m.data[3] * v.y;

        return res;
}

PUB FMatrix2 fmat2_from_mat2(Matrix2 m)
{
        FMatrix2 res;
        s32 i;

        for(i = 0; i < 4; i++) {
                res.data[i] = (f32)m.data[i];
        }

        return res;
}

PUB Matrix2 mat2_from_fmat2(FMatrix2 m)
{
        Matrix2 res;
        s32 i;

        for(i = 0; i < 4; i++) {
                res.data[i] = m.data[i];
        }

        return res;
}
