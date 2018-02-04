#pragma once

#include <algorithm>
#include <type_traits>

#include "core/as-types.hpp"
#include "core/as-assert.hpp"

#include "as-math.hpp"

namespace as
{

template<typename T, size_t n>
struct Vec
{
    T elem[n];
    static const size_t size = n;

    constexpr T& operator[](size_t i) { return elem[i]; }
    constexpr const T& operator[](size_t i) const { return elem[i]; }

    Vec() = default;
    Vec(const Vec&) = default;
    Vec& operator=(const Vec&) = default;
    Vec(Vec&&) noexcept = default;
    Vec& operator=(Vec&&) noexcept = default;
    ~Vec() = default;

    template<typename...> struct typelist;
    template<typename... Args, typename = std::enable_if_t<!std::is_same<typelist<Vec>, typelist<std::decay_t<Args>...>>::value>>
    Vec(Args... args) noexcept : elem{ std::forward<Args>(args)... } {}
};

template<>
struct Vec<real, 2>
{
    union
    {
        real elem[2];
        struct { real x; real y; };
    };

    static const size_t size = 2;

    constexpr real& operator[](size_t i) { return elem[i]; }
    constexpr const real& operator[](size_t i) const { return elem[i]; }

    Vec() = default;
    Vec(const Vec&) = default;
    Vec& operator=(const Vec&) = default;
    Vec(Vec&&) noexcept = default;
    Vec& operator=(Vec&&) noexcept = default;
    ~Vec() = default;

    constexpr explicit Vec(real xy) : x(xy), y(xy) {}
    constexpr Vec(real x, real y) : x(x), y(y) {}
};

using v2 = Vec<real, 2>;

template<>
struct Vec<real, 3>
{
    union
    {
        real elem[3];
        struct { real x; real y; real z; };
    };

    static const size_t size = 3;

    constexpr real& operator[](size_t i) { return elem[i]; }
    constexpr const real& operator[](size_t i) const { return elem[i]; }

    Vec() = default;
    Vec(const Vec&) = default;
    Vec& operator=(const Vec&) = default;
    Vec(Vec&&) noexcept = default;
    Vec& operator=(Vec&&) noexcept = default;
    ~Vec() = default;

    constexpr explicit Vec(real xyz) : x(xyz), y(xyz), z(xyz) {}
    constexpr Vec(const v2& xy, real z) : x(xy.x), y(xy.y), z(z) {}
    constexpr Vec(real x, real y, real z) : x(x), y(y), z(z) {}

    constexpr v2 xy() const { return { x, y }; }
};

using v3 = Vec<real, 3>;

template<>
struct Vec<real, 4>
{
    union
    {
        real elem[4];
        struct { real x; real y; real z; real w; };
    };

    static const size_t size = 4;

    constexpr real& operator[](size_t i) { return elem[i]; }
    constexpr const real& operator[](size_t i) const { return elem[i]; }

    Vec() = default;
    Vec(const Vec&) = default;
    Vec& operator=(const Vec&) = default;
    Vec(Vec&&) noexcept = default;
    Vec& operator=(Vec&&) noexcept = default;
    ~Vec() = default;

    constexpr explicit Vec(real xyzw) : x(xyzw), y(xyzw), z(xyzw), w(xyzw) {}
    constexpr Vec(const v3& xyz, real w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}
    constexpr Vec(const v2& xy, real z, real w) : x(xy.x), y(xy.y), z(z), w(w) {}
    constexpr Vec(const v2& xy, const v2& zw) : x(xy.x), y(xy.y), z(zw.x), w(zw.y) {}
    constexpr Vec(real x, real y, real z, real w) : x(x), y(y), z(z), w(w) {}

    constexpr v2 xy() const { return { x, y }; }
    constexpr v2 zw() const { return { z, w }; }
    constexpr v3 xyz() const { return { x, y, z }; }
};

using v4 = Vec<real, 4>;

template<typename T, size_t n>
inline Vec<T, n> operator+(const Vec<T, n>& lhs, const Vec<T, n>& rhs);

template<typename T, size_t n>
inline Vec<T, n>& operator+=(Vec<T, n>& lhs, const Vec<T, n>& rhs);

template<typename T, size_t n>
inline Vec<T, n> operator-(const Vec<T, n>& lhs, const Vec<T, n>& rhs);

template<typename T, size_t n>
inline Vec<T, n>& operator-=(Vec<T, n>& lhs, const Vec<T, n>& rhs);

template<typename T, size_t n>
inline Vec<T, n> operator-(const Vec<T, n>& vec);

template<typename T, size_t n>
inline Vec<T, n> operator*(const Vec<T, n>& vec, T val);

template<typename T, size_t n>
inline Vec<T, n> operator*(T val, const Vec<T, n>& vec);

template<typename T, size_t n>
inline void operator*=(Vec<T, n>& vec, T val);

template<typename T, size_t n>
inline Vec<T, n> operator/(const Vec<T, n>& vec, T val);

template<typename T, size_t n>
inline void operator/=(Vec<T, n>& vec, T val);

} // namespace as

#include "as-vec.inl"