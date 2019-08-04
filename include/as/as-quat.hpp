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

    AS_API constexpr quat_t(real_t w_, real_t x_, real_t y_, real_t z_)
        : w(w_), x(x_), y(y_), z(z_) {}

    AS_API constexpr quat_t(real_t w_, const vec3_t& xyz_)
        : w(w_), x(xyz_.x), y(xyz_.y), z(xyz_.z) {}
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
