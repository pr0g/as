#pragma once

#include "as-vec.hpp"

namespace as
{

struct quat_t
{
    real_t w, x, y, z;

    quat_t() = default;
    quat_t(const quat_t&) = default;
    quat_t& operator=(const quat_t&) = default;
    quat_t(quat_t&&) noexcept = default;
    quat_t& operator=(quat_t&&) noexcept = default;
    ~quat_t() = default;

    constexpr quat_t(real_t w, real_t x, real_t y, real_t z) : w(w), x(x), y(y), z(z) {}
    constexpr quat_t(real_t w, const vec3_t& xyz) : w(w), x(xyz.x), y(xyz.y), z(xyz.z) {}
};

constexpr inline const quat_t operator*(const quat_t& lhs, const quat_t& rhs);
constexpr inline quat_t& operator*=(quat_t& lhs, const quat_t& rhs);
inline const quat_t operator+(const quat_t& lhs, const quat_t& rhs);
inline const quat_t operator-(const quat_t& lhs, const quat_t& rhs);
inline const quat_t operator-(const quat_t& q);
inline const quat_t operator/(const quat_t& lhs, real_t rhs);
inline const quat_t operator*(const quat_t& lhs, real_t rhs);

} // namespace as

#include "as-quat.inl"
