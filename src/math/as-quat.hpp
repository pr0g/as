#pragma once

#include "as-vec.hpp"

namespace as
{

#ifdef _MSC_VER
__pragma(warning(push))
__pragma(warning(disable:4201))
#endif

struct quat
{
    union
    {
        real data[4];
        struct { real r; real i; real j; real k; };
    };

    AS_INLINE real& operator[](int i) { return data[i]; }
    AS_INLINE const real& operator[](int i) const { return data[i]; }
};

#ifdef _MSC_VER
__pragma(warning(pop))
#endif

AS_INLINE quat make_quat(real r, real i, real j, real k)
{
    quat result;
    result.r = r;
    result.i = i;
    result.j = j;
    result.k = k;
    return result;
}

AS_INLINE quat make_quat(real r, const v3& ijk)
{
    quat result;
    result.r = r;
    result.i = ijk.x;
    result.j = ijk.y;
    result.k = ijk.z;
    return result;
}

AS_INLINE quat identity()
{
    quat result;
    result.r = 1.0f;
    result.i = 0.0f;
    result.j = 0.0f;
    result.k = 0.0f;
    return result;
}

AS_INLINE quat operator*(const quat& a, const quat& b)
{
    return make_quat(a.r*b.r - a.i*b.i - a.j*b.j - a.k*b.k,
                     a.r*b.i + a.i*b.r + a.j*b.k - a.k*b.j,
                     a.r*b.j + a.j*b.r + a.k*b.i - a.i*b.k,
                     a.r*b.k + a.k*b.r + a.i*b.j - a.j*b.i);
}

AS_INLINE quat operator*=(quat& a, quat& b)
{
    a = a * b;
    return a;
}

AS_INLINE quat operator+(const quat& a, const quat& b)
{
    quat result;
    for (int i = 0; i < 4; ++i) {
        result.data[i] = a.data[i] + b.data[i];
    }
    return result;
}

AS_INLINE quat operator/(real a, const quat& b)
{
    quat result;
    for (size_t i = 0; i < 4; ++i) {
        result.data[i] = a / b.data[i];
    }
    return result;
}

AS_INLINE quat operator/(const quat& a, real b)
{
    quat result;
    for (int i = 0; i < 4; ++i) {
        result.data[i] = a.data[i] / b;
    }
    return result;
}

AS_INLINE quat operator*(real a, const quat& b)
{
    quat result;
    for (size_t i = 0; i < 4; ++i) {
        result.data[i] = a * b.data[i];
    }
    return result;
}

AS_INLINE quat operator*(const quat& a, real b)
{
    quat result;
    for (int i = 0; i < 4; ++i) {
        result.data[i] = a.data[i] * b;
    }
    return result;
}

AS_INLINE real dot(const quat& a, const quat& b)
{
    return a.r*b.r + a.i*b.i + a.j*b.j + a.k*b.k;
}

AS_INLINE real lengthSquared(const quat& a)
{
    return dot(a, a);
}

AS_INLINE real length(const quat& a)
{
    return std::sqrt(lengthSquared(a));
}

AS_INLINE quat normalize(const quat& a)
{
    return a / length(a);
}

AS_INLINE quat conjugate(const quat& a)
{
    return make_quat(a.r, -a.i, -a.j, -a.k);
}

AS_INLINE quat inverse(const quat& a)
{
    return conjugate(a) / lengthSquared(a);
}

AS_INLINE v3 rotate(const quat& q, const v3& v)
{
    quat t = make_quat( 0, v.x, v.y, v.z );
    quat quat_result = q * t * conjugate(q);
    return v3(quat_result.i, quat_result.j, quat_result.k);
}

AS_INLINE quat quat_rotation_axis_angle(const v3& axis, real radians)
{
    real sinHalfTheta = sinr(0.5f * radians);
    real cosHalfTheta = cosr(0.5f * radians);

    return make_quat(cosHalfTheta, axis * sinHalfTheta);
}

AS_INLINE quat quat_rotation_zxy(real x, real y, real z)
{
    real sinHalfX = sinr(0.5f * x);
    real cosHalfX = cosr(0.5f * x);
    real sinHalfY = sinr(0.5f * y);
    real cosHalfY = cosr(0.5f * y);
    real sinHalfZ = sinr(0.5f * z);
    real cosHalfZ = cosr(0.5f * z);

    quat quatX = make_quat(cosHalfX, sinHalfX, 0, 0);
    quat quatY = make_quat(cosHalfY, 0, sinHalfY, 0);
    quat quatZ = make_quat(cosHalfZ, 0, 0, sinHalfZ);

    return quatY * quatX * quatZ;
}

quat slerp(const quat& a, const quat& b, real u)
{
    real theta = acosr(dot(a, b));
    return (a * sinr((1.0f - u) * theta) + b * sinr(u * theta)) / sinr(theta);
}

}