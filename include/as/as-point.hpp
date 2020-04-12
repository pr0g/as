#pragma once

#include "as-math.hpp"
#include "as-vec.hpp"

namespace as
{

struct point2_t
{
    using value_type = real_t;

    point2_t() = default;
    point2_t(const point2_t&) = default;
    point2_t& operator=(const point2_t&) = default;
    point2_t(point2_t&&) noexcept = default;
    point2_t& operator=(point2_t&&) noexcept = default;
    ~point2_t() = default;

    constexpr explicit point2_t(real_t xy_);
    constexpr explicit point2_t(const vec2_t& v_);
    constexpr point2_t(real_t x_, real_t y_);

    real_t& operator[](index_t i) &;
    const real_t& operator[](index_t i) const&;
    real_t operator[](index_t i) &&;

    vec2_t v;
};

struct point3_t
{
    using value_type = real_t;

    point3_t() = default;
    point3_t(const point3_t&) = default;
    point3_t& operator=(const point3_t&) = default;
    point3_t(point3_t&&) noexcept = default;
    point3_t& operator=(point3_t&&) noexcept = default;
    ~point3_t() = default;

    constexpr explicit point3_t(real_t xyz_);
    constexpr explicit point3_t(const vec3_t& v_);
    constexpr point3_t(real_t x_, real_t y_, real_t z_);
    constexpr point3_t(const vec2_t& xy_, real_t z_);

    real_t& operator[](index_t i) &;
    const real_t& operator[](index_t i) const&;
    real_t operator[](index_t i) &&;

    vec3_t v;
};

const vec2_t operator-(const point2_t& lhs, const point2_t& rhs);
const point2_t operator+(const point2_t& point, const vec2_t& vec);
point2_t& operator+=(point2_t& point, const vec2_t& vec);
const point2_t operator-(const point2_t& point, const vec2_t& vec);
point2_t& operator-=(point2_t& point, const vec2_t& vec);

const vec3_t operator-(const point3_t& lhs, const point3_t& rhs);
const point3_t operator+(const point3_t& point, const vec3_t& vec);
point3_t& operator+=(point3_t& point, const vec3_t& vec);
const point3_t operator-(const point3_t& point, const vec3_t& vec);
point3_t& operator-=(point3_t& point, const vec3_t& vec);

} // namespace as

#include "as-point.inl"
