#pragma once

#include "as-math.hpp"
#include "as-vec.hpp"

namespace as
{

struct point2_t
{
    union
    {
        vec2_t v;
        struct { real_t x; real_t y; };
    };

    constexpr real_t& operator[](size_t i) { return v[i]; }
    constexpr const real_t& operator[](size_t i) const { return v[i]; }

    point2_t() = default;
    point2_t(const point2_t&) = default;
    point2_t& operator=(const point2_t&) = default;
    point2_t(point2_t&&) noexcept = default;
    point2_t& operator=(point2_t&&) noexcept = default;
    ~point2_t() = default;

    constexpr explicit point2_t(real_t xy) : x(xy), y(xy) {}
    constexpr explicit point2_t(const vec2_t& v) : v(v) {}
    constexpr point2_t(real_t x, real_t y) : x(x), y(y) {}
};

struct point3_t
{
    union
    {
        vec3_t v;
        struct { real_t x; real_t y; real_t z; };
        point2_t xy;
    };

    constexpr real_t& operator[](size_t i) { return v[i]; }
    constexpr const real_t& operator[](size_t i) const { return v[i]; }

    point3_t() = default;
    point3_t(const point3_t&) = default;
    point3_t& operator=(const point3_t&) = default;
    point3_t(point3_t&&) noexcept = default;
    point3_t& operator=(point3_t&&) noexcept = default;
    ~point3_t() = default;

    constexpr explicit point3_t(real_t xyz) : x(xyz), y(xyz), z(xyz) {}
    constexpr explicit point3_t(const vec3_t& v) : v(v) {}
    constexpr point3_t(real_t x, real_t y, real_t z) : x(x), y(y), z(z) {}
    constexpr point3_t(const vec2_t& xy, real_t z) : x(xy.x), y(xy.y), z(z) {}
};

inline vec2_t operator-(const point2_t& lhs, const point2_t& rhs);
inline point2_t operator+(const point2_t& point, const vec2_t& vec);
inline void operator+=(point2_t& point, const vec2_t& vec);
inline point2_t operator-(const point2_t& point, const vec2_t& vec);
inline void operator-=(point2_t& point, const vec2_t& vec);

inline vec3_t operator-(const point3_t& lhs, const point3_t& rhs);
inline point3_t operator+(const point3_t& point, const vec3_t& vec);
inline void operator+=(point3_t& point, const vec3_t& vec);
inline point3_t operator-(const point3_t& point, const vec3_t& vec);
inline void operator-=(point3_t& point, const vec3_t& vec);

} // namespace as

#include "as-point.inl"