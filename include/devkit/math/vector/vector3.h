#ifndef VASALL_DEVKIT_VECTOR3_H
#define VASALL_DEVKIT_VECTOR3_H

#include <devkit/scope.h>
#include <devkit/types.h>

typedef struct Vector3 {
        f64 x;
        f64 y;
        f64 z;
} Vector3;

PUB Vector3 vec3(f64 x, f64 y, f64 z);
PUB Vector3 vec3_zero(void);
PUB Vector3 vec3_set(f64 value);

/* ret_v = v1 + v2 */
PUB Vector3 vec3_add(Vector3 v1, Vector3 v2);

/* ret_v = v1 - v2 */
PUB Vector3 vec3_sub(Vector3 v1, Vector3 v2);

/* ret_v = v * scalar */
PUB Vector3 vec3_scale(Vector3 v, f64 scalar);

/* ret_v = v / |v| (returns zero vector if |v| = 0) */
PUB Vector3 vec3_norm(Vector3 v);

/* ret_mag = sqrt(x * x + y * y + z * z) */
PUB f64 vec3_mag(Vector3 v);

/* ret_mag_sqr = x * x + y * y + z * z */
PUB f64 vec3_mag_sqr(Vector3 v);

/* ret_dot = v1 ⋅ v2 */
PUB f64 vec3_dot(Vector3 v1, Vector3 v2);

/* ret_v = v1 x v2 */
PUB Vector3 vec3_cross(Vector3 v1, Vector3 v2);

/* ret_v = v scaled so that min_v <= |v| <= max_v (zero vector unchanged) */
PUB Vector3 vec3_clamp(Vector3 v, f64 min_v, f64 max_v);

/* ret_v = v1 + (v2 - v1) * t */
PUB Vector3 vec3_lerp(Vector3 v1, Vector3 v2, f64 t);

#endif /* VASALL_DEVKIT_VECTOR3_H */
