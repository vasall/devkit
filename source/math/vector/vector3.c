#include <devkit/math/vector/vector3.h>

#include <devkit/util/helper.h>

#include <math.h>

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
