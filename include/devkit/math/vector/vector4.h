#ifndef VASALL_DEVKIT_VECTOR4_H
#define VASALL_DEVKIT_VECTOR4_H

#include <devkit/scope.h>
#include <devkit/types.h>

typedef struct Vector4 {
        f64 x;
        f64 y;
        f64 z;
        f64 w;
} Vector4;

PUB Vector4 vec4(f64 x, f64 y, f64 z, f64 w);
PUB Vector4 vec4_zero(void);
PUB Vector4 vec4_set(f64 value);

/* ret_v = v1 + v2 */
PUB Vector4 vec4_add(Vector4 v1, Vector4 v2);

/* ret_v = v1 - v2 */
PUB Vector4 vec4_sub(Vector4 v1, Vector4 v2);

/* ret_v = v * scalar */
PUB Vector4 vec4_scale(Vector4 v, f64 scalar);

/* ret_v = v / |v| (returns zero vector if |v| = 0) */
PUB Vector4 vec4_norm(Vector4 v);

/* ret_mag = sqrt(x * x + y * y + z * z + w * w) */
PUB f64 vec4_mag(Vector4 v);

/* ret_mag_sqr = x * x + y * y + z * z + w * w */
PUB f64 vec4_mag_sqr(Vector4 v);

/* ret_dot = v1 ⋅ v2 */
PUB f64 vec4_dot(Vector4 v1, Vector4 v2);

/* ret_v = v scaled so that min_v <= |v| <= max_v (zero vector unchanged) */
PUB Vector4 vec4_clamp(Vector4 v, f64 min_v, f64 max_v);

/* ret_v = v1 + (v2 - v1) * t */
PUB Vector4 vec4_lerp(Vector4 v1, Vector4 v2, f64 t);

#endif /* VASALL_DEVKIT_VECTOR4_H */
