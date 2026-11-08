#ifndef VASALL_DEVKIT_VECTOR_H
#define VASALL_DEVKIT_VECTOR_H

#include <devkit/scope.h>
#include <devkit/types.h>

/******************************** VECTOR2 *************************************/

typedef struct Vector2 {
        f64 x;
        f64 y;
} Vector2;

PUB Vector2 vec2(f64 x, f64 y);
PUB Vector2 vec2_zero(void);
PUB Vector2 vec2_set(f64 value);

/* ret_v = v1 + v2 */
PUB Vector2 vec2_add(Vector2 v1, Vector2 v2);

/* ret_v = v1 - v2 */
PUB Vector2 vec2_sub(Vector2 v1, Vector2 v2);

/* ret_v = v * scalar */
PUB Vector2 vec2_scale(Vector2 v, f64 scalar);

/* ret_v = v / |v| (returns zero vector if |v| = 0) */
PUB Vector2 vec2_norm(Vector2 v);

/* ret_mag = sqrt(x * x + y * y) */
PUB f64 vec2_mag(Vector2 v);

/* ret_mag_sqr = x * x + y * y */
PUB f64 vec2_mag_sqr(Vector2 v);

/* ret_dot = v1 ⋅ v2 */
PUB f64 vec2_dot(Vector2 v1, Vector2 v2);

/* ret_v = v scaled so that min_v <= |v| <= max_v (zero vector unchanged) */
PUB Vector2 vec2_clamp(Vector2 v, f64 min_v, f64 max_v);

/* ret_v = v1 + (v2 - v1) * t */
PUB Vector2 vec2_lerp(Vector2 v1, Vector2 v2, f64 t);

/******************************** VECTOR3 *************************************/

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

/******************************** VECTOR4 *************************************/

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

#endif /* VASALL_DEVKIT_VECTOR_H */
