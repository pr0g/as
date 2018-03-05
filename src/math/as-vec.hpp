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

    T* elems() { return elem; }
    const T* elems() const { return elem; }

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
struct Vec<real_t, 2>
{
    real_t x, y;

    static const size_t size = 2;

    constexpr real_t& operator[](size_t i) { return this->*elem[i]; }
    constexpr const real_t& operator[](size_t i) const { return this->*elem[i]; }

    Vec() = default;
    Vec(const Vec&) = default;
    Vec& operator=(const Vec&) = default;
    Vec(Vec&&) noexcept = default;
    Vec& operator=(Vec&&) noexcept = default;
    ~Vec() = default;

    constexpr explicit Vec(real_t xy) : x(xy), y(xy) {}
    constexpr Vec(real_t x, real_t y) : x(x), y(y) {}

    real_t* elems() { return &(this->*elem[0]); }
    const real_t* elems() const { return &(this->*elem[0]); }

private:
    static real_t Vec::*elem[2];
};

using vec2_t = Vec<real_t, 2>;

template<>
struct Vec<real_t, 3>
{
    real_t x, y, z;

    static const size_t size = 3;

    constexpr real_t& operator[](size_t i) { return this->*elem[i]; }
    constexpr const real_t& operator[](size_t i) const { return this->*elem[i]; }

    Vec() = default;
    Vec(const Vec&) = default;
    Vec& operator=(const Vec&) = default;
    Vec(Vec&&) noexcept = default;
    Vec& operator=(Vec&&) noexcept = default;
    ~Vec() = default;

    constexpr explicit Vec(real_t xyz) : x(xyz), y(xyz), z(xyz) {}
    constexpr Vec(const vec2_t& xy, real_t z) : x(xy.x), y(xy.y), z(z) {}
    constexpr Vec(real_t x, real_t y, real_t z) : x(x), y(y), z(z) {}

    real_t* elems() { return &(this->*elem[0]); }
    const real_t* elems() const { return &(this->*elem[0]); }

    constexpr vec2_t xy() const { return { x, y }; }

private:
    static real_t Vec::*elem[3];
};

using vec3_t = Vec<real_t, 3>;

template<>
struct Vec<real_t, 4>
{
    real_t x, y, z, w;

    static const size_t size = 4;

    constexpr real_t& operator[](size_t i) { return this->*elem[i]; }
    constexpr const real_t& operator[](size_t i) const { return this->*elem[i]; }

    Vec() = default;
    Vec(const Vec&) = default;
    Vec& operator=(const Vec&) = default;
    Vec(Vec&&) noexcept = default;
    Vec& operator=(Vec&&) noexcept = default;
    ~Vec() = default;

    constexpr explicit Vec(real_t xyzw) : x(xyzw), y(xyzw), z(xyzw), w(xyzw) {}
    constexpr Vec(const vec3_t& xyz, real_t w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}
    constexpr Vec(const vec2_t& xy, real_t z, real_t w) : x(xy.x), y(xy.y), z(z), w(w) {}
    constexpr Vec(const vec2_t& xy, const vec2_t& zw) : x(xy.x), y(xy.y), z(zw.x), w(zw.y) {}
    constexpr Vec(real_t x, real_t y, real_t z, real_t w) : x(x), y(y), z(z), w(w) {}

    real_t* elems() { return &(this->*elem[0]); }
    const real_t* elems() const { return &(this->*elem[0]); }

    constexpr vec2_t xy() const { return { x, y }; }
    constexpr vec2_t zw() const { return { z, w }; }
    constexpr vec3_t xyz() const { return { x, y, z }; }

private:
    static real_t Vec::*elem[4];
};

using vec4_t = Vec<real_t, 4>;

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