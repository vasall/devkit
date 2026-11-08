#ifndef VASALL_DEVKIT_QUATERNION_H
#define VASALL_DEVKIT_QUATERNION_H

#include <devkit/scope.h>
#include <devkit/types.h>

#include <devkit/math/vector.h>
#include <devkit/math/matrix.h>

/*
 * Quaternion q = w + xi + yj + zk
 *
 * Rotation quaternions are unit quaternions. They follow the same convention
 * as mat4_rotation(): right-handed, counter-clockwise rotation around the
 * axis when looking down it towards the origin.
 */
typedef struct Quaternion {
        f64 w;
        f64 x;
        f64 y;
        f64 z;
} Quaternion;

PUB Quaternion quat(f64 w, f64 x, f64 y, f64 z);
PUB Quaternion quat_zero(void);
PUB Quaternion quat_identity(void);

/* ret_q = rotation of rad around axis (axis does not need to be normalized) */
PUB Quaternion quat_axis_angle(Vector3 axis, f64 rad);

/*
 * ret_q = qz * qy * qx
 *
 * Rotates around x first, then y, then z (same as Rz * Ry * Rx).
 */
PUB Quaternion quat_euler(f64 x_rad, f64 y_rad, f64 z_rad);

/* ret_q = q1 + q2 */
PUB Quaternion quat_add(Quaternion q1, Quaternion q2);

/* ret_q = q1 - q2 */
PUB Quaternion quat_sub(Quaternion q1, Quaternion q2);

/* ret_q = q * scalar */
PUB Quaternion quat_scale(Quaternion q, f64 scalar);

/* ret_q = q1 * q2 (Hamilton product, applies q2 first, then q1) */
PUB Quaternion quat_mul(Quaternion q1, Quaternion q2);

/* ret_q = conjugate(q) = w - xi - yj - zk */
PUB Quaternion quat_conj(Quaternion q);

/* ret_q = conj(q) / |q|^2 (returns zero quaternion if |q| = 0) */
PUB Quaternion quat_inv(Quaternion q);

/* ret_q = q / |q| (returns identity if |q| = 0) */
PUB Quaternion quat_norm(Quaternion q);

/* ret_mag = sqrt(w * w + x * x + y * y + z * z) */
PUB f64 quat_mag(Quaternion q);

/* ret_mag_sqr = w * w + x * x + y * y + z * z */
PUB f64 quat_mag_sqr(Quaternion q);

/* ret_dot = q1 ⋅ q2 */
PUB f64 quat_dot(Quaternion q1, Quaternion q2);

/* ret_v = q * v * conj(q) (q must be a unit quaternion) */
PUB Vector3 quat_rotate(Quaternion q, Vector3 v);

/* ret_q = normalized linear interpolation, shortest path */
PUB Quaternion quat_nlerp(Quaternion q1, Quaternion q2, f64 t);

/* ret_q = spherical linear interpolation, shortest path */
PUB Quaternion quat_slerp(Quaternion q1, Quaternion q2, f64 t);

/* ret_m = rotation matrix of q (q must be a unit quaternion) */
PUB Matrix3 quat_to_mat3(Quaternion q);
PUB Matrix4 quat_to_mat4(Quaternion q);

/* ret_q = rotation of m (m must be a pure rotation matrix) */
PUB Quaternion quat_from_mat3(Matrix3 m);

#endif /* VASALL_DEVKIT_QUATERNION_H */
