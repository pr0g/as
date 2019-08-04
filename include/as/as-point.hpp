#pragma once

#include "as-math.hpp"
#include "as-vec.hpp"

namespace as
{

struct point2_t
{
    vec2_t v;

    AS_API real_t& operator[](size_t i) & { return v[i]; }
    AS_API const real_t& operator[](size_t i) const& { return v[i]; }
    AS_API real_t operator[](size_t i) && { return v[i]; }

    point2_t() = default;
    point2_t(const point2_t&) = default;
    point2_t& operator=(const point2_t&) = default;
    point2_t(point2_t&&) noexcept = default;
    point2_t& operator=(point2_t&&) noexcept = default;
    ~point2_t() = default;

    AS_API constexpr explicit point2_t(real_t xy_) : v { xy_, xy_ } {}
    AS_API constexpr explicit point2_t(const vec2_t& v_) : v(v_) {}
    AS_API constexpr point2_t(real_t x_, real_t y_) : v { x_, y_ } {}
};

struct point3_t
{
    vec3_t v;

    AS_API real_t& operator[](size_t i) & { return v[i]; }
    AS_API const real_t& operator[](size_t i) const& { return v[i]; }
    AS_API real_t operator[](size_t i) && { return v[i]; }

    point3_t() = default;
    point3_t(const point3_t&) = default;
    point3_t& operator=(const point3_t&) = default;
    point3_t(point3_t&&) noexcept = default;
    point3_t& operator=(point3_t&&) noexcept = default;
    ~point3_t() = default;

    AS_API constexpr explicit point3_t(real_t xyz_) : v { xyz_, xyz_, xyz_ } {}
    AS_API constexpr explicit point3_t(const vec3_t& v_) : v(v_) {}
    AS_API constexpr point3_t(real_t x_, real_t y_, real_t z_) : v { x_, y_, z_ } {}
    AS_API constexpr point3_t(const vec2_t& xy_, real_t z_) : v { xy_.x, xy_.y, z_ } {}
};

AS_API const vec2_t operator-(const point2_t& lhs, const point2_t& rhs);
AS_API const point2_t operator+(const point2_t& point, const vec2_t& vec);
AS_API point2_t& operator+=(point2_t& point, const vec2_t& vec);
AS_API const point2_t operator-(const point2_t& point, const vec2_t& vec);
AS_API point2_t& operator-=(point2_t& point, const vec2_t& vec);

AS_API const vec3_t operator-(const point3_t& lhs, const point3_t& rhs);
AS_API const point3_t operator+(const point3_t& point, const vec3_t& vec);
AS_API point3_t& operator+=(point3_t& point, const vec3_t& vec);
AS_API const point3_t operator-(const point3_t& point, const vec3_t& vec);
AS_API point3_t& operator-=(point3_t& point, const vec3_t& vec);

} // namespace as

#include "as-point.inl"
