#pragma once

#include "core/as-types.hpp"
#include "core/as-assert.hpp"

#include "as-math.hpp"

namespace as
{

struct point2
{
    union
    {
        v2 v;
        struct { real x; real y; };
    };

    AS_INLINE real& operator[](size_t i) { return v[i]; }
    AS_INLINE const real& operator[](size_t i) const { return v[i]; }

    explicit point2() = default;
    constexpr explicit point2(real xy) : x(xy), y(xy) {}
    constexpr explicit point2(real x, real y) : x(x), y(y) {}
    constexpr explicit point2(const v2& v) : v(v) {}
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

    AS_INLINE real& operator[](size_t i) { return v[i]; }
    AS_INLINE const real& operator[](size_t i) const { return v[i]; }

    explicit point3() = default;
    constexpr explicit point3(real xyz) : x(xyz), y(xyz), z(xyz) {}
    constexpr explicit point3(const v2& xy, real z) : x(xy.x), y(xy.y), z(z) {}
    constexpr explicit point3(real x, real y, real z) : x(x), y(y), z(z) {}
    constexpr explicit point3(const v3& v) : v(v) {}
};

using p3 = point3;

AS_INLINE v2 operator-(const p2& lhs, const p2& rhs)
{
    return lhs.v - rhs.v;
}

AS_INLINE p2 operator+(const p2& point, const v2& vec)
{
    return p2(point.v + vec);
}

AS_INLINE p2& operator+=(p2& point, const v2& vec)
{
    point.v += vec;
    return point;
}

AS_INLINE p2 operator-(const p2& point, const v2& vec)
{
    return p2(point.v - vec);
}

AS_INLINE p2& operator-=(p2& point, const v2& vec)
{
    point.v -= vec;
    return point;
}

AS_INLINE bool equal(const p2& lhs, const p2& rhs, real epsilon = std::numeric_limits<real>::epsilon())
{
    return equal(lhs.v, rhs.v, epsilon);
}

AS_INLINE v3 operator-(const p3& lhs, const p3& rhs)
{
    return lhs.v - rhs.v;
}

AS_INLINE p3 operator+(const p3& point, const v3& vec)
{
    return p3(point.v + vec);
}

AS_INLINE p3& operator+=(p3& point, const v3& vec)
{
    point.v += vec;
    return point;
}

AS_INLINE p3 operator-(const p3& point, const v3& vec)
{
    return p3(point.v - vec);
}

AS_INLINE p3& operator-=(p3& point, const v3& vec)
{
    point.v -= vec;
    return point;
}

AS_INLINE bool equal(const p3& lhs, const p3& rhs, real epsilon = std::numeric_limits<real>::epsilon())
{
    return equal(lhs.v, rhs.v, epsilon);
}

}