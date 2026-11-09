#ifndef VASALL_DEVKIT_FVECTOR2_H
#define VASALL_DEVKIT_FVECTOR2_H

#include <devkit/scope.h>
#include <devkit/types.h>

#include <devkit/math/vector/vector2.h>

typedef struct FVector2 {
        f32 x;
        f32 y;
} FVector2;

PUB FVector2 fvec2(f32 x, f32 y);
PUB FVector2 fvec2_zero(void);
PUB FVector2 fvec2_set(f32 value);

/* ret_v = v1 + v2 */
PUB FVector2 fvec2_add(FVector2 v1, FVector2 v2);

/* ret_v = v1 - v2 */
PUB FVector2 fvec2_sub(FVector2 v1, FVector2 v2);

/* ret_v = v * scalar */
PUB FVector2 fvec2_scale(FVector2 v, f32 scalar);

/* ret_v = v / |v| (returns zero vector if |v| = 0) */
PUB FVector2 fvec2_norm(FVector2 v);

/* ret_mag = sqrt(x * x + y * y) */
PUB f32 fvec2_mag(FVector2 v);

/* ret_mag_sqr = x * x + y * y */
PUB f32 fvec2_mag_sqr(FVector2 v);

/* ret_dot = v1 ⋅ v2 */
PUB f32 fvec2_dot(FVector2 v1, FVector2 v2);

/* ret_v = v scaled so that min_v <= |v| <= max_v (zero vector unchanged) */
PUB FVector2 fvec2_clamp(FVector2 v, f32 min_v, f32 max_v);

/* ret_v = v1 + (v2 - v1) * t */
PUB FVector2 fvec2_lerp(FVector2 v1, FVector2 v2, f32 t);

/* Convert between f64 and f32. Converting to f32 loses precision */
PUB FVector2 fvec2_from_vec2(Vector2 v);
PUB Vector2 vec2_from_fvec2(FVector2 v);

#endif /* VASALL_DEVKIT_FVECTOR2_H */
