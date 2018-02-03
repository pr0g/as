#pragma once

#include "as-math.hpp"
#include "as-vec.hpp"

namespace as
{

struct point2
{
    union
    {
        v2 v;
        struct { real x; real y; };
    };

    constexpr real& operator[](size_t i) { return v[i]; }
    constexpr const real& operator[](size_t i) const { return v[i]; }

    point2() = default;
    point2(const point2&) = default;
    point2& operator=(const point2&) = default;
    point2(point2&&) noexcept = default;
    point2& operator=(point2&&) noexcept = default;
    ~point2() = default;

    constexpr explicit point2(real xy) : x(xy), y(xy) {}
    constexpr explicit point2(const v2& v) : v(v) {}
    constexpr point2(real x, real y) : x(x), y(y) {}
};

using p2 = point2;

struct point3
{
    union
    {
        v3 v;
        struct { real x; real y; real z; };
        p2 xy;
    };

    constexpr real& operator[](size_t i) { return v[i]; }
    constexpr const real& operator[](size_t i) const { return v[i]; }

    point3() = default;
    point3(const point3&) = default;
    point3& operator=(const point3&) = default;
    point3(point3&&) noexcept = default;
    point3& operator=(point3&&) noexcept = default;
    ~point3() = default;

    constexpr explicit point3(real xyz) : x(xyz), y(xyz), z(xyz) {}
    constexpr explicit point3(const v3& v) : v(v) {}
    constexpr point3(real x, real y, real z) : x(x), y(y), z(z) {}
    constexpr point3(const v2& xy, real z) : x(xy.x), y(xy.y), z(z) {}
};

using p3 = point3;

inline v2 operator-(const p2& lhs, const p2& rhs);
inline p2 operator+(const p2& point, const v2& vec);
inline void operator+=(p2& point, const v2& vec);
inline p2 operator-(const p2& point, const v2& vec);
inline void operator-=(p2& point, const v2& vec);
inline bool equal(const p2& lhs, const p2& rhs,
    real epsilon = std::numeric_limits<real>::epsilon());

inline v3 operator-(const p3& lhs, const p3& rhs);
inline p3 operator+(const p3& point, const v3& vec);
inline void operator+=(p3& point, const v3& vec);
inline p3 operator-(const p3& point, const v3& vec);
inline void operator-=(p3& point, const v3& vec);
inline bool equal(const p3& lhs, const p3& rhs,
    real epsilon = std::numeric_limits<real>::epsilon());

} // namespace as

#include "as-point.inl"