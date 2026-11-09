#include <devkit/math/vector/vector2.h>

#include <devkit/util/helper.h>

#include <math.h>

PUB Vector2 vec2(f64 x, f64 y)
{
        Vector2 v;
        v.x = x;
        v.y = y;
        return v;
}

PUB Vector2 vec2_zero(void)
{
        Vector2 v;
        v.x = 0;
        v.y = 0;
        return v;
}

PUB Vector2 vec2_set(f64 value)
{
        Vector2 v;
        v.x = value;
        v.y = value;
        return v;
}

PUB Vector2 vec2_add(Vector2 v1, Vector2 v2)
{
        Vector2 v_sum;
        v_sum.x = v1.x + v2.x;
        v_sum.y = v1.y + v2.y;
        return v_sum;
}

PUB Vector2 vec2_sub(Vector2 v1, Vector2 v2)
{
        Vector2 v_diff;
        v_diff.x = v1.x - v2.x;
        v_diff.y = v1.y - v2.y;
        return v_diff;
}

PUB Vector2 vec2_scale(Vector2 v, f64 scalar)
{
        Vector2 v_scaled;
        v_scaled.x = v.x * scalar;
        v_scaled.y = v.y * scalar;
        return v_scaled;
}

PUB Vector2 vec2_norm(Vector2 v)
{
        Vector2 norm_v;
        f64 mag = sqrt(v.x * v.x + v.y * v.y);

        if(mag == 0) {
                return vec2_zero();
        }

        norm_v.x = v.x / mag;
        norm_v.y = v.y / mag;
        return norm_v;
}

PUB f64 vec2_mag(Vector2 v)
{
        return sqrt(v.x * v.x + v.y * v.y);
}

PUB f64 vec2_mag_sqr(Vector2 v)
{
        return v.x * v.x + v.y * v.y;
}

PUB f64 vec2_dot(Vector2 v1, Vector2 v2)
{
        return (v1.x * v2.x) + (v1.y * v2.y);
}

PUB Vector2 vec2_clamp(Vector2 v, f64 min_v, f64 max_v)
{
        f64 mag = vec2_mag(v);

        /* A zero vector has no drection to scale along */
        if(mag == 0) {
                return v;
        }

        return vec2_scale(v, MIN(MAX(min_v, mag), max_v) / mag);
}

PUB Vector2 vec2_lerp(Vector2 v1, Vector2 v2, f64 t)
{
        Vector2 ret_v;
        ret_v.x = v1.x + (v2.x - v1.x) * t;
        ret_v.y = v1.y + (v2.y - v1.y) * t;
        return ret_v;
}
