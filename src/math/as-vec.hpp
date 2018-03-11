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

template<typename empty>
struct vec2_base_t
{
    real_t x, y;

    static const size_t size = 2;

    real_t& operator[](size_t i) { return this->*elem[i]; }
    const real_t& operator[](size_t i) const { return this->*elem[i]; }

    real_t* elems() { return &(this->*elem[0]); }
    const real_t* elems() const { return &(this->*elem[0]); }

    vec2_base_t() = default;
    vec2_base_t(const vec2_base_t&) = default;
    vec2_base_t& operator=(const vec2_base_t&) = default;
    vec2_base_t(vec2_base_t&&) noexcept = default;
    vec2_base_t& operator=(vec2_base_t&&) noexcept = default;
    ~vec2_base_t() = default;

    constexpr explicit vec2_base_t(real_t xy) : x(xy), y(xy) {}
    constexpr vec2_base_t(real_t x, real_t y) : x(x), y(y) {}

private:
    static real_t vec2_base_t::*elem[2];
};

template<class empty>
real_t vec2_base_t<empty>::*vec2_base_t<empty>::elem[2] =
{ 
    &vec2_base_t<empty>::x,
    &vec2_base_t<empty>::y
};

template<>
struct vec_t<real_t, 2> : vec2_base_t<void>
{
    vec_t() = default;
    vec_t(const vec_t&) = default;
    vec_t& operator=(const vec_t&) = default;
    vec_t(vec_t&&) noexcept = default;
    vec_t& operator=(vec_t&&) noexcept = default;
    ~vec_t() = default;

    constexpr explicit vec_t(real_t xy) : vec2_base_t(xy) {}
    constexpr vec_t(real_t x, real_t y) : vec2_base_t(x, y) {}
};

using vec2_t = vec_t<real_t, 2>;

template<typename empty>
struct vec3_base_t
{
    real_t x, y, z;
    static const size_t size = 3;

    real_t& operator[](size_t i) { return this->*elem[i]; }
    const real_t& operator[](size_t i) const { return this->*elem[i]; }

    real_t* elems() { return &(this->*elem[0]); }
    const real_t* elems() const { return &(this->*elem[0]); }

    vec3_base_t() = default;
    vec3_base_t(const vec3_base_t&) = default;
    vec3_base_t& operator=(const vec3_base_t&) = default;
    vec3_base_t(vec3_base_t&&) noexcept = default;
    vec3_base_t& operator=(vec3_base_t&&) noexcept = default;
    ~vec3_base_t() = default;

    constexpr explicit vec3_base_t(real_t xyz) : x(xyz), y(xyz), z(xyz) {}
    constexpr vec3_base_t(const vec2_t& xy, real_t z) : x(xy.x), y(xy.y), z(z) {}
    constexpr vec3_base_t(real_t x, real_t y, real_t z) : x(x), y(y), z(z) {}

    constexpr vec2_t xy() const { return { x, y }; }

private:
    static real_t vec3_base_t::*elem[3];
};

template<class empty>
real_t vec3_base_t<empty>::*vec3_base_t<empty>::elem[3] =
{
    &vec3_base_t<empty>::x,
    &vec3_base_t<empty>::y,
    &vec3_base_t<empty>::z
};

template<>
struct vec_t<real_t, 3> : vec3_base_t<void>
{
    vec_t() = default;
    vec_t(const vec_t&) = default;
    vec_t& operator=(const vec_t&) = default;
    vec_t(vec_t&&) noexcept = default;
    vec_t& operator=(vec_t&&) noexcept = default;
    ~vec_t() = default;

    constexpr explicit vec_t(real_t xyz) : vec3_base_t(xyz) {}
    constexpr vec_t(const vec2_t& xy, real_t z) : vec3_base_t(xy, z) {}
    constexpr vec_t(real_t x, real_t y, real_t z) : vec3_base_t(x, y, z) {}
};

using vec3_t = vec_t<real_t, 3>;

template<typename empty>
struct vec4_base_t
{
    real_t x, y, z, w;
    static const size_t size = 4;

    real_t& operator[](size_t i) { return this->*elem[i]; }
    const real_t& operator[](size_t i) const { return this->*elem[i]; }

    real_t* elems() { return &(this->*elem[0]); }
    const real_t* elems() const { return &(this->*elem[0]); }

    vec4_base_t() = default;
    vec4_base_t(const vec4_base_t&) = default;
    vec4_base_t& operator=(const vec4_base_t&) = default;
    vec4_base_t(vec4_base_t&&) noexcept = default;
    vec4_base_t& operator=(vec4_base_t&&) noexcept = default;
    ~vec4_base_t() = default;

    constexpr explicit vec4_base_t(real_t xyzw) : x(xyzw), y(xyzw), z(xyzw), w(xyzw) {}
    constexpr vec4_base_t(const vec3_t& xyz, real_t w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}
    constexpr vec4_base_t(const vec2_t& xy, real_t z, real_t w) : x(xy.x), y(xy.y), z(z), w(w) {}
    constexpr vec4_base_t(const vec2_t& xy, const vec2_t& zw) : x(xy.x), y(xy.y), z(zw.x), w(zw.y) {}
    constexpr vec4_base_t(real_t x, real_t y, real_t z, real_t w) : x(x), y(y), z(z), w(w) {}

    constexpr vec2_t xy() const { return { x, y }; }
    constexpr vec2_t zw() const { return { z, w }; }
    constexpr vec3_t xyz() const { return { x, y, z }; }

private:
    static real_t vec4_base_t::*elem[4];
};

template<class empty>
real_t vec4_base_t<empty>::*vec4_base_t<empty>::elem[4] =
{ 
    &vec4_base_t<empty>::x,
    &vec4_base_t<empty>::y,
    &vec4_base_t<empty>::z,
    &vec4_base_t<empty>::w
};

template<>
struct vec_t<real_t, 4> : vec4_base_t<void>
{
    vec_t() = default;
    vec_t(const vec_t&) = default;
    vec_t& operator=(const vec_t&) = default;
    vec_t(vec_t&&) noexcept = default;
    vec_t& operator=(vec_t&&) noexcept = default;
    ~vec_t() = default;

    constexpr explicit vec_t(real_t xyzw) : vec4_base_t(xyzw) {}
    constexpr vec_t(const vec3_t& xyz, real_t w) : vec4_base_t(xyz, w) {}
    constexpr vec_t(const vec2_t& xy, real_t z, real_t w) : vec4_base_t(xy, z, w) {}
    constexpr vec_t(const vec2_t& xy, const vec2_t& zw) : vec4_base_t(xy, zw) {}
    constexpr vec_t(real_t x, real_t y, real_t z, real_t w) : vec4_base_t(x, y, z, w) {}
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