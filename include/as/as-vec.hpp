#pragma once

#include <utility>
#include <type_traits>

#include "as-types.hpp"

namespace as
{

template<typename T, index_t n>
struct vec_t
{
    T elem[n];

    constexpr static index_t size() { return n; }

    using value_type = T;

    constexpr T& operator[](index_t i) & { return elem[i]; }
    constexpr const T& operator[](index_t i) const& { return elem[i]; }
    constexpr T operator[](index_t i) && { return elem[i]; }

    vec_t() noexcept = default;
    vec_t(const vec_t&) noexcept = default;
    vec_t& operator=(const vec_t&) noexcept = default;
    vec_t(vec_t&&) noexcept = default;
    vec_t& operator=(vec_t&&) noexcept = default;
    ~vec_t() = default;

    template<typename...> struct typelist {};
    template<
        typename... Args,
        typename = std::enable_if_t<
            !std::is_same<typelist<vec_t>,
                typelist<std::decay_t<Args>...>>::value>>
    explicit vec_t(Args... args) noexcept : elem { std::forward<Args>(args)... }
    {
        static_assert(sizeof ...(args) == n, "Not enough arguments for dimension");
    }
};

namespace internal
{

template<typename T>
struct vec2_base_t
{
    T x, y;

    constexpr static index_t size() { return 2; }

    using value_type = T;

    AS_API T& operator[](index_t i) & { return this->*elem[i]; }
    AS_API const T& operator[](index_t i) const& { return this->*elem[i]; }
    AS_API const T operator[](index_t i) && { return this->*elem[i]; }

    vec2_base_t() noexcept = default;
    vec2_base_t(const vec2_base_t&) noexcept  = default;
    vec2_base_t& operator=(const vec2_base_t&) noexcept  = default;
    vec2_base_t(vec2_base_t&&) noexcept = default;
    vec2_base_t& operator=(vec2_base_t&&) noexcept = default;
    ~vec2_base_t() = default;

    AS_API constexpr explicit vec2_base_t(T xy_)
        : x(xy_), y(xy_) {}
    AS_API constexpr vec2_base_t(T x_, T y_)
        : x(x_), y(y_) {}

private:
    static T vec2_base_t::*elem[2];
};

template<typename T>
T vec2_base_t<T>::*vec2_base_t<T>::elem[2] =
{
    &vec2_base_t<T>::x,
    &vec2_base_t<T>::y
};

} // namespace internal

template<typename T>
struct vec_t<T, 2> : internal::vec2_base_t<T>
{
    vec_t() noexcept = default;
    vec_t(const vec_t&) noexcept = default;
    vec_t& operator=(const vec_t&) noexcept = default;
    vec_t(vec_t&&) noexcept = default;
    vec_t& operator=(vec_t&&) noexcept = default;
    ~vec_t() = default;

    AS_API constexpr explicit vec_t(T xy_)
        : internal::vec2_base_t<T>(xy_) {}
    AS_API constexpr vec_t(T x_, T y_)
        : internal::vec2_base_t<T>(x_, y_) {}
};

using vec2_t = vec_t<real_t, 2>;
using vec2f_t = vec_t<float, 2>;
using vec2d_t = vec_t<double, 2>;
using vec2i_t = vec_t<int32_t, 2>;
using vec2l_t = vec_t<int64_t, 2>;

namespace internal
{

template<typename T>
struct vec3_base_t
{
    T x, y, z;

    constexpr static index_t size() { return 3; }

    using value_type = T;

    AS_API T& operator[](index_t i) & { return this->*elem[i]; }
    AS_API const T& operator[](index_t i) const& { return this->*elem[i]; }
    AS_API const T operator[](index_t i) && { return this->*elem[i]; }

    vec3_base_t() noexcept = default;
    vec3_base_t(const vec3_base_t&) noexcept = default;
    vec3_base_t& operator=(const vec3_base_t&) noexcept = default;
    vec3_base_t(vec3_base_t&&) noexcept = default;
    vec3_base_t& operator=(vec3_base_t&&) noexcept = default;
    ~vec3_base_t() = default;

    AS_API constexpr explicit vec3_base_t(T xyz_)
        : x(xyz_), y(xyz_), z(xyz_) {}
    AS_API constexpr vec3_base_t(const vec_t<T, 2>& xy_, T z_)
        : x(xy_.x), y(xy_.y), z(z_) {}
    AS_API constexpr vec3_base_t(T x_, T y_, T z_)
        : x(x_), y(y_), z(z_) {}

    AS_API constexpr vec_t<T, 2> xy() const { return { x, y }; }

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

} // namespace internal

template<typename T>
struct vec_t<T, 3> : internal::vec3_base_t<T>
{
    vec_t() noexcept = default;
    vec_t(const vec_t&) noexcept = default;
    vec_t& operator=(const vec_t&) noexcept = default;
    vec_t(vec_t&&) noexcept = default;
    vec_t& operator=(vec_t&&) noexcept = default;
    ~vec_t() = default;

    AS_API constexpr explicit vec_t(T xyz_)
        : internal::vec3_base_t<T>(xyz_) {}
    AS_API constexpr vec_t(const vec_t<T, 2>& xy_, T z_)
        : internal::vec3_base_t<T>(xy_, z_) {}
    AS_API constexpr vec_t(T x_, T y_, T z_)
        : internal::vec3_base_t<T>(x_, y_, z_) {}
};

using vec3_t = vec_t<real_t, 3>;
using vec3f_t = vec_t<float, 3>;
using vec3d_t = vec_t<double, 3>;
using vec3i_t = vec_t<int32_t, 3>;
using vec3l_t = vec_t<int64_t, 3>;

namespace internal
{

template<typename T>
struct vec4_base_t
{
    T x, y, z, w;

    constexpr static index_t size() { return 4; }

    using value_type = T;

    AS_API T& operator[](index_t i) & { return this->*elem[i]; }
    AS_API const T& operator[](index_t i) const& { return this->*elem[i]; }
    AS_API const T operator[](index_t i) && { return this->*elem[i]; }

    vec4_base_t() noexcept = default;
    vec4_base_t(const vec4_base_t&) noexcept  = default;
    vec4_base_t& operator=(const vec4_base_t&) noexcept  = default;
    vec4_base_t(vec4_base_t&&) noexcept = default;
    vec4_base_t& operator=(vec4_base_t&&) noexcept = default;
    ~vec4_base_t() = default;

    AS_API constexpr explicit vec4_base_t(T xyzw_)
        : x(xyzw_), y(xyzw_), z(xyzw_), w(xyzw_) {}
    AS_API constexpr vec4_base_t(const vec_t<T, 3>& xyz_, T w_)
        : x(xyz_.x), y(xyz_.y), z(xyz_.z), w(w_) {}
    AS_API constexpr vec4_base_t(const vec_t<T, 2>& xy_, T z_, T w_)
        : x(xy_.x), y(xy_.y), z(z_), w(w_) {}
    AS_API constexpr vec4_base_t(const vec_t<T, 2>& xy_, const vec_t<T, 2>& zw)
        : x(xy_.x), y(xy_.y), z(zw.x), w(zw.y) {}
    AS_API constexpr vec4_base_t(T x_, T y_, T z_, T w_)
        : x(x_), y(y_), z(z_), w(w_) {}

    AS_API constexpr vec_t<T, 2> xy() const { return { x, y }; }
    AS_API constexpr vec_t<T, 2> zw() const { return { z, w }; }
    AS_API constexpr vec_t<T, 3> xyz() const { return { x, y, z }; }

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

} // namespace internal

template<typename T>
struct vec_t<T, 4> : internal::vec4_base_t<T>
{
    vec_t() noexcept = default;
    vec_t(const vec_t&) noexcept = default;
    vec_t& operator=(const vec_t&) noexcept = default;
    vec_t(vec_t&&) noexcept = default;
    vec_t& operator=(vec_t&&) noexcept = default;
    ~vec_t() = default;

    AS_API constexpr explicit vec_t(T xyzw_)
        : internal::vec4_base_t<T>(xyzw_) {}
    AS_API constexpr vec_t(const vec_t<T, 3>& xyz_, T w_)
        : internal::vec4_base_t<T>(xyz_, w_) {}
    AS_API constexpr vec_t(const vec_t<T, 2>& xy_, T z_, T w_)
        : internal::vec4_base_t<T>(xy_, z_, w_) {}
    AS_API constexpr vec_t(const vec_t<T, 2>& xy_, const vec_t<T, 2>& zw)
        : internal::vec4_base_t<T>(xy_, zw) {}
    AS_API constexpr vec_t(T x_, T y_, T z_, T w_)
        : internal::vec4_base_t<T>(x_, y_, z_, w_) {}
};

using vec4_t = vec_t<real_t, 4>;
using vec4f_t = vec_t<float, 4>;
using vec4d_t = vec_t<double, 4>;
using vec4i_t = vec_t<int32_t, 4>;
using vec4l_t = vec_t<int64_t, 4>;

template<typename T, index_t n>
AS_API const vec_t<T, n> operator+(
    const vec_t<T, n>& lhs, const vec_t<T, n>& rhs);

template<>
AS_API const vec3_t operator+(const vec3_t& lhs, const vec3_t& rhs);

template<typename T, index_t n>
AS_API vec_t<T, n>& operator+=(vec_t<T, n>& lhs, const vec_t<T, n>& rhs);

template<>
AS_API vec3_t& operator+=(vec3_t& lhs, const vec3_t& rhs);

template<typename T, index_t n>
AS_API const vec_t<T, n> operator-(
    const vec_t<T, n>& lhs, const vec_t<T, n>& rhs);

template<>
AS_API const vec3_t operator-(const vec3_t& lhs, const vec3_t& rhs);

template<typename T, index_t n>
AS_API vec_t<T, n>& operator-=(vec_t<T, n>& lhs, const vec_t<T, n>& rhs);

template<>
AS_API vec3_t& operator-=(vec3_t& lhs, const vec3_t& rhs);

template<typename T, index_t n>
AS_API const vec_t<T, n> operator-(const vec_t<T, n>& rhs);

template<>
AS_API const vec3_t operator-(const vec3_t& rhs);

template<typename T, index_t n>
AS_API const vec_t<T, n> operator*(const vec_t<T, n>& lhs, T val);

template<>
AS_API const vec3_t operator*(const vec3_t& lhs, real_t val);

template<typename T, index_t n>
AS_API const vec_t<T, n> operator*(T val, const vec_t<T, n>& rhs);

template<>
AS_API const vec3_t operator*(real_t val, const vec3_t& rhs);

template<typename T, index_t n>
AS_API vec_t<T, n>& operator*=(vec_t<T, n>& lhs, T val);

template<>
AS_API vec3_t& operator*=(vec3_t& lhs, real_t val);

template<typename T, index_t n>
AS_API const vec_t<T, n> operator*(
    const vec_t<T, n>& lhs, const vec_t<T, n>& rhs);

template<>
AS_API const vec3_t operator*(const vec3_t& lhs, const vec3_t& rhs);

template<typename T, index_t n>
AS_API vec_t<T, n>& operator*=(vec_t<T, n>& lhs, const vec_t<T, n>& rhs);

template<>
AS_API vec3_t& operator*=(vec3_t& lhs, const vec3_t& rhs);

template<typename T, index_t n>
AS_API const vec_t<T, n> operator/(const vec_t<T, n>& lhs, T val);

template<>
AS_API const vec3_t operator/(const vec3_t& lhs, real_t val);

template<typename T, index_t n>
AS_API vec_t<T, n>& operator/=(vec_t<T, n>& lhs, T val);

template<>
AS_API vec3_t& operator/=(vec3_t& lhs, real_t val);

template<typename T, index_t n>
AS_API const vec_t<T, n> operator/(
    const vec_t<T, n>& lhs, const vec_t<T, n>& rhs);

template<>
AS_API const vec3_t operator/(const vec3_t& lhs, const vec3_t& rhs);

template<typename T, index_t n>
AS_API vec_t<T, n>& operator/=(vec_t<T, n>& lhs, const vec_t<T, n>& rhs);

template<>
AS_API vec3_t& operator/=(vec3_t& lhs, const vec3_t& rhs);

} // namespace as

#include "as-vec.inl"
