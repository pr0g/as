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

    constexpr real& operator[](size_t i) { return data[i]; }
    constexpr const real& operator[](size_t i) const { return data[i]; }

    quat() = default;
    quat(const quat&) = default;
    quat& operator=(const quat&) = default;
    quat(quat&&) noexcept = default;
    quat& operator=(quat&&) noexcept = default;
    ~quat() = default;

    constexpr quat(real r, real i, real j, real k) : r(r), i(i), j(j), k(k) {}
    constexpr quat(real r, const v3& ijk) : r(r), i(ijk.x), j(ijk.y), k(ijk.z) {}

    constexpr static quat identity() { return { 1.0f, 0.0f, 0.0f, 0.0f }; }
    constexpr inline static real dot(const quat& a, const quat& b);
    constexpr inline static real length_squared(const quat& a);
    constexpr inline static quat conjugate(const quat& a);
    
    inline static quat axis_angle(const v3& axis, real radians);
    inline static quat rotation_zxy(real x, real y, real z);
    inline static real length(const quat& a);
    inline static quat normalize(const quat& a);
    inline static quat inverse(const quat& a);
    inline static v3 rotate(const quat& q, const v3& v);
    inline static quat slerp(const quat& a, const quat& b, real u);
};

#ifdef _MSC_VER
__pragma(warning(pop))
#endif

constexpr inline quat operator*(const quat& a, const quat& b);
constexpr inline void operator*=(quat& a, const quat& b);
inline quat operator+(const quat& a, const quat& b);
inline quat operator/(const quat& a, real b);
inline quat operator*(real a, const quat& b);
inline quat operator*(const quat& a, real b);

}

#include "as-quat.inl"