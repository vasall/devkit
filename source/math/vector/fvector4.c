#include <devkit/math/vector/fvector4.h>

#include <devkit/util/helper.h>

#include <math.h>

PUB FVector4 fvec4(f32 x, f32 y, f32 z, f32 w)
{
        FVector4 v;
        v.x = x;
        v.y = y;
        v.z = z;
        v.w = w;
        return v;
}

PUB FVector4 fvec4_zero(void)
{
        FVector4 v;
        v.x = 0;
        v.y = 0;
        v.z = 0;
        v.w = 0;
        return v;
}

PUB FVector4 fvec4_set(f32 value)
{
        FVector4 v;
        v.x = value;
        v.y = value;
        v.z = value;
        v.w = value;
        return v;
}

PUB FVector4 fvec4_add(FVector4 v1, FVector4 v2)
{
        FVector4 v;
        v.x = v1.x + v2.x;
        v.y = v1.y + v2.y;
        v.z = v1.z + v2.z;
        v.w = v1.w + v2.w;
        return v;
}

PUB FVector4 fvec4_sub(FVector4 v1, FVector4 v2)
{
        FVector4 v;
        v.x = v1.x - v2.x;
        v.y = v1.y - v2.y;
        v.z = v1.z - v2.z;
        v.w = v1.w - v2.w;
        return v;
}

PUB FVector4 fvec4_scale(FVector4 v, f32 scalar)
{
        FVector4 ret_v;
        ret_v.x = v.x * scalar;
        ret_v.y = v.y * scalar;
        ret_v.z = v.z * scalar;
        ret_v.w = v.w * scalar;
        return ret_v;
}

PUB FVector4 fvec4_norm(FVector4 v)
{
        FVector4 ret_v;
        f32 mag = (f32)sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);

        if(mag == 0) {
                return fvec4_zero();
        }

        ret_v.x = v.x / mag;
        ret_v.y = v.y / mag;
        ret_v.z = v.z / mag;
        ret_v.w = v.w / mag;
        return ret_v;
}

PUB f32 fvec4_mag(FVector4 v)
{
        f32 mag = (f32)sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
        return mag;
}

PUB f32 fvec4_mag_sqr(FVector4 v)
{
        f32 mag = v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
        return mag;
}

PUB f32 fvec4_dot(FVector4 v1, FVector4 v2)
{
        return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w);
}

PUB FVector4 fvec4_clamp(FVector4 v, f32 min_v, f32 max_v)
{
        f32 mag = fvec4_mag(v);

        if(mag == 0) {
                return v;
        }

        return fvec4_scale(v, MIN(MAX(min_v, mag), max_v) / mag);
}

PUB FVector4 fvec4_lerp(FVector4 v1, FVector4 v2, f32 t)
{
        FVector4 ret_v;
        ret_v.x = v1.x + (v2.x - v1.x) * t;
        ret_v.y = v1.y + (v2.y - v1.y) * t;
        ret_v.z = v1.z + (v2.z - v1.z) * t;
        ret_v.w = v1.w + (v2.w - v1.w) * t;
        return ret_v;
}

PUB FVector4 fvec4_from_vec4(Vector4 v)
{
        FVector4 res;

        res.x = (f32)v.x;
        res.y = (f32)v.y;
        res.z = (f32)v.z;
        res.w = (f32)v.w;

        return res;
}

PUB Vector4 vec4_from_fvec4(FVector4 v)
{
        Vector4 res;

        res.x = v.x;
        res.y = v.y;
        res.z = v.z;
        res.w = v.w;

        return res;
}
