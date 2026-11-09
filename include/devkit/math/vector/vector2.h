#ifndef VASALL_DEVKIT_VECTOR2_H
#define VASALL_DEVKIT_VECTOR2_H

#include <devkit/scope.h>
#include <devkit/types.h>

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

#endif /* VASALL_DEVKIT_VECTOR2_H */
