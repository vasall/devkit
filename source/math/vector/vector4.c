#include <devkit/math/vector/vector4.h>

#include <devkit/util/helper.h>

#include <math.h>

PUB Vector4 vec4(f64 x, f64 y, f64 z, f64 w)
{
        Vector4 v;
        v.x = x;
        v.y = y;
        v.z = z;
        v.w = w;
        return v;
}

PUB Vector4 vec4_zero(void)
{
        Vector4 v;
        v.x = 0;
        v.y = 0;
        v.z = 0;
        v.w = 0;
        return v;
}

PUB Vector4 vec4_set(f64 value)
{
        Vector4 v;
        v.x = value;
        v.y = value;
        v.z = value;
        v.w = value;
        return v;
}

PUB Vector4 vec4_add(Vector4 v1, Vector4 v2)
{
        Vector4 v;
        v.x = v1.x + v2.x;
        v.y = v1.y + v2.y;
        v.z = v1.z + v2.z;
        v.w = v1.w + v2.w;
        return v;
}

PUB Vector4 vec4_sub(Vector4 v1, Vector4 v2)
{
        Vector4 v;
        v.x = v1.x - v2.x;
        v.y = v1.y - v2.y;
        v.z = v1.z - v2.z;
        v.w = v1.w - v2.w;
        return v;
}

PUB Vector4 vec4_scale(Vector4 v, f64 scalar)
{
        Vector4 ret_v;
        ret_v.x = v.x * scalar;
        ret_v.y = v.y * scalar;
        ret_v.z = v.z * scalar;
        ret_v.w = v.w * scalar;
        return ret_v;
}

PUB Vector4 vec4_norm(Vector4 v)
{
        Vector4 ret_v;
        f64 mag = sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);

        if(mag == 0) {
                return vec4_zero();
        }

        ret_v.x = v.x / mag;
        ret_v.y = v.y / mag;
        ret_v.z = v.z / mag;
        ret_v.w = v.w / mag;
        return ret_v;
}

PUB f64 vec4_mag(Vector4 v)
{
        f64 mag = sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
        return mag;
}

PUB f64 vec4_mag_sqr(Vector4 v)
{
        f64 mag = v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
        return mag;
}

PUB f64 vec4_dot(Vector4 v1, Vector4 v2)
{
        return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w);
}

PUB Vector4 vec4_clamp(Vector4 v, f64 min_v, f64 max_v)
{
        f64 mag = vec4_mag(v);

        if(mag == 0) {
                return v;
        }

        return vec4_scale(v, MIN(MAX(min_v, mag), max_v) / mag);
}

PUB Vector4 vec4_lerp(Vector4 v1, Vector4 v2, f64 t)
{
        Vector4 ret_v;
        ret_v.x = v1.x + (v2.x - v1.x) * t;
        ret_v.y = v1.y + (v2.y - v1.y) * t;
        ret_v.z = v1.z + (v2.z - v1.z) * t;
        ret_v.w = v1.w + (v2.w - v1.w) * t;
        return ret_v;
}
