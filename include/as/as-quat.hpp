#pragma once

#include "as-vec.hpp"

namespace as
{

struct quat_t
{
    using value_type = real_t;

    quat_t() = default;
    quat_t(const quat_t&) = default;
    quat_t& operator=(const quat_t&) = default;
    quat_t(quat_t&&) noexcept = default;
    quat_t& operator=(quat_t&&) noexcept = default;
    ~quat_t() = default;

    constexpr quat_t(real_t w_, real_t x_, real_t y_, real_t z_);
    constexpr quat_t(real_t w_, const vec3_t& xyz_);

    real_t w, x, y, z;
};

constexpr const quat_t operator*(const quat_t& lhs, const quat_t& rhs);
constexpr quat_t& operator*=(quat_t& lhs, const quat_t& rhs);
const quat_t operator+(const quat_t& lhs, const quat_t& rhs);
const quat_t operator-(const quat_t& lhs, const quat_t& rhs);
const quat_t operator-(const quat_t& q);
const quat_t operator/(const quat_t& lhs, real_t rhs);
const quat_t operator*(const quat_t& lhs, real_t rhs);

} // namespace as

#include "as-quat.inl"
