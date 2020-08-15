//! \file
//! as-point

#pragma once

#include "as-math.hpp"
#include "as-vec.hpp"

namespace as
{

struct point2_t
{
    using value_type = real_t;

    point2_t() = default;
    constexpr explicit point2_t(real_t xy_);
    constexpr explicit point2_t(const vec2_t& v_);
    constexpr point2_t(real_t x_, real_t y_);

    real_t& operator[](index_t i) &;
    const real_t& operator[](index_t i) const&;
    real_t operator[](index_t i) &&;

    constexpr static index_t size();

    constexpr static point2_t zero();
    constexpr static point2_t axis_x(real_t len = 1.0_r);
    constexpr static point2_t axis_y(real_t len = 1.0_r);

    constexpr vec2_t as_vec() &&;
    constexpr const vec2_t& as_vec() const&;

private:
    friend constexpr const vec2_t operator-(
        const point2_t& lhs, const point2_t& rhs);
    friend constexpr const point2_t operator+(
        const point2_t& point, const vec2_t& vec);
    friend constexpr point2_t& operator+=(point2_t& point, const vec2_t& vec);
    friend constexpr const point2_t operator-(
        const point2_t& point, const vec2_t& vec);
    friend constexpr point2_t& operator-=(point2_t& point, const vec2_t& vec);
    friend const point2_t operator-(const point2_t& point);

    vec2_t v;
};

struct point3_t
{
    using value_type = real_t;

    point3_t() = default;

    constexpr explicit point3_t(real_t xyz_);
    constexpr explicit point3_t(const vec3_t& v_);
    constexpr point3_t(real_t x_, real_t y_, real_t z_);
    constexpr point3_t(const vec2_t& xy_, real_t z_);

    real_t& operator[](index_t i) &;
    const real_t& operator[](index_t i) const&;
    real_t operator[](index_t i) &&;

    constexpr static index_t size();

    constexpr static point3_t zero();
    constexpr static point3_t axis_x(real_t len = 1.0_r);
    constexpr static point3_t axis_y(real_t len = 1.0_r);
    constexpr static point3_t axis_z(real_t len = 1.0_r);

    constexpr vec3_t as_vec() &&;
    constexpr const vec3_t& as_vec() const&;

private:
    friend constexpr const vec3_t operator-(
        const point3_t& lhs, const point3_t& rhs);
    friend constexpr const point3_t operator+(
        const point3_t& point, const vec3_t& vec);
    friend constexpr point3_t& operator+=(point3_t& point, const vec3_t& vec);
    friend constexpr const point3_t operator-(
        const point3_t& point, const vec3_t& vec);
    friend constexpr point3_t& operator-=(point3_t& point, const vec3_t& vec);
    friend constexpr const point3_t operator-(const point3_t& point);

    vec3_t v;
};

} // namespace as

#include "as-point.inl"
