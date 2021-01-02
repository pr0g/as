//! \file
//! as-vec

#pragma once

#include <limits>
#include <type_traits>
#include <utility>

#include "as-types.hpp"
#include "as-iterator.hpp"

namespace as
{

//! A geometric vector class template parameterized by type and dimension.
template<typename T, index d>
struct vec
{
  //! Type alias for template parameter `T`.
  using value_type = T;

  vec() noexcept = default;

  template<typename...>
  struct typelist
  {
  };

  //! A variadic template constructor that accepts the same number of elements
  //! as the dimension of the vector.
  //! \note Passing the wrong number of elements will result in a compile
  //! error.
  template<
    typename... Args, typename = std::enable_if_t<!std::is_same<
                        typelist<vec>, typelist<std::decay_t<Args>...>>::value>>
  constexpr vec(Args... args) noexcept : elem{std::forward<Args>(args)...}
  {
    static_assert(
      sizeof...(args) == size(), "Incorrect number of arguments for dimension");
  }

  //! Returns a mutable reference to the value at the given index.
  //! \note Can only be called on a mutable lvalue object.
  //! \warning No bounds checking is performed.
  constexpr T& operator[](index i) &;
  //! Returns a const reference to the value at the given index.
  //! \note Can only be called on a const lvalue object.
  //! \warning No bounds checking is performed.
  constexpr const T& operator[](index i) const&;
  //! Returns a copy of the value at the given index.
  //! \note Can only be called on an rvalue object.
  //! \warning No bounds checking is performed.
  constexpr const T operator[](index i) &&;

  //! Returns the number of elements in the vector.
  constexpr static index size();

private:
  T elem[size()]; //!< Elements of the vector.
};

//! Partial template specialization of \ref vec for a two dimensional vector.
template<typename T>
struct vec<T, 2>
{
  //! Type alias for template parameter `T`.
  using value_type = T;

  vec() noexcept = default;

  //! Constructs vec with `(xy_, xy_)`.
  constexpr explicit vec(T xy_);
  //! Constructs vec with `(x_, y_)`.
  constexpr vec(T x_, T y_);

  //! Returns a mutable reference to the value at the given index.
  //! \note Can only be called on a mutable lvalue object.
  //! \warning No bounds checking is performed.
  T& operator[](index i) &;
  //! Returns a const reference to the value at the given index.
  //! \note Can only be called on a const lvalue object.
  //! \warning No bounds checking is performed.
  const T& operator[](index i) const&;
  //! Returns a copy of the value at the given index.
  //! \note Can only be called on an rvalue object.
  //! \warning No bounds checking is performed.
  const T operator[](index i) &&;

  //! Returns `2`.
  constexpr static index size();

  //! Returns `(x, 0)`.
  //! \param x Optional parameter for the length of the axis, defaults to 1.
  constexpr static vec<T, 2> axis_x(T x = T(1.0));
  //! Returns `(0, y)`.
  //! \param y Optional parameter for the length of the axis, defaults to 1.
  constexpr static vec<T, 2> axis_y(T y = T(1.0));
  //! Returns `(0, 0)`.
  constexpr static vec<T, 2> zero();
  //! Returns `(1, 1)`.
  constexpr static vec<T, 2> one();
  //! Returns <tt>(T\::max, T\::max)</tt>.
  //! All elements are initialized to the largest representable value of the
  //! type T.
  constexpr static vec<T, 2> max();
  //! Returns <tt>(T\::min, T\::min)</tt>.
  //! All elements are initialized to the smallest representable value of the
  //! type T.
  constexpr static vec<T, 2> min();
  //! Returns <tt>(T\::lowest, T\::lowest)</tt>.
  //! All elements are initialized to the lowest representable value of the
  //! type T.
  constexpr static vec<T, 2> lowest();

  T x; //!< Synonymous with `operator[](0)` value.
  T y; //!< Synonymous with `operator[](1)` value.

private:
  static T vec::*elem[size()];
};

template<typename T>
T vec<T, 2>::*vec<T, 2>::elem[size()] = {&vec<T, 2>::x, &vec<T, 2>::y};

//! Type alias for a two dimensional vector of type ::real.
using vec2 = vec<real, 2>;
//! Type alias for a two dimensional vector of type `float`.
using vec2f = vec<float, 2>;
//! Type alias for a two dimensional vector of type `double`.
using vec2d = vec<double, 2>;
//! Type alias for a two dimensional vector of type `int32_t`.
using vec2i = vec<int32_t, 2>;
//! Type alias for a two dimensional vector of type `int64_t`.
using vec2l = vec<int64_t, 2>;

//! Partial template specialization of \ref vec for a three dimensional
//! vector.
template<typename T>
struct vec<T, 3>
{
  //! Type alias for template parameter `T`.
  using value_type = T;

  vec() noexcept = default;

  //! Constructs vec with `(xyz_, xyz_, xyz_)`.
  constexpr explicit vec(T xyz_);
  //! Constructs vec with `(xy_.x, xy_.y, z_)`.
  constexpr vec(const vec<T, 2>& xy_, T z_ = T(0.0));
  //! Constructs vec with `(x_, y_, z_)`.
  constexpr vec(T x_, T y_, T z_);

  //! Returns a mutable reference to the value at the given index.
  //! \note Can only be called on a mutable lvalue object.
  //! \warning No bounds checking is performed.
  T& operator[](index i) &;
  //! Returns a const reference to the value at the given index.
  //! \note Can only be called on a const lvalue object.
  //! \warning No bounds checking is performed.
  const T& operator[](index i) const&;
  //! Returns a copy of the value at the given index.
  //! \note Can only be called on an rvalue object.
  //! \warning No bounds checking is performed.
  const T operator[](index i) &&;

  //! Returns `3`.
  constexpr static index size();

  //! Returns `(x, 0, 0)`.
  //! \param x Optional parameter for the length of the axis, defaults to 1.
  constexpr static vec<T, 3> axis_x(T x = T(1.0));
  //! Returns `(0, y, 0)`.
  //! \param y Optional parameter for the length of the axis, defaults to 1.
  constexpr static vec<T, 3> axis_y(T y = T(1.0));
  //! Returns `(0, 0, z)`.
  //! \param z Optional parameter for the length of the axis, defaults to 1.
  constexpr static vec<T, 3> axis_z(T z = T(1.0));
  //! Returns `(0, 0, 0)`.
  constexpr static vec<T, 3> zero();
  //! Returns `(1, 1, 1)`.
  constexpr static vec<T, 3> one();
  //! Returns <tt>(T\::max, T\::max, T\::max)</tt>.
  //! All elements are initialized to the largest representable value of the
  //! type T.
  constexpr static vec<T, 3> max();
  //! Returns <tt>(T\::min, T\::min, T\::min)</tt>.
  //! All elements are initialized to the smallest representable value of the
  //! type T.
  constexpr static vec<T, 3> min();
  //! Returns <tt>(T\::lowest, T\::lowest, T\::lowest)</tt>.
  //! All elements are initialized to the lowest representable value of the
  //! type T.
  constexpr static vec<T, 3> lowest();

  T x; //!< Synonymous with `operator[](0)` value.
  T y; //!< Synonymous with `operator[](1)` value.
  T z; //!< Synonymous with `operator[](2)` value.

private:
  static T vec::*elem[size()];
};

template<typename T>
T vec<T, 3>::*vec<T, 3>::elem[size()] = {
  &vec<T, 3>::x, &vec<T, 3>::y, &vec<T, 3>::z};

//! Type alias for a three dimensional vector of type ::real.
using vec3 = vec<real, 3>;
//! Type alias for a three dimensional vector of type `float`.
using vec3f = vec<float, 3>;
//! Type alias for a three dimensional vector of type `double`.
using vec3d = vec<double, 3>;
//! Type alias for a three dimensional vector of type `int32_t`.
using vec3i = vec<int32_t, 3>;
//! Type alias for a three dimensional vector of type `int64_t`.
using vec3l = vec<int64_t, 3>;

//! Partial template specialization of \ref vec for a four dimensional vector.
template<typename T>
struct vec<T, 4>
{
  //! Type alias for template parameter `T`.
  using value_type = T;

  vec() noexcept = default;

  //! Constructs vec with `(xyzw_, xyzw_, xyzw_, xyzw_)`.
  constexpr explicit vec(T xyzw_);
  //! Constructs vec with `(xyz_.x, xyz_.y, xyz_.z, w_)`.
  constexpr vec(const vec<T, 3>& xyz_, T w_ = T(0.0));
  //! Constructs vec with `(xy_.x, xy_.y, z_, w_)`.
  constexpr vec(const vec<T, 2>& xy_, T z_ = T(0.0), T w_ = T(0.0));
  //! Constructs vec with `(xy_.x, xy_.y, zw_.z, zw_.w)`.
  constexpr vec(const vec<T, 2>& xy_, const vec<T, 2>& zw_);
  //! Constructs vec with `(x_, y_, z_, w_)`.
  constexpr vec(T x_, T y_, T z_, T w_);

  //! Returns a mutable reference to the value at the given index.
  //! \note Can only be called on a mutable lvalue object.
  //! \warning No bounds checking is performed.
  T& operator[](index i) &;
  //! Returns a const reference to the value at the given index.
  //! \note Can only be called on a const lvalue object.
  //! \warning No bounds checking is performed.
  const T& operator[](index i) const&;
  //! Returns a copy of the value at the given index.
  //! \note Can only be called on an rvalue object.
  //! \warning No bounds checking is performed.
  const T operator[](index i) &&;

  //! Returns `4`.
  constexpr static index size();

  //! Returns `(x, 0, 0, 0)`.
  //! \param x Optional parameter for the length of the axis, defaults to 1.
  constexpr static vec<T, 4> axis_x(T x = T(1.0));
  //! Returns `(0, y, 0, 0)`.
  //! \param y Optional parameter for the length of the axis, defaults to 1.
  constexpr static vec<T, 4> axis_y(T y = T(1.0));
  //! Returns `(0, 0, z, 0)`.
  //! \param z Optional parameter for the length of the axis, defaults to 1.
  constexpr static vec<T, 4> axis_z(T z = T(1.0));
  //! Returns `(0, 0, 0, w)`.
  //! \param w Optional parameter for the length of the axis, defaults to 1.
  constexpr static vec<T, 4> axis_w(T w = T(1.0));
  //! Returns `(0, 0, 0, 0)`.
  constexpr static vec<T, 4> zero();
  //! Returns `(1, 1, 1, 1)`.
  constexpr static vec<T, 4> one();
  //! Returns <tt>(T\::max, T\::max, T\::max, T\::max)</tt>.
  //! All elements are initialized to the largest representable value of the
  //! type T.
  constexpr static vec<T, 4> max();
  //! Returns <tt>(T\::min, T\::min, T\::min, T\::min)</tt>.
  //! All elements are initialized to the smallest representable value of the
  //! type T.
  constexpr static vec<T, 4> min();
  //! Returns <tt>(T\::lowest, T\::lowest, T\::lowest, T\::lowest)</tt>.
  //! All elements are initialized to the lowest representable value of the
  //! type T.
  constexpr static vec<T, 4> lowest();

  T x; //!< Synonymous with `operator[](0)` value.
  T y; //!< Synonymous with `operator[](1)` value.
  T z; //!< Synonymous with `operator[](2)` value.
  T w; //!< Synonymous with `operator[](3)` value.

private:
  static T vec::*elem[size()];
};

template<typename T>
T vec<T, 4>::*vec<T, 4>::elem[size()] = {
  &vec<T, 4>::x, &vec<T, 4>::y, &vec<T, 4>::z, &vec<T, 4>::w};

//! Type alias for a four dimensional vector of type ::real.
using vec4 = vec<real, 4>;
//! Type alias for a four dimensional vector of type `float`.
using vec4f = vec<float, 4>;
//! Type alias for a four dimensional vector of type `double`.
using vec4d = vec<double, 4>;
//! Type alias for a four dimensional vector of type `int32_t`.
using vec4i = vec<int32_t, 4>;
//! Type alias for a four dimensional vector of type `int64_t`.
using vec4l = vec<int64_t, 4>;

//! Returns the sum of two vectors.
template<typename T, index d>
constexpr const vec<T, d> operator+(const vec<T, d>& lhs, const vec<T, d>& rhs);

//! Returns the sum of two vector twos.
template<>
constexpr const vec2 operator+(const vec2& lhs, const vec2& rhs);

//! Returns the sum of two vector threes.
template<>
constexpr const vec3 operator+(const vec3& lhs, const vec3& rhs);

//! Performs addition assignment of two vectors.
template<typename T, index d>
constexpr vec<T, d>& operator+=(vec<T, d>& lhs, const vec<T, d>& rhs);

//! Performs addition assignment of two vector threes.
template<>
constexpr vec3& operator+=(vec3& lhs, const vec3& rhs);

//! Returns the result of the right hand vector subtracted from the left hand
//! vector.
template<typename T, index d>
constexpr const vec<T, d> operator-(const vec<T, d>& lhs, const vec<T, d>& rhs);

//! Returns the result of the right hand vector two subtracted from the left
//! hand vector two.
template<>
constexpr const vec2 operator-(const vec2& lhs, const vec2& rhs);

//! Returns the result of the right hand vector three subtracted from the left
//! hand vector three.
template<>
constexpr const vec3 operator-(const vec3& lhs, const vec3& rhs);

//! Performs substraction assignment of two vectors.
template<typename T, index d>
constexpr vec<T, d>& operator-=(vec<T, d>& lhs, const vec<T, d>& rhs);

//! Performs substraction assignment of two vector threes.
template<>
constexpr vec3& operator-=(vec3& lhs, const vec3& rhs);

//! Returns the negation of a vector.
template<typename T, index d>
const vec<T, d> operator-(const vec<T, d>& rhs);

//! Returns the negation of a vector three.
template<>
constexpr const vec3 operator-(const vec3& rhs);

//! Returns a vector multiplied by a scalar quantity.
template<typename T, index d>
constexpr const vec<T, d> operator*(const vec<T, d>& lhs, T val);

//! Returns a vector three multiplied by a scalar quantity.
template<>
constexpr const vec3 operator*(const vec3& lhs, real val);

//! Returns a vector multiplied by a scalar quantity.
//! \note operator* overload with arguments switched.
template<typename T, index d>
constexpr const vec<T, d> operator*(T val, const vec<T, d>& rhs);

//! Returns a vector three multiplied by a scalar quantity.
//! \note operator* overload with arguments switched.
template<>
constexpr const vec3 operator*(real val, const vec3& rhs);

//! Performs a multiplication assignment of a vector and a scalar quantity.
template<typename T, index d>
constexpr vec<T, d>& operator*=(vec<T, d>& lhs, T val);

//! Performs a multiplication assignment of a vector three and a scalar
//! quantity. \note Template specialization.
template<>
constexpr vec3& operator*=(vec3& lhs, real val);

//! Returns a vector multiplied by another vector.
//! \note Elements are multiplied componentwise.
template<typename T, index d>
constexpr const vec<T, d> operator*(const vec<T, d>& lhs, const vec<T, d>& rhs);

//! Returns a vector three multiplied by another vector three.
//! \note Elements are multiplied componentwise.
template<>
constexpr const vec3 operator*(const vec3& lhs, const vec3& rhs);

//! Performs a multiplication assignment of two vectors.
//! \note Elements are multiplied componentwise.
template<typename T, index d>
constexpr vec<T, d>& operator*=(vec<T, d>& lhs, const vec<T, d>& rhs);

//! Performs a multiplication assignment of two vector threes.
//! \note Elements are multiplied componentwise.
template<>
constexpr vec3& operator*=(vec3& lhs, const vec3& rhs);

//! Returns a vector divided by a scalar quantity.
//! \note Elements are divided componentwise.
template<typename T, index d>
constexpr const vec<T, d> operator/(const vec<T, d>& lhs, T val);

//! Returns a vector three divided by a scalar quantity.
//! \note Elements are divided componentwise.
template<>
constexpr const vec3 operator/(const vec3& lhs, real val);

//! Performs a division assignment of two vectors.
template<typename T, index d>
constexpr vec<T, d>& operator/=(vec<T, d>& lhs, T val);

//! Performs a division assignment of two vector threes.
template<>
constexpr vec3& operator/=(vec3& lhs, real val);

//! Returns a vector divided by another vector.
//! \note Elements are divided componentwise.
template<typename T, index d>
constexpr const vec<T, d> operator/(const vec<T, d>& lhs, const vec<T, d>& rhs);

//! Returns a vector three divided by another vector three.
//! \note Elements are divided componentwise.
template<>
constexpr const vec3 operator/(const vec3& lhs, const vec3& rhs);

//! Performs a division assignment of two vectors.
template<typename T, index d>
constexpr vec<T, d>& operator/=(vec<T, d>& lhs, const vec<T, d>& rhs);

//! Performs a division assignment of two vector threes.
template<>
constexpr vec3& operator/=(vec3& lhs, const vec3& rhs);

//! Returns an iterator to the beginning of the vector.
template<typename T, index d>
constexpr subscript_iterator<vec<T, d>> begin(vec<T, d>& vec);

//! Returns an iterator to the end of the vector.
template<typename T, index d>
constexpr subscript_iterator<vec<T, d>> end(vec<T, d>& vec);

//! Returns an iterator to the beginning of the vector.
//! \note `const` overload
template<typename T, index d>
constexpr subscript_const_iterator<vec<T, d>> begin(const vec<T, d>& vec);

//! Returns an iterator to the end of the vector.
//! \note `const` overload
template<typename T, index d>
constexpr subscript_const_iterator<vec<T, d>> end(const vec<T, d>& vec);

//! Returns a const iterator to the beginning of the vector.
template<typename T, index d>
constexpr subscript_const_iterator<vec<T, d>> cbegin(const vec<T, d>& vec);

//! Returns a const iterator to the end of the vector.
template<typename T, index d>
constexpr subscript_const_iterator<vec<T, d>> cend(const vec<T, d>& vec);

} // namespace as

#include "as-vec.inl"
