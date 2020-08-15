//! \file
//! as-quat

#pragma once

#include "as-vec.hpp"

namespace as
{

struct quat_t
{
    using value_type = real_t;

    quat_t() = default;
    constexpr quat_t(real_t w_, real_t x_, real_t y_, real_t z_);
    constexpr quat_t(real_t w_, const vec3_t& xyz_);

    constexpr static quat_t identity();

    real_t w, x, y, z;
};

constexpr const quat_t operator*(const quat_t& lhs, const quat_t& rhs);
constexpr quat_t& operator*=(quat_t& lhs, const quat_t& rhs);
constexpr const quat_t operator+(const quat_t& lhs, const quat_t& rhs);
constexpr const quat_t operator-(const quat_t& lhs, const quat_t& rhs);
constexpr const quat_t operator-(const quat_t& q);
constexpr const quat_t operator/(const quat_t& lhs, real_t rhs);
constexpr const quat_t operator*(const quat_t& lhs, real_t rhs);

} // namespace as

#include "as-quat.inl"
