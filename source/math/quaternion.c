#include <devkit/math/quaternion.h>

#include <math.h>

/* Below this dot product, slerp switches to nlerp to avoid dividing by ~0 */
#define QUAT_SLERP_THRESHOLD 0.9995

PUB Quaternion quat(f64 w, f64 x, f64 y, f64 z)
{
        Quaternion q;
        q.w = w;
        q.x = x;
        q.y = y;
        q.z = z;
        return q;
}

PUB Quaternion quat_zero(void)
{
        return quat(0, 0, 0, 0);
}

PUB Quaternion quat_identity(void)
{
        return quat(1, 0, 0, 0);
}

PUB Quaternion quat_axis_angle(Vector3 axis, f64 rad)
{
        f64 mag = vec3_mag(axis);
        f64 s;

        if(mag == 0) {
                return quat_identity();
        }

        s = sin(rad * 0.5) / mag;
        return quat(cos(rad * 0.5), axis.x * s, axis.y * s, axis.z * s);
}

PUB Quaternion quat_euler(f64 x_rad, f64 y_rad, f64 z_rad)
{
        f64 cx = cos(x_rad * 0.5);
        f64 sx = sin(x_rad * 0.5);
        f64 cy = cos(y_rad * 0.5);
        f64 sy = sin(y_rad * 0.5);
        f64 cz = cos(z_rad * 0.5);
        f64 sz = sin(z_rad * 0.5);

        return quat(
            cz * cy * cx + sz * sy * sx,
            cz * cy * sx - sz * sy * cx,
            cz * sy * cx + sz * cy * sx,
            sz * cy * cx - cz * sy * sx
        );
}

PUB Quaternion quat_add(Quaternion q1, Quaternion q2)
{
        return quat(q1.w + q2.w, q1.x + q2.x, q1.y + q2.y, q1.z + q2.z);
}

PUB Quaternion quat_sub(Quaternion q1, Quaternion q2)
{
        return quat(q1.w - q2.w, q1.x - q2.x, q1.y - q2.y, q1.z - q2.z);
}

PUB Quaternion quat_scale(Quaternion q, f64 scalar)
{
        return quat(q.w * scalar, q.x * scalar, q.y * scalar, q.z * scalar);
}

PUB Quaternion quat_mul(Quaternion q1, Quaternion q2)
{
        Quaternion q;
        q.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
        q.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
        q.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
        q.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
        return q;
}

PUB Quaternion quat_conj(Quaternion q)
{
        return quat(q.w, -q.x, -q.y, -q.z);
}

PUB Quaternion quat_inv(Quaternion q)
{
        f64 mag_sqr = quat_mag_sqr(q);

        if(mag_sqr == 0) {
                return quat_zero();
        }

        return quat_scale(quat_conj(q), 1.0 / mag_sqr);
}

PUB Quaternion quat_norm(Quaternion q)
{
        f64 mag = quat_mag(q);

        if(mag == 0) {
                return quat_identity();
        }

        return quat_scale(q, 1.0 / mag);
}

PUB f64 quat_mag(Quaternion q)
{
        return sqrt(quat_mag_sqr(q));
}

PUB f64 quat_mag_sqr(Quaternion q)
{
        return q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z;
}

PUB f64 quat_dot(Quaternion q1, Quaternion q2)
{
        return q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;
}

PUB Vector3 quat_rotate(Quaternion q, Vector3 v)
{
        /* v' = v + 2w(u x v) + 2(u x (u x v)), with u = (x, y, z) */
        Vector3 u = vec3(q.x, q.y, q.z);
        Vector3 t = vec3_scale(vec3_cross(u, v), 2.0);

        return vec3_add(vec3_add(v, vec3_scale(t, q.w)), vec3_cross(u, t));
}

PUB Quaternion quat_nlerp(Quaternion q1, Quaternion q2, f64 t)
{
        /* q and -q are the same rotation, pick the one closer to q1 */
        if(quat_dot(q1, q2) < 0) {
                q2 = quat_scale(q2, -1.0);
        }

        return quat_norm(quat_add(quat_scale(q1, 1.0 - t),
                                  quat_scale(q2, t)));
}

PUB Quaternion quat_slerp(Quaternion q1, Quaternion q2, f64 t)
{
        f64 dot = quat_dot(q1, q2);
        f64 theta;
        f64 sin_theta;
        f64 s1;
        f64 s2;

        if(dot < 0) {
                q2 = quat_scale(q2, -1.0);
                dot = -dot;
        }

        if(dot > QUAT_SLERP_THRESHOLD) {
                return quat_nlerp(q1, q2, t);
        }

        theta = acos(dot);
        sin_theta = sin(theta);
        s1 = sin((1.0 - t) * theta) / sin_theta;
        s2 = sin(t * theta) / sin_theta;

        return quat_add(quat_scale(q1, s1), quat_scale(q2, s2));
}

PUB Matrix3 quat_to_mat3(Quaternion q)
{
        Matrix3 m;
        f64 xx = q.x * q.x, yy = q.y * q.y, zz = q.z * q.z;
        f64 xy = q.x * q.y, xz = q.x * q.z, yz = q.y * q.z;
        f64 wx = q.w * q.x, wy = q.w * q.y, wz = q.w * q.z;

        /* column 0 */
        m.data[0] = 1.0 - 2.0 * (yy + zz);
        m.data[1] = 2.0 * (xy + wz);
        m.data[2] = 2.0 * (xz - wy);

        /* column 1 */
        m.data[3] = 2.0 * (xy - wz);
        m.data[4] = 1.0 - 2.0 * (xx + zz);
        m.data[5] = 2.0 * (yz + wx);

        /* column 2 */
        m.data[6] = 2.0 * (xz + wy);
        m.data[7] = 2.0 * (yz - wx);
        m.data[8] = 1.0 - 2.0 * (xx + yy);

        return m;
}

PUB Matrix4 quat_to_mat4(Quaternion q)
{
        Matrix3 r = quat_to_mat3(q);
        Matrix4 m = mat4_identity();
        s32 col;
        s32 row;

        for(col = 0; col < 3; col++) {
                for(row = 0; row < 3; row++) {
                        m.data[col * 4 + row] = r.data[col * 3 + row];
                }
        }

        return m;
}

PUB Quaternion quat_from_mat3(Matrix3 m)
{
        /* m(row, col) with column-major storage */
        f64 m00 = m.data[0], m10 = m.data[1], m20 = m.data[2];
        f64 m01 = m.data[3], m11 = m.data[4], m21 = m.data[5];
        f64 m02 = m.data[6], m12 = m.data[7], m22 = m.data[8];
        f64 trace = m00 + m11 + m22;
        f64 s;

        /* Pick the largest component as divisor for numerical stability */
        if(trace > 0) {
                s = sqrt(trace + 1.0) * 2.0;
                return quat_norm(quat(0.25 * s,
                                      (m21 - m12) / s,
                                      (m02 - m20) / s,
                                      (m10 - m01) / s));
        }
        else if(m00 > m11 && m00 > m22) {
                s = sqrt(1.0 + m00 - m11 - m22) * 2.0;
                return quat_norm(quat((m21 - m12) / s,
                                      0.25 * s,
                                      (m01 + m10) / s,
                                      (m02 + m20) / s));
        }
        else if(m11 > m22) {
                s = sqrt(1.0 + m11 - m00 - m22) * 2.0;
                return quat_norm(quat((m02 - m20) / s,
                                      (m01 + m10) / s,
                                      0.25 * s,
                                      (m12 + m21) / s));
        }
        else {
                s = sqrt(1.0 + m22 - m00 - m11) * 2.0;
                return quat_norm(quat((m10 - m01) / s,
                                      (m02 + m20) / s,
                                      (m12 + m21) / s,
                                      0.25 * s));
        }
}
