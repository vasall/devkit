#ifndef VASALL_DEVKIT_FVECTOR3_H
#define VASALL_DEVKIT_FVECTOR3_H

#include <devkit/scope.h>
#include <devkit/types.h>

#include <devkit/math/vector/vector3.h>

typedef struct FVector3 {
        f32 x;
        f32 y;
        f32 z;
} FVector3;

PUB FVector3 fvec3(f32 x, f32 y, f32 z);
PUB FVector3 fvec3_zero(void);
PUB FVector3 fvec3_set(f32 value);

/* ret_v = v1 + v2 */
PUB FVector3 fvec3_add(FVector3 v1, FVector3 v2);

/* ret_v = v1 - v2 */
PUB FVector3 fvec3_sub(FVector3 v1, FVector3 v2);

/* ret_v = v * scalar */
PUB FVector3 fvec3_scale(FVector3 v, f32 scalar);

/* ret_v = v / |v| (returns zero vector if |v| = 0) */
PUB FVector3 fvec3_norm(FVector3 v);

/* ret_mag = sqrt(x * x + y * y + z * z) */
PUB f32 fvec3_mag(FVector3 v);

/* ret_mag_sqr = x * x + y * y + z * z */
PUB f32 fvec3_mag_sqr(FVector3 v);

/* ret_dot = v1 ⋅ v2 */
PUB f32 fvec3_dot(FVector3 v1, FVector3 v2);

/* ret_v = v1 x v2 */
PUB FVector3 fvec3_cross(FVector3 v1, FVector3 v2);

/* ret_v = v scaled so that min_v <= |v| <= max_v (zero vector unchanged) */
PUB FVector3 fvec3_clamp(FVector3 v, f32 min_v, f32 max_v);

/* ret_v = v1 + (v2 - v1) * t */
PUB FVector3 fvec3_lerp(FVector3 v1, FVector3 v2, f32 t);

/* Convert between f64 and f32. Converting to f32 loses precision */
PUB FVector3 fvec3_from_vec3(Vector3 v);
PUB Vector3 vec3_from_fvec3(FVector3 v);

#endif /* VASALL_DEVKIT_FVECTOR3_H */
