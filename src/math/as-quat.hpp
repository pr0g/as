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
        real elem[4];
        struct { real r; real i; real j; real k; };
    };

    constexpr real& operator[](size_t i) { return elem[i]; }
    constexpr const real& operator[](size_t i) const { return elem[i]; }

    quat() = default;
    quat(const quat&) = default;
    quat& operator=(const quat&) = default;
    quat(quat&&) noexcept = default;
    quat& operator=(quat&&) noexcept = default;
    ~quat() = default;

    constexpr quat(real r, real i, real j, real k) : r(r), i(i), j(j), k(k) {}
    constexpr quat(real r, const v3& ijk) : r(r), i(ijk.x), j(ijk.y), k(ijk.z) {}
};

#ifdef _MSC_VER
__pragma(warning(pop))
#endif

constexpr inline quat operator*(const quat& lhs, const quat& rhs);
constexpr inline void operator*=(quat& lhs, const quat& rhs);
inline quat operator+(const quat& lhs, const quat& rhs);
inline quat operator/(const quat& lhs, real rhs);
inline quat operator*(const quat& lhs, real rhs);

}

#include "as-quat.inl"