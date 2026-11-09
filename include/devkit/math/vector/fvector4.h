#ifndef VASALL_DEVKIT_FVECTOR4_H
#define VASALL_DEVKIT_FVECTOR4_H

#include <devkit/scope.h>
#include <devkit/types.h>

#include <devkit/math/vector/vector4.h>

typedef struct FVector4 {
        f32 x;
        f32 y;
        f32 z;
        f32 w;
} FVector4;

PUB FVector4 fvec4(f32 x, f32 y, f32 z, f32 w);
PUB FVector4 fvec4_zero(void);
PUB FVector4 fvec4_set(f32 value);

/* ret_v = v1 + v2 */
PUB FVector4 fvec4_add(FVector4 v1, FVector4 v2);

/* ret_v = v1 - v2 */
PUB FVector4 fvec4_sub(FVector4 v1, FVector4 v2);

/* ret_v = v * scalar */
PUB FVector4 fvec4_scale(FVector4 v, f32 scalar);

/* ret_v = v / |v| (returns zero vector if |v| = 0) */
PUB FVector4 fvec4_norm(FVector4 v);

/* ret_mag = sqrt(x * x + y * y + z * z + w * w) */
PUB f32 fvec4_mag(FVector4 v);

/* ret_mag_sqr = x * x + y * y + z * z + w * w */
PUB f32 fvec4_mag_sqr(FVector4 v);

/* ret_dot = v1 ⋅ v2 */
PUB f32 fvec4_dot(FVector4 v1, FVector4 v2);

/* ret_v = v scaled so that min_v <= |v| <= max_v (zero vector unchanged) */
PUB FVector4 fvec4_clamp(FVector4 v, f32 min_v, f32 max_v);

/* ret_v = v1 + (v2 - v1) * t */
PUB FVector4 fvec4_lerp(FVector4 v1, FVector4 v2, f32 t);

/* Convert between f64 and f32. Converting to f32 loses precision */
PUB FVector4 fvec4_from_vec4(Vector4 v);
PUB Vector4 vec4_from_fvec4(FVector4 v);

#endif /* VASALL_DEVKIT_FVECTOR4_H */
