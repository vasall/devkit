#include <devkit/math/vector.h>

#include <devkit/util/helper.h>

#include <math.h>

/******************************** VECTOR2 *************************************/

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

/******************************** VECTOR3 *************************************/

PUB Vector3 vec3(f64 x, f64 y, f64 z)
{
        Vector3 v;
        v.x = x;
        v.y = y;
        v.z = z;
        return v;
}

PUB Vector3 vec3_zero(void)
{
        Vector3 v;
        v.x = 0;
        v.y = 0;
        v.z = 0;
        return v;
}

PUB Vector3 vec3_set(f64 value)
{
        Vector3 v;
        v.x = value;
        v.y = value;
        v.z = value;
        return v;
}

PUB Vector3 vec3_add(Vector3 v1, Vector3 v2)
{
        Vector3 v;
        v.x = v1.x + v2.x;
        v.y = v1.y + v2.y;
        v.z = v1.z + v2.z;
        return v;
}

PUB Vector3 vec3_sub(Vector3 v1, Vector3 v2)
{
        Vector3 v;
        v.x = v1.x - v2.x;
        v.y = v1.y - v2.y;
        v.z = v1.z - v2.z;
        return v;
}

PUB Vector3 vec3_scale(Vector3 v, f64 scalar)
{
        Vector3 ret_v;
        ret_v.x = v.x * scalar;
        ret_v.y = v.y * scalar;
        ret_v.z = v.z * scalar;
        return ret_v;
}

PUB Vector3 vec3_norm(Vector3 v)
{
        Vector3 ret_v;
        f64 mag = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);

        if(mag == 0) {
                return vec3_zero();
        }

        ret_v.x = v.x / mag;
        ret_v.y = v.y / mag;
        ret_v.z = v.z / mag;
        return ret_v;
}

PUB f64 vec3_mag(Vector3 v)
{
        f64 mag = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
        return mag;
}

PUB f64 vec3_mag_sqr(Vector3 v)
{
        f64 mag_sqr = v.x * v.x + v.y * v.y + v.z * v.z;
        return mag_sqr;
}

PUB f64 vec3_dot(Vector3 v1, Vector3 v2)
{
        f64 ret_dot = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
        return ret_dot;
}

PUB Vector3 vec3_cross(Vector3 v1, Vector3 v2)
{
        Vector3 v;
        v.x = (v1.y * v2.z) - (v1.z * v2.y);
        v.y = (v1.z * v2.x) - (v1.x * v2.z);
        v.z = (v1.x * v2.y) - (v1.y * v2.x);
        return v;
}

PUB Vector3 vec3_clamp(Vector3 v, f64 min_v, f64 max_v)
{
        f64 mag = vec3_mag(v);

        if(mag == 0) {
                return v;
        }

        return vec3_scale(v, MIN(MAX(min_v, mag), max_v) / mag);
}

PUB Vector3 vec3_lerp(Vector3 v1, Vector3 v2, f64 t)
{
        Vector3 ret_v;
        ret_v.x = v1.x + (v2.x - v1.x) * t;
        ret_v.y = v1.y + (v2.y - v1.y) * t;
        ret_v.z = v1.z + (v2.z - v1.z) * t;
        return ret_v;
}

/******************************** VECTOR4 *************************************/

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
