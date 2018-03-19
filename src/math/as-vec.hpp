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

template<typename T>
struct vec2_base_t
{
    T x, y;

    static const size_t size = 2;

    T& operator[](size_t i) { return this->*elem[i]; }
    const T& operator[](size_t i) const { return this->*elem[i]; }

    T* elems() { return &(this->*elem[0]); }
    const T* elems() const { return &(this->*elem[0]); }

    vec2_base_t() = default;
    vec2_base_t(const vec2_base_t&) = default;
    vec2_base_t& operator=(const vec2_base_t&) = default;
    vec2_base_t(vec2_base_t&&) noexcept = default;
    vec2_base_t& operator=(vec2_base_t&&) noexcept = default;
    ~vec2_base_t() = default;

    constexpr vec2_base_t(T xy) : x(xy), y(xy) {}
    constexpr vec2_base_t(T x, T y) : x(x), y(y) {}

private:
    static T vec2_base_t::*elem[2];
};

template<typename T>
T vec2_base_t<T>::*vec2_base_t<T>::elem[2] =
{ 
    &vec2_base_t<T>::x,
    &vec2_base_t<T>::y
};

template<typename T>
struct vec_t<T, 2> : vec2_base_t<T>
{
    vec_t() = default;
    vec_t(const vec_t&) = default;
    vec_t& operator=(const vec_t&) = default;
    vec_t(vec_t&&) noexcept = default;
    vec_t& operator=(vec_t&&) noexcept = default;
    ~vec_t() = default;

    constexpr vec_t(T xy) : vec2_base_t(xy) {}
    constexpr vec_t(T x, T y) : vec2_base_t(x, y) {}
};

using vec2_t = vec_t<real_t, 2>;
using vec2i_t = vec_t<integer_t, 2>;

template<typename T>
struct vec3_base_t
{
    T x, y, z;
    static const size_t size = 3;

    T& operator[](size_t i) { return this->*elem[i]; }
    const T& operator[](size_t i) const { return this->*elem[i]; }

    T* elems() { return &(this->*elem[0]); }
    const T* elems() const { return &(this->*elem[0]); }

    vec3_base_t() = default;
    vec3_base_t(const vec3_base_t&) = default;
    vec3_base_t& operator=(const vec3_base_t&) = default;
    vec3_base_t(vec3_base_t&&) noexcept = default;
    vec3_base_t& operator=(vec3_base_t&&) noexcept = default;
    ~vec3_base_t() = default;

    constexpr vec3_base_t(T xyz) : x(xyz), y(xyz), z(xyz) {}
    constexpr vec3_base_t(const vec2_t& xy, T z) : x(xy.x), y(xy.y), z(z) {}
    constexpr vec3_base_t(T x, T y, T z) : x(x), y(y), z(z) {}

    constexpr vec2_t xy() const { return { x, y }; }

private:
    static T vec3_base_t::*elem[3];
};

template<typename T>
T vec3_base_t<T>::*vec3_base_t<T>::elem[3] =
{
    &vec3_base_t<T>::x,
    &vec3_base_t<T>::y,
    &vec3_base_t<T>::z
};

template<typename T>
struct vec_t<T, 3> : vec3_base_t<T>
{
    vec_t() = default;
    vec_t(const vec_t&) = default;
    vec_t& operator=(const vec_t&) = default;
    vec_t(vec_t&&) noexcept = default;
    vec_t& operator=(vec_t&&) noexcept = default;
    ~vec_t() = default;

    constexpr vec_t(T xyz) : vec3_base_t(xyz) {}
    constexpr vec_t(const vec_t<T, 2>& xy, T z) : vec3_base_t(xy, z) {}
    constexpr vec_t(T x, T y, T z) : vec3_base_t(x, y, z) {}
};

using vec3_t = vec_t<real_t, 3>;
using vec3i_t = vec_t<integer_t, 3>;

template<typename T>
struct vec4_base_t
{
    T x, y, z, w;
    static const size_t size = 4;

    T& operator[](size_t i) { return this->*elem[i]; }
    const T& operator[](size_t i) const { return this->*elem[i]; }

    T* elems() { return &(this->*elem[0]); }
    const T* elems() const { return &(this->*elem[0]); }

    vec4_base_t() = default;
    vec4_base_t(const vec4_base_t&) = default;
    vec4_base_t& operator=(const vec4_base_t&) = default;
    vec4_base_t(vec4_base_t&&) noexcept = default;
    vec4_base_t& operator=(vec4_base_t&&) noexcept = default;
    ~vec4_base_t() = default;

    constexpr vec4_base_t(T xyzw) : x(xyzw), y(xyzw), z(xyzw), w(xyzw) {}
    constexpr vec4_base_t(const vec_t<T, 3>& xyz, T w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}
    constexpr vec4_base_t(const vec_t<T, 2>& xy, T z, T w) : x(xy.x), y(xy.y), z(z), w(w) {}
    constexpr vec4_base_t(const vec_t<T, 2>& xy, const vec_t<T, 2>& zw) : x(xy.x), y(xy.y), z(zw.x), w(zw.y) {}
    constexpr vec4_base_t(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

    constexpr vec2_t xy() const { return { x, y }; }
    constexpr vec2_t zw() const { return { z, w }; }
    constexpr vec3_t xyz() const { return { x, y, z }; }

private:
    static T vec4_base_t::*elem[4];
};

template<typename T>
T vec4_base_t<T>::*vec4_base_t<T>::elem[4] =
{ 
    &vec4_base_t<T>::x,
    &vec4_base_t<T>::y,
    &vec4_base_t<T>::z,
    &vec4_base_t<T>::w
};

template<typename T>
struct vec_t<T, 4> : vec4_base_t<T>
{
    vec_t() = default;
    vec_t(const vec_t&) = default;
    vec_t& operator=(const vec_t&) = default;
    vec_t(vec_t&&) noexcept = default;
    vec_t& operator=(vec_t&&) noexcept = default;
    ~vec_t() = default;

    constexpr vec_t(T xyzw) : vec4_base_t(xyzw) {}
    constexpr vec_t(const vec_t<T, 3>& xyz, T w) : vec4_base_t(xyz, w) {}
    constexpr vec_t(const vec_t<T, 2>& xy, T z, T w) : vec4_base_t(xy, z, w) {}
    constexpr vec_t(const vec_t<T, 2>& xy, const vec_t<T, 2>& zw) : vec4_base_t(xy, zw) {}
    constexpr vec_t(T x, T y, T z, T w) : vec4_base_t(x, y, z, w) {}
};

using vec4_t = vec_t<real_t, 4>;
using vec4i_t = vec_t<integer_t, 4>;

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