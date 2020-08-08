#pragma once

#include <limits>
#include <type_traits>
#include <utility>

#include "as-types.hpp"

namespace as
{

//! Geometric vector class template parameterized by type and dimension.
template<typename T, index_t n>
struct vec_t
{
    using value_type = T;

    vec_t() noexcept = default;

    template<typename...>
    struct typelist
    {
    };

    //! A variadic template constructor that accepts the same number of elements
    //! as the dimension of the vector.
    //! \note Passing the wrong number of elements will result in a compile
    //! error.
    template<
        typename... Args,
        typename = std::enable_if_t<!std::is_same<
            typelist<vec_t>, typelist<std::decay_t<Args>...>>::value>>
    constexpr vec_t(Args... args) noexcept : elem{std::forward<Args>(args)...}
    {
        static_assert(
            sizeof...(args) == size(),
            "Incorrent number of arguments for dimension");
    }

    //! Returns a mutable reference at the given index.
    //! \note Can only be called on a mutable lvalue object.
    constexpr T& operator[](index_t i) &;
    //! Returns a const reference at the given index.
    //! \note Can only be called on a const lvalue object.
    constexpr const T& operator[](index_t i) const&;
    //! Returns a value at the given index.
    //! \note Can only be called on an rvalue object.
    constexpr T operator[](index_t i) &&;

    //! The number of elements in the vector.
    //! \note Synonymous with the dimension.
    constexpr static index_t size();

private:
    T elem[size()];
};

//! Partial template specialization of \ref vec_t for a two dimensional vector.
template<typename T>
struct vec_t<T, 2>
{
    using value_type = T;

    vec_t() noexcept = default;
    constexpr explicit vec_t(T xy_);
    constexpr vec_t(T x_, T y_);

    T& operator[](index_t i) &;
    const T& operator[](index_t i) const&;
    const T operator[](index_t i) &&;

    constexpr static index_t size();

    //! Returns `(x, 0)`.
    //! \param x Optional parameter for the length of the axis, defaults to 1.
    constexpr static vec_t<T, 2> axis_x(T x = T(1.0));
    //! Returns `(0, y)`.
    //! \param y Optional parameter for the length of the axis, defaults to 1.
    constexpr static vec_t<T, 2> axis_y(T y = T(1.0));
    //! Returns `(0, 0)`.
    constexpr static vec_t<T, 2> zero();
    //! Returns `(1, 1)`.
    constexpr static vec_t<T, 2> one();
    //! Returns `(<T>::max, <T>::max)`.
    //! All elements are initialized to the largest representable value of the
    //! type T.
    constexpr static vec_t<T, 2> max();
    //! Returns `(<T>::lowest, <T>::lowest)`.
    //! All elements are initialized to the lowest representable value of the
    //! type T.
    //! \note This is equivalent to `std::numeric_limits<T>::lowest()`,
    //! _not_ `std::numeric_limits<T>::min()`. `std::numeric_limits<T>::min()`
    //! is the smallest representable value of type T.
    constexpr static vec_t<T, 2> min();

    T x; //!< Synonymous with elem[0] value.
    T y; //!< Synonymous with elem[1] value.

private:
    static T vec_t::*elem[size()];
};

template<typename T>
T vec_t<T, 2>::*vec_t<T, 2>::elem[size()] = {&vec_t<T, 2>::x, &vec_t<T, 2>::y};

using vec2_t = vec_t<real_t, 2>;
using vec2f_t = vec_t<float, 2>;
using vec2d_t = vec_t<double, 2>;
using vec2i_t = vec_t<int32_t, 2>;
using vec2l_t = vec_t<int64_t, 2>;

//! Partial template specialization of \ref vec_t for a three dimensional vector.
template<typename T>
struct vec_t<T, 3>
{
    using value_type = T;

    vec_t() noexcept = default;
    constexpr explicit vec_t(T xyz_);
    constexpr vec_t(const vec_t<T, 2>& xy_, T z_);
    constexpr vec_t(T x_, T y_, T z_);

    T& operator[](index_t i) &;
    const T& operator[](index_t i) const&;
    const T operator[](index_t i) &&;

    constexpr static index_t size();

    constexpr static vec_t<T, 3> axis_x(T len = T(1.0));
    constexpr static vec_t<T, 3> axis_y(T len = T(1.0));
    constexpr static vec_t<T, 3> axis_z(T len = T(1.0));
    constexpr static vec_t<T, 3> zero();
    constexpr static vec_t<T, 3> one();
    constexpr static vec_t<T, 3> max();
    constexpr static vec_t<T, 3> min();

    T x, y, z;

private:
    static T vec_t::*elem[size()];
};

template<typename T>
T vec_t<T, 3>::*vec_t<T, 3>::elem[size()] = {
    &vec_t<T, 3>::x, &vec_t<T, 3>::y, &vec_t<T, 3>::z};

using vec3_t = vec_t<real_t, 3>;
using vec3f_t = vec_t<float, 3>;
using vec3d_t = vec_t<double, 3>;
using vec3i_t = vec_t<int32_t, 3>;
using vec3l_t = vec_t<int64_t, 3>;

//! Partial template specialization of \ref vec_t for a four dimensional vector.
template<typename T>
struct vec_t<T, 4>
{
    using value_type = T;

    vec_t() noexcept = default;
    constexpr explicit vec_t(T xyzw_);
    constexpr vec_t(const vec_t<T, 3>& xyz_, T w_);
    constexpr vec_t(const vec_t<T, 2>& xy_, T z_, T w_);
    constexpr vec_t(const vec_t<T, 2>& xy_, const vec_t<T, 2>& zw);
    constexpr vec_t(T x_, T y_, T z_, T w_);

    T& operator[](index_t i) &;
    const T& operator[](index_t i) const&;
    const T operator[](index_t i) &&;

    constexpr static index_t size();

    constexpr static vec_t<T, 4> axis_x(T len = T(1.0));
    constexpr static vec_t<T, 4> axis_y(T len = T(1.0));
    constexpr static vec_t<T, 4> axis_z(T len = T(1.0));
    constexpr static vec_t<T, 4> axis_w(T len = T(1.0));
    constexpr static vec_t<T, 4> zero();
    constexpr static vec_t<T, 4> one();
    constexpr static vec_t<T, 4> max();
    constexpr static vec_t<T, 4> min();

    T x, y, z, w;

private:
    static T vec_t::*elem[size()];
};

template<typename T>
T vec_t<T, 4>::*vec_t<T, 4>::elem[size()] = {
    &vec_t<T, 4>::x, &vec_t<T, 4>::y, &vec_t<T, 4>::z, &vec_t<T, 4>::w};

using vec4_t = vec_t<real_t, 4>;
using vec4f_t = vec_t<float, 4>;
using vec4d_t = vec_t<double, 4>;
using vec4i_t = vec_t<int32_t, 4>;
using vec4l_t = vec_t<int64_t, 4>;

template<typename T, index_t n>
constexpr const vec_t<T, n> operator+(
    const vec_t<T, n>& lhs, const vec_t<T, n>& rhs);

template<>
constexpr const vec3_t operator+(const vec3_t& lhs, const vec3_t& rhs);

template<typename T, index_t n>
constexpr vec_t<T, n>& operator+=(vec_t<T, n>& lhs, const vec_t<T, n>& rhs);

template<>
constexpr vec3_t& operator+=(vec3_t& lhs, const vec3_t& rhs);

template<typename T, index_t n>
constexpr const vec_t<T, n> operator-(
    const vec_t<T, n>& lhs, const vec_t<T, n>& rhs);

template<>
constexpr const vec3_t operator-(const vec3_t& lhs, const vec3_t& rhs);

template<typename T, index_t n>
constexpr vec_t<T, n>& operator-=(vec_t<T, n>& lhs, const vec_t<T, n>& rhs);

template<>
constexpr vec3_t& operator-=(vec3_t& lhs, const vec3_t& rhs);

template<typename T, index_t n>
const vec_t<T, n> operator-(const vec_t<T, n>& rhs);

template<>
constexpr const vec3_t operator-(const vec3_t& rhs);

template<typename T, index_t n>
constexpr const vec_t<T, n> operator*(const vec_t<T, n>& lhs, T val);

template<>
constexpr const vec3_t operator*(const vec3_t& lhs, real_t val);

template<typename T, index_t n>
constexpr const vec_t<T, n> operator*(T val, const vec_t<T, n>& rhs);

template<>
constexpr const vec3_t operator*(real_t val, const vec3_t& rhs);

template<typename T, index_t n>
constexpr vec_t<T, n>& operator*=(vec_t<T, n>& lhs, T val);

template<>
constexpr vec3_t& operator*=(vec3_t& lhs, real_t val);

template<typename T, index_t n>
constexpr const vec_t<T, n> operator*(
    const vec_t<T, n>& lhs, const vec_t<T, n>& rhs);

template<>
constexpr const vec3_t operator*(const vec3_t& lhs, const vec3_t& rhs);

template<typename T, index_t n>
constexpr vec_t<T, n>& operator*=(vec_t<T, n>& lhs, const vec_t<T, n>& rhs);

template<>
constexpr vec3_t& operator*=(vec3_t& lhs, const vec3_t& rhs);

template<typename T, index_t n>
constexpr const vec_t<T, n> operator/(const vec_t<T, n>& lhs, T val);

template<>
constexpr const vec3_t operator/(const vec3_t& lhs, real_t val);

template<typename T, index_t n>
constexpr vec_t<T, n>& operator/=(vec_t<T, n>& lhs, T val);

template<>
constexpr vec3_t& operator/=(vec3_t& lhs, real_t val);

template<typename T, index_t n>
constexpr const vec_t<T, n> operator/(
    const vec_t<T, n>& lhs, const vec_t<T, n>& rhs);

template<>
constexpr const vec3_t operator/(const vec3_t& lhs, const vec3_t& rhs);

template<typename T, index_t n>
constexpr vec_t<T, n>& operator/=(vec_t<T, n>& lhs, const vec_t<T, n>& rhs);

template<>
constexpr vec3_t& operator/=(vec3_t& lhs, const vec3_t& rhs);

} // namespace as

#include "as-vec.inl"
