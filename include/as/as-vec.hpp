#pragma once

#include <limits>
#include <type_traits>
#include <utility>

#include "as-types.hpp"

//! \file
//! as-vec

namespace as
{

//! Geometric vector class template parameterized by type and dimension.
template<typename T, index_t n>
struct vec_t
{
    //! Type alias for template parameter `T`.
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

    //! Returns a mutable reference to the value at the given index.
    //! \note Can only be called on a mutable lvalue object.
    //! \warning No bounds checking is performed.
    constexpr T& operator[](index_t i) &;
    //! Returns a const reference to the value at the given index.
    //! \note Can only be called on a const lvalue object.
    //! \warning No bounds checking is performed.
    constexpr const T& operator[](index_t i) const&;
    //! Returns a copy of the value at the given index.
    //! \note Can only be called on an rvalue object.
    //! \warning No bounds checking is performed.
    constexpr const T operator[](index_t i) &&;

    //! Returns the number of elements in the vector.
    constexpr static index_t size();

private:
    T elem[size()];
};

//! Partial template specialization of \ref vec_t for a two dimensional vector.
template<typename T>
struct vec_t<T, 2>
{
    //! Type alias for template parameter `T`.
    using value_type = T;

    vec_t() noexcept = default;

    //! Constructs vec_t with `(xy_, xy_)`.
    constexpr explicit vec_t(T xy_);
    //! Constructs vec_t with `(x_, y_)`.
    constexpr vec_t(T x_, T y_);

    //! Returns a mutable reference to the value at the given index.
    //! \note Can only be called on a mutable lvalue object.
    //! \warning No bounds checking is performed.
    T& operator[](index_t i) &;
    //! Returns a const reference to the value at the given index.
    //! \note Can only be called on a const lvalue object.
    //! \warning No bounds checking is performed.
    const T& operator[](index_t i) const&;
    //! Returns a copy of the value at the given index.
    //! \note Can only be called on an rvalue object.
    //! \warning No bounds checking is performed.
    const T operator[](index_t i) &&;

    //! Returns `2`.
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

    T x; //!< Synonymous with `operator[](0)` value.
    T y; //!< Synonymous with `operator[](1)` value.

private:
    static T vec_t::*elem[size()];
};

template<typename T>
T vec_t<T, 2>::*vec_t<T, 2>::elem[size()] = {&vec_t<T, 2>::x, &vec_t<T, 2>::y};

//! Type alias for a two dimensional vector of type `real_t`
using vec2_t = vec_t<real_t, 2>;
//! Type alias for a two dimensional vector of type `float`
using vec2f_t = vec_t<float, 2>;
//! Type alias for a two dimensional vector of type `double`
using vec2d_t = vec_t<double, 2>;
//! Type alias for a two dimensional vector of type `int32_t`
using vec2i_t = vec_t<int32_t, 2>;
//! Type alias for a two dimensional vector of type `int64_t`
using vec2l_t = vec_t<int64_t, 2>;

//! Partial template specialization of \ref vec_t for a three dimensional vector.
template<typename T>
struct vec_t<T, 3>
{
    //! Type alias for template parameter `T`.
    using value_type = T;

    vec_t() noexcept = default;

    //! Constructs vec_t with `(xyz_, xyz_, xyz_)`.
    constexpr explicit vec_t(T xyz_);
    //! Constructs vec_t with `((x_, y_), z_)`.
    constexpr vec_t(const vec_t<T, 2>& xy_, T z_);
    //! Constructs vec_t with `(x_, y_, z_)`.
    constexpr vec_t(T x_, T y_, T z_);

    //! Returns a mutable reference to the value at the given index.
    //! \note Can only be called on a mutable lvalue object.
    //! \warning No bounds checking is performed.
    T& operator[](index_t i) &;
    //! Returns a const reference to the value at the given index.
    //! \note Can only be called on a const lvalue object.
    //! \warning No bounds checking is performed.
    const T& operator[](index_t i) const&;
    //! Returns a copy of the value at the given index.
    //! \note Can only be called on an rvalue object.
    //! \warning No bounds checking is performed.
    const T operator[](index_t i) &&;

    //! Returns `3`.
    constexpr static index_t size();

    //! Returns `(x, 0, 0)`.
    //! \param x Optional parameter for the length of the axis, defaults to 1.
    constexpr static vec_t<T, 3> axis_x(T x = T(1.0));
    //! Returns `(0, y, 0)`.
    //! \param y Optional parameter for the length of the axis, defaults to 1.
    constexpr static vec_t<T, 3> axis_y(T y = T(1.0));
    //! Returns `(0, 0, z)`.
    //! \param z Optional parameter for the length of the axis, defaults to 1.
    constexpr static vec_t<T, 3> axis_z(T z = T(1.0));
    //! Returns `(0, 0, 0)`.
    constexpr static vec_t<T, 3> zero();
    //! Returns `(1, 1, 1)`.
    constexpr static vec_t<T, 3> one();
    //! Returns `(<T>::max, <T>::max, <T>::max)`.
    constexpr static vec_t<T, 3> max();
    //! Returns `(<T>::lowest, <T>::lowest, <T>::lowest)`.
    constexpr static vec_t<T, 3> min();

    T x; //!< Synonymous with `operator[](0)` value.
    T y; //!< Synonymous with `operator[](1)` value.
    T z; //!< Synonymous with `operator[](2)` value.

private:
    static T vec_t::*elem[size()];
};

template<typename T>
T vec_t<T, 3>::*vec_t<T, 3>::elem[size()] = {
    &vec_t<T, 3>::x, &vec_t<T, 3>::y, &vec_t<T, 3>::z};

//! Type alias for a three dimensional vector of type `real_t`
using vec3_t = vec_t<real_t, 3>;
//! Type alias for a three dimensional vector of type `float`
using vec3f_t = vec_t<float, 3>;
//! Type alias for a three dimensional vector of type `double`
using vec3d_t = vec_t<double, 3>;
//! Type alias for a three dimensional vector of type `int32_t`
using vec3i_t = vec_t<int32_t, 3>;
//! Type alias for a three dimensional vector of type `int64_t`
using vec3l_t = vec_t<int64_t, 3>;

//! Partial template specialization of \ref vec_t for a four dimensional vector.
template<typename T>
struct vec_t<T, 4>
{
    //! Type alias for template parameter `T`.
    using value_type = T;

    vec_t() noexcept = default;

    //! Constructs vec_t with `(xyzw_, xyzw_, xyzw_, xyzw_)`.
    constexpr explicit vec_t(T xyzw_);
    //! Constructs vec_t with `((x_, y_, z_), w_)`.
    constexpr vec_t(const vec_t<T, 3>& xyz_, T w_);
    //! Constructs vec_t with `((x_, y_), z_, w_)`.
    constexpr vec_t(const vec_t<T, 2>& xy_, T z_, T w_);
    //! Constructs vec_t with `((x_, y_), (z_, w_))`.
    constexpr vec_t(const vec_t<T, 2>& xy_, const vec_t<T, 2>& zw_);
    //! Constructs vec_t with `(x_, y_, z_, w_)`.
    constexpr vec_t(T x_, T y_, T z_, T w_);

    //! Returns a mutable reference to the value at the given index.
    //! \note Can only be called on a mutable lvalue object.
    //! \warning No bounds checking is performed.
    T& operator[](index_t i) &;
    //! Returns a const reference to the value at the given index.
    //! \note Can only be called on a const lvalue object.
    //! \warning No bounds checking is performed.
    const T& operator[](index_t i) const&;
    //! Returns a copy of the value at the given index.
    //! \note Can only be called on an rvalue object.
    //! \warning No bounds checking is performed.
    const T operator[](index_t i) &&;

    //! Returns `4`.
    constexpr static index_t size();

    //! Returns `(x, 0, 0, 0)`.
    //! \param x Optional parameter for the length of the axis, defaults to 1.
    constexpr static vec_t<T, 4> axis_x(T len = T(1.0));
    //! Returns `(0, y, 0, 0)`.
    //! \param y Optional parameter for the length of the axis, defaults to 1.
    constexpr static vec_t<T, 4> axis_y(T len = T(1.0));
    //! Returns `(0, 0, z, 0)`.
    //! \param z Optional parameter for the length of the axis, defaults to 1.
    constexpr static vec_t<T, 4> axis_z(T len = T(1.0));
    //! Returns `(0, 0, 0, w)`.
    //! \param w Optional parameter for the length of the axis, defaults to 1.
    constexpr static vec_t<T, 4> axis_w(T len = T(1.0));
    //! Returns `(0, 0, 0, 0)`.
    constexpr static vec_t<T, 4> zero();
    //! Returns `(1, 1, 1, 1)`.
    constexpr static vec_t<T, 4> one();
    //! Returns `(<T>::max, <T>::max, <T>::max, <T>::max)`.
    constexpr static vec_t<T, 4> max();
    //! Returns `(<T>::lowest, <T>::lowest, <T>::lowest, <T>::lowest)`.
    constexpr static vec_t<T, 4> min();

    T x; //!< Synonymous with `operator[](0)` value.
    T y; //!< Synonymous with `operator[](1)` value.
    T z; //!< Synonymous with `operator[](2)` value.
    T w; //!< Synonymous with `operator[](3)` value.

private:
    static T vec_t::*elem[size()];
};

template<typename T>
T vec_t<T, 4>::*vec_t<T, 4>::elem[size()] = {
    &vec_t<T, 4>::x, &vec_t<T, 4>::y, &vec_t<T, 4>::z, &vec_t<T, 4>::w};

//! Type alias for a four dimensional vector of type `real_t`
using vec4_t = vec_t<real_t, 4>;
//! Type alias for a four dimensional vector of type `float`
using vec4f_t = vec_t<float, 4>;
//! Type alias for a four dimensional vector of type `double`
using vec4d_t = vec_t<double, 4>;
//! Type alias for a four dimensional vector of type `int32_t`
using vec4i_t = vec_t<int32_t, 4>;
//! Type alias for a four dimensional vector of type `int64_t`
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
