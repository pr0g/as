#pragma once

#include <algorithm>
#include <type_traits>

#include "core/as-types.hpp"
#include "core/as-assert.hpp"

#include "as-math.hpp"

namespace as
{

template<typename T, size_t n>
struct vec_t
{
    T elem[n];
    static const size_t size = n;

    constexpr T& operator[](size_t i) { return elem[i]; }
    constexpr const T& operator[](size_t i) const { return elem[i]; }

    constexpr T* elems() { return elem; }
    constexpr const T* elems() const { return elem; }

    vec_t() = default;
    vec_t(const vec_t&) = default;
    vec_t& operator=(const vec_t&) = default;
    vec_t(vec_t&&) noexcept = default;
    vec_t& operator=(vec_t&&) noexcept = default;
    ~vec_t() = default;

    template<typename...> struct typelist;
    template<typename... Args, typename = std::enable_if_t<!std::is_same<typelist<vec_t>, typelist<std::decay_t<Args>...>>::value>>
    vec_t(Args... args) noexcept : elem{ std::forward<Args>(args)... } {}
};

template<>
struct vec_t<real_t, 2>
{
    real_t x, y;
    static const size_t size = 2;

    real_t& operator[](size_t i) { return this->*elem[i]; }
    const real_t& operator[](size_t i) const { return this->*elem[i]; }

    real_t* elems() { return &(this->*elem[0]); }
    const real_t* elems() const { return &(this->*elem[0]); }

    vec_t() = default;
    vec_t(const vec_t&) = default;
    vec_t& operator=(const vec_t&) = default;
    vec_t(vec_t&&) noexcept = default;
    vec_t& operator=(vec_t&&) noexcept = default;
    ~vec_t() = default;

    constexpr explicit vec_t(real_t xy) : x(xy), y(xy) {}
    constexpr vec_t(real_t x, real_t y) : x(x), y(y) {}

private:
    static real_t vec_t::*elem[2];
};

using vec2_t = vec_t<real_t, 2>;

template<>
struct vec_t<real_t, 3>
{
    real_t x, y, z;
    static const size_t size = 3;

    real_t& operator[](size_t i) { return this->*elem[i]; }
    const real_t& operator[](size_t i) const { return this->*elem[i]; }

    real_t* elems() { return &(this->*elem[0]); }
    const real_t* elems() const { return &(this->*elem[0]); }

    vec_t() = default;
    vec_t(const vec_t&) = default;
    vec_t& operator=(const vec_t&) = default;
    vec_t(vec_t&&) noexcept = default;
    vec_t& operator=(vec_t&&) noexcept = default;
    ~vec_t() = default;

    constexpr explicit vec_t(real_t xyz) : x(xyz), y(xyz), z(xyz) {}
    constexpr vec_t(const vec2_t& xy, real_t z) : x(xy.x), y(xy.y), z(z) {}
    constexpr vec_t(real_t x, real_t y, real_t z) : x(x), y(y), z(z) {}

    constexpr vec2_t xy() const { return { x, y }; }

private:
    static real_t vec_t::*elem[3];
};

using vec3_t = vec_t<real_t, 3>;

template<>
struct vec_t<real_t, 4>
{
    real_t x, y, z, w;
    static const size_t size = 4;

    real_t& operator[](size_t i) { return this->*elem[i]; }
    const real_t& operator[](size_t i) const { return this->*elem[i]; }

    real_t* elems() { return &(this->*elem[0]); }
    const real_t* elems() const { return &(this->*elem[0]); }

    vec_t() = default;
    vec_t(const vec_t&) = default;
    vec_t& operator=(const vec_t&) = default;
    vec_t(vec_t&&) noexcept = default;
    vec_t& operator=(vec_t&&) noexcept = default;
    ~vec_t() = default;

    constexpr explicit vec_t(real_t xyzw) : x(xyzw), y(xyzw), z(xyzw), w(xyzw) {}
    constexpr vec_t(const vec3_t& xyz, real_t w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}
    constexpr vec_t(const vec2_t& xy, real_t z, real_t w) : x(xy.x), y(xy.y), z(z), w(w) {}
    constexpr vec_t(const vec2_t& xy, const vec2_t& zw) : x(xy.x), y(xy.y), z(zw.x), w(zw.y) {}
    constexpr vec_t(real_t x, real_t y, real_t z, real_t w) : x(x), y(y), z(z), w(w) {}

    constexpr vec2_t xy() const { return { x, y }; }
    constexpr vec2_t zw() const { return { z, w }; }
    constexpr vec3_t xyz() const { return { x, y, z }; }

private:
    static real_t vec_t::*elem[4];
};

using vec4_t = vec_t<real_t, 4>;

template<typename T, size_t n>
inline vec_t<T, n> operator+(const vec_t<T, n>& lhs, const vec_t<T, n>& rhs);

template<typename T, size_t n>
inline vec_t<T, n>& operator+=(vec_t<T, n>& lhs, const vec_t<T, n>& rhs);

template<typename T, size_t n>
inline vec_t<T, n> operator-(const vec_t<T, n>& lhs, const vec_t<T, n>& rhs);

template<typename T, size_t n>
inline vec_t<T, n>& operator-=(vec_t<T, n>& lhs, const vec_t<T, n>& rhs);

template<typename T, size_t n>
inline vec_t<T, n> operator-(const vec_t<T, n>& vec);

template<typename T, size_t n>
inline vec_t<T, n> operator*(const vec_t<T, n>& vec, T val);

template<typename T, size_t n>
inline vec_t<T, n> operator*(T val, const vec_t<T, n>& vec);

template<typename T, size_t n>
inline void operator*=(vec_t<T, n>& vec, T val);

template<typename T, size_t n>
inline vec_t<T, n> operator/(const vec_t<T, n>& vec, T val);

template<typename T, size_t n>
inline void operator/=(vec_t<T, n>& vec, T val);

} // namespace as

#include "as-vec.inl"