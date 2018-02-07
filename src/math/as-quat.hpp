#pragma once

#include "as-vec.hpp"

namespace as
{

#ifdef _MSC_VER
__pragma(warning(push))
__pragma(warning(disable:4201))
#endif

struct quat_t
{
    union
    {
        real_t elem[4];
        struct { real_t w; real_t x; real_t y; real_t z; };
    };

    constexpr real_t& operator[](size_t x) { return elem[x]; }
    constexpr const real_t& operator[](size_t x) const { return elem[x]; }

    quat_t() = default;
    quat_t(const quat_t&) = default;
    quat_t& operator=(const quat_t&) = default;
    quat_t(quat_t&&) noexcept = default;
    quat_t& operator=(quat_t&&) noexcept = default;
    ~quat_t() = default;

    constexpr quat_t(real_t w, real_t x, real_t y, real_t z) : w(w), x(x), y(y), z(z) {}
    constexpr quat_t(real_t w, const vec3_t& xyz) : w(w), x(xyz.x), y(xyz.y), z(xyz.z) {}
};

#ifdef _MSC_VER
__pragma(warning(pop))
#endif

constexpr inline quat_t operator*(const quat_t& lhs, const quat_t& rhs);
constexpr inline void operator*=(quat_t& lhs, const quat_t& rhs);
inline quat_t operator+(const quat_t& lhs, const quat_t& rhs);
inline quat_t operator/(const quat_t& lhs, real_t rhs);
inline quat_t operator*(const quat_t& lhs, real_t rhs);

}

#include "as-quat.inl"