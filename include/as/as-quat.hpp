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

    AS_API constexpr quat_t(real_t w, real_t x, real_t y, real_t z) : w(w), x(x), y(y), z(z) {}
    AS_API constexpr quat_t(real_t w, const vec3_t& xyz) : w(w), x(xyz.x), y(xyz.y), z(xyz.z) {}
};

AS_API constexpr const quat_t operator*(const quat_t& lhs, const quat_t& rhs);
AS_API constexpr quat_t& operator*=(quat_t& lhs, const quat_t& rhs);
AS_API const quat_t operator+(const quat_t& lhs, const quat_t& rhs);
AS_API const quat_t operator-(const quat_t& lhs, const quat_t& rhs);
AS_API const quat_t operator-(const quat_t& q);
AS_API const quat_t operator/(const quat_t& lhs, real_t rhs);
AS_API const quat_t operator*(const quat_t& lhs, real_t rhs);

} // namespace as

#include "as-quat.inl"
