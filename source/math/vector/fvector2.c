#include <devkit/math/vector/fvector2.h>

#include <devkit/util/helper.h>

#include <math.h>

PUB FVector2 fvec2(f32 x, f32 y)
{
        FVector2 v;
        v.x = x;
        v.y = y;
        return v;
}

PUB FVector2 fvec2_zero(void)
{
        FVector2 v;
        v.x = 0;
        v.y = 0;
        return v;
}

PUB FVector2 fvec2_set(f32 value)
{
        FVector2 v;
        v.x = value;
        v.y = value;
        return v;
}

PUB FVector2 fvec2_add(FVector2 v1, FVector2 v2)
{
        FVector2 v_sum;
        v_sum.x = v1.x + v2.x;
        v_sum.y = v1.y + v2.y;
        return v_sum;
}

PUB FVector2 fvec2_sub(FVector2 v1, FVector2 v2)
{
        FVector2 v_diff;
        v_diff.x = v1.x - v2.x;
        v_diff.y = v1.y - v2.y;
        return v_diff;
}

PUB FVector2 fvec2_scale(FVector2 v, f32 scalar)
{
        FVector2 v_scaled;
        v_scaled.x = v.x * scalar;
        v_scaled.y = v.y * scalar;
        return v_scaled;
}

PUB FVector2 fvec2_norm(FVector2 v)
{
        FVector2 norm_v;
        f32 mag = (f32)sqrt(v.x * v.x + v.y * v.y);

        if(mag == 0) {
                return fvec2_zero();
        }

        norm_v.x = v.x / mag;
        norm_v.y = v.y / mag;
        return norm_v;
}

PUB f32 fvec2_mag(FVector2 v)
{
        return (f32)sqrt(v.x * v.x + v.y * v.y);
}

PUB f32 fvec2_mag_sqr(FVector2 v)
{
        return v.x * v.x + v.y * v.y;
}

PUB f32 fvec2_dot(FVector2 v1, FVector2 v2)
{
        return (v1.x * v2.x) + (v1.y * v2.y);
}

PUB FVector2 fvec2_clamp(FVector2 v, f32 min_v, f32 max_v)
{
        f32 mag = fvec2_mag(v);

        /* A zero vector has no drection to scale along */
        if(mag == 0) {
                return v;
        }

        return fvec2_scale(v, MIN(MAX(min_v, mag), max_v) / mag);
}

PUB FVector2 fvec2_lerp(FVector2 v1, FVector2 v2, f32 t)
{
        FVector2 ret_v;
        ret_v.x = v1.x + (v2.x - v1.x) * t;
        ret_v.y = v1.y + (v2.y - v1.y) * t;
        return ret_v;
}

PUB FVector2 fvec2_from_vec2(Vector2 v)
{
        FVector2 res;

        res.x = (f32)v.x;
        res.y = (f32)v.y;

        return res;
}

PUB Vector2 vec2_from_fvec2(FVector2 v)
{
        Vector2 res;

        res.x = v.x;
        res.y = v.y;

        return res;
}
