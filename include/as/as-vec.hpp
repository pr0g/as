#pragma once

#include <type_traits>
#include <utility>

#include "as-types.hpp"

namespace as
{

template<typename T, index_t n>
struct vec_t
{
    using value_type = T;

    vec_t() noexcept = default;
    vec_t(const vec_t&) noexcept = default;
    vec_t& operator=(const vec_t&) noexcept = default;
    vec_t(vec_t&&) noexcept = default;
    vec_t& operator=(vec_t&&) noexcept = default;
    ~vec_t() = default;

    template<typename...>
    struct typelist
    {
    };

    template<
        typename... Args,
        typename = std::enable_if_t<!std::is_same<
            typelist<vec_t>, typelist<std::decay_t<Args>...>>::value>>
    vec_t(Args... args) noexcept : elem{std::forward<Args>(args)...}
    {
        static_assert(
            sizeof...(args) == n, "Not enough arguments for dimension");
    }

    constexpr T& operator[](index_t i) &;
    constexpr const T& operator[](index_t i) const&;
    constexpr T operator[](index_t i) &&;

    constexpr static index_t size();

private:
    T elem[size()];
};

namespace internal
{

template<typename T>
struct vec2_base_t
{
    using value_type = T;

    vec2_base_t() noexcept = default;
    vec2_base_t(const vec2_base_t&) noexcept = default;
    vec2_base_t& operator=(const vec2_base_t&) noexcept = default;
    vec2_base_t(vec2_base_t&&) noexcept = default;
    vec2_base_t& operator=(vec2_base_t&&) noexcept = default;
    ~vec2_base_t() = default;

    constexpr explicit vec2_base_t(T xy_);
    constexpr vec2_base_t(T x_, T y_);

    T& operator[](index_t i) &;
    const T& operator[](index_t i) const&;
    const T operator[](index_t i) &&;

    constexpr static index_t size();

    T x, y;

private:
    static T vec2_base_t::*elem[size()];
};

template<typename T>
T vec2_base_t<T>::*vec2_base_t<T>::elem[vec2_base_t::size()] = {
    &vec2_base_t<T>::x, &vec2_base_t<T>::y};

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

    constexpr explicit vec_t(T xy_);
    constexpr vec_t(T x_, T y_);
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
    using value_type = T;

    vec3_base_t() noexcept = default;
    vec3_base_t(const vec3_base_t&) noexcept = default;
    vec3_base_t& operator=(const vec3_base_t&) noexcept = default;
    vec3_base_t(vec3_base_t&&) noexcept = default;
    vec3_base_t& operator=(vec3_base_t&&) noexcept = default;
    ~vec3_base_t() = default;

    constexpr explicit vec3_base_t(T xyz_);
    constexpr vec3_base_t(const vec_t<T, 2>& xy_, T z_);
    constexpr vec3_base_t(T x_, T y_, T z_);

    T& operator[](index_t i) &;
    const T& operator[](index_t i) const&;
    const T operator[](index_t i) &&;

    constexpr static index_t size();

    T x, y, z;

private:
    static T vec3_base_t::*elem[size()];
};

template<typename T>
T vec3_base_t<T>::*vec3_base_t<T>::elem[vec3_base_t::size()] = {
    &vec3_base_t<T>::x, &vec3_base_t<T>::y, &vec3_base_t<T>::z};

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

    constexpr explicit vec_t(T xyz_);
    constexpr vec_t(const vec_t<T, 2>& xy_, T z_);
    constexpr vec_t(T x_, T y_, T z_);
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
    using value_type = T;

    vec4_base_t() noexcept = default;
    vec4_base_t(const vec4_base_t&) noexcept = default;
    vec4_base_t& operator=(const vec4_base_t&) noexcept = default;
    vec4_base_t(vec4_base_t&&) noexcept = default;
    vec4_base_t& operator=(vec4_base_t&&) noexcept = default;
    ~vec4_base_t() = default;

    constexpr explicit vec4_base_t(T xyzw_);
    constexpr vec4_base_t(const vec_t<T, 3>& xyz_, T w_);
    constexpr vec4_base_t(const vec_t<T, 2>& xy_, T z_, T w_);
    constexpr vec4_base_t(const vec_t<T, 2>& xy_, const vec_t<T, 2>& zw);
    constexpr vec4_base_t(T x_, T y_, T z_, T w_);

    T& operator[](index_t i) &;
    const T& operator[](index_t i) const&;
    const T operator[](index_t i) &&;

    constexpr static index_t size();

    T x, y, z, w;

private:
    static T vec4_base_t::*elem[size()];
};

template<typename T>
T vec4_base_t<T>::*vec4_base_t<T>::elem[vec4_base_t::size()] = {
    &vec4_base_t<T>::x, &vec4_base_t<T>::y, &vec4_base_t<T>::z,
    &vec4_base_t<T>::w};

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

    constexpr explicit vec_t(T xyzw_);
    constexpr vec_t(const vec_t<T, 3>& xyz_, T w_);
    constexpr vec_t(const vec_t<T, 2>& xy_, T z_, T w_);
    constexpr vec_t(const vec_t<T, 2>& xy_, const vec_t<T, 2>& zw);
    constexpr vec_t(T x_, T y_, T z_, T w_);
};

using vec4_t = vec_t<real_t, 4>;
using vec4f_t = vec_t<float, 4>;
using vec4d_t = vec_t<double, 4>;
using vec4i_t = vec_t<int32_t, 4>;
using vec4l_t = vec_t<int64_t, 4>;

template<typename T, index_t n>
const vec_t<T, n> operator+(const vec_t<T, n>& lhs, const vec_t<T, n>& rhs);

template<>
const vec3_t operator+(const vec3_t& lhs, const vec3_t& rhs);

template<typename T, index_t n>
vec_t<T, n>& operator+=(vec_t<T, n>& lhs, const vec_t<T, n>& rhs);

template<>
vec3_t& operator+=(vec3_t& lhs, const vec3_t& rhs);

template<typename T, index_t n>
const vec_t<T, n> operator-(const vec_t<T, n>& lhs, const vec_t<T, n>& rhs);

template<>
const vec3_t operator-(const vec3_t& lhs, const vec3_t& rhs);

template<typename T, index_t n>
vec_t<T, n>& operator-=(vec_t<T, n>& lhs, const vec_t<T, n>& rhs);

template<>
vec3_t& operator-=(vec3_t& lhs, const vec3_t& rhs);

template<typename T, index_t n>
const vec_t<T, n> operator-(const vec_t<T, n>& rhs);

template<>
const vec3_t operator-(const vec3_t& rhs);

template<typename T, index_t n>
const vec_t<T, n> operator*(const vec_t<T, n>& lhs, T val);

template<>
const vec3_t operator*(const vec3_t& lhs, real_t val);

template<typename T, index_t n>
const vec_t<T, n> operator*(T val, const vec_t<T, n>& rhs);

template<>
const vec3_t operator*(real_t val, const vec3_t& rhs);

template<typename T, index_t n>
vec_t<T, n>& operator*=(vec_t<T, n>& lhs, T val);

template<>
vec3_t& operator*=(vec3_t& lhs, real_t val);

template<typename T, index_t n>
const vec_t<T, n> operator*(const vec_t<T, n>& lhs, const vec_t<T, n>& rhs);

template<>
const vec3_t operator*(const vec3_t& lhs, const vec3_t& rhs);

template<typename T, index_t n>
vec_t<T, n>& operator*=(vec_t<T, n>& lhs, const vec_t<T, n>& rhs);

template<>
vec3_t& operator*=(vec3_t& lhs, const vec3_t& rhs);

template<typename T, index_t n>
const vec_t<T, n> operator/(const vec_t<T, n>& lhs, T val);

template<>
const vec3_t operator/(const vec3_t& lhs, real_t val);

template<typename T, index_t n>
vec_t<T, n>& operator/=(vec_t<T, n>& lhs, T val);

template<>
vec3_t& operator/=(vec3_t& lhs, real_t val);

template<typename T, index_t n>
const vec_t<T, n> operator/(const vec_t<T, n>& lhs, const vec_t<T, n>& rhs);

template<>
const vec3_t operator/(const vec3_t& lhs, const vec3_t& rhs);

template<typename T, index_t n>
vec_t<T, n>& operator/=(vec_t<T, n>& lhs, const vec_t<T, n>& rhs);

template<>
vec3_t& operator/=(vec3_t& lhs, const vec3_t& rhs);

} // namespace as

#include "as-vec.inl"
