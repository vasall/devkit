#include <devkit/math/vector/fvector3.h>

#include <devkit/util/helper.h>

#include <math.h>

PUB FVector3 fvec3(f32 x, f32 y, f32 z)
{
        FVector3 v;
        v.x = x;
        v.y = y;
        v.z = z;
        return v;
}

PUB FVector3 fvec3_zero(void)
{
        FVector3 v;
        v.x = 0;
        v.y = 0;
        v.z = 0;
        return v;
}

PUB FVector3 fvec3_set(f32 value)
{
        FVector3 v;
        v.x = value;
        v.y = value;
        v.z = value;
        return v;
}

PUB FVector3 fvec3_add(FVector3 v1, FVector3 v2)
{
        FVector3 v;
        v.x = v1.x + v2.x;
        v.y = v1.y + v2.y;
        v.z = v1.z + v2.z;
        return v;
}

PUB FVector3 fvec3_sub(FVector3 v1, FVector3 v2)
{
        FVector3 v;
        v.x = v1.x - v2.x;
        v.y = v1.y - v2.y;
        v.z = v1.z - v2.z;
        return v;
}

PUB FVector3 fvec3_scale(FVector3 v, f32 scalar)
{
        FVector3 ret_v;
        ret_v.x = v.x * scalar;
        ret_v.y = v.y * scalar;
        ret_v.z = v.z * scalar;
        return ret_v;
}

PUB FVector3 fvec3_norm(FVector3 v)
{
        FVector3 ret_v;
        f32 mag = (f32)sqrt(v.x * v.x + v.y * v.y + v.z * v.z);

        if(mag == 0) {
                return fvec3_zero();
        }

        ret_v.x = v.x / mag;
        ret_v.y = v.y / mag;
        ret_v.z = v.z / mag;
        return ret_v;
}

PUB f32 fvec3_mag(FVector3 v)
{
        f32 mag = (f32)sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
        return mag;
}

PUB f32 fvec3_mag_sqr(FVector3 v)
{
        f32 mag_sqr = v.x * v.x + v.y * v.y + v.z * v.z;
        return mag_sqr;
}

PUB f32 fvec3_dot(FVector3 v1, FVector3 v2)
{
        f32 ret_dot = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
        return ret_dot;
}

PUB FVector3 fvec3_cross(FVector3 v1, FVector3 v2)
{
        FVector3 v;
        v.x = (v1.y * v2.z) - (v1.z * v2.y);
        v.y = (v1.z * v2.x) - (v1.x * v2.z);
        v.z = (v1.x * v2.y) - (v1.y * v2.x);
        return v;
}

PUB FVector3 fvec3_clamp(FVector3 v, f32 min_v, f32 max_v)
{
        f32 mag = fvec3_mag(v);

        if(mag == 0) {
                return v;
        }

        return fvec3_scale(v, MIN(MAX(min_v, mag), max_v) / mag);
}

PUB FVector3 fvec3_lerp(FVector3 v1, FVector3 v2, f32 t)
{
        FVector3 ret_v;
        ret_v.x = v1.x + (v2.x - v1.x) * t;
        ret_v.y = v1.y + (v2.y - v1.y) * t;
        ret_v.z = v1.z + (v2.z - v1.z) * t;
        return ret_v;
}

PUB FVector3 fvec3_from_vec3(Vector3 v)
{
        FVector3 res;

        res.x = (f32)v.x;
        res.y = (f32)v.y;
        res.z = (f32)v.z;

        return res;
}

PUB Vector3 vec3_from_fvec3(FVector3 v)
{
        Vector3 res;

        res.x = v.x;
        res.y = v.y;
        res.z = v.z;

        return res;
}
