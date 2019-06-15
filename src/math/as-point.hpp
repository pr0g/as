#pragma once

#include "as-math.hpp"
#include "as-vec.hpp"

namespace as
{

struct point2_t
{
    vec2_t v;

    real_t& operator[](size_t i) { return v[i]; }
    const real_t& operator[](size_t i) const { return v[i]; }

    point2_t() = default;
    point2_t(const point2_t&) = default;
    point2_t& operator=(const point2_t&) = default;
    point2_t(point2_t&&) noexcept = default;
    point2_t& operator=(point2_t&&) noexcept = default;
    ~point2_t() = default;

    constexpr explicit point2_t(real_t xy) : v { xy, xy } {}
    constexpr explicit point2_t(const vec2_t& v) : v(v) {}
    constexpr point2_t(real_t x, real_t y) : v { x, y } {}
};

struct point3_t
{
    vec3_t v;

    real_t& operator[](size_t i) { return v[i]; }
    const real_t& operator[](size_t i) const { return v[i]; }

    point3_t() = default;
    point3_t(const point3_t&) = default;
    point3_t& operator=(const point3_t&) = default;
    point3_t(point3_t&&) noexcept = default;
    point3_t& operator=(point3_t&&) noexcept = default;
    ~point3_t() = default;

    constexpr explicit point3_t(real_t xyz) : v { xyz, xyz, xyz } {}
    constexpr explicit point3_t(const vec3_t& v) : v(v) {}
    constexpr point3_t(real_t x, real_t y, real_t z) : v { x, y, z } {}
    constexpr point3_t(const vec2_t& xy, real_t z) : v { xy.x, xy.y, z } {}
};

inline const vec2_t operator-(const point2_t& lhs, const point2_t& rhs);
inline const point2_t operator+(const point2_t& point, const vec2_t& vec);
inline point2_t& operator+=(point2_t& point, const vec2_t& vec);
inline const point2_t operator-(const point2_t& point, const vec2_t& vec);
inline point2_t& operator-=(point2_t& point, const vec2_t& vec);

inline const vec3_t operator-(const point3_t& lhs, const point3_t& rhs);
inline const point3_t operator+(const point3_t& point, const vec3_t& vec);
inline point3_t& operator+=(point3_t& point, const vec3_t& vec);
inline const point3_t operator-(const point3_t& point, const vec3_t& vec);
inline point3_t& operator-=(point3_t& point, const vec3_t& vec);

} // namespace as

#include "as-point.inl"
