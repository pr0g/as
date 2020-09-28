//! \file
//! as-point

#pragma once

#include "as-math.hpp"
#include "as-vec.hpp"

namespace as
{

//! A geometric point class template parameterized by type and dimension.
template<typename T, index d>
struct point
{
  // unused
};

//! Represents a two dimensional point.
//! A point provides many of the same operations as a vector but has a more
//! restrictive interface. It is geometrically very different from a vector and
//! can be used to increase type safety and prevent erroneous operations.
template<typename T>
struct point<T, 2>
{
  //! Type alias for template parameter `T`.
  using value_type = T;

  point<T, 2>() noexcept = default;

  //! Constructs point2 with `(xy_, xy_)`.
  constexpr explicit point<T, 2>(T xy_);
  //! Constructs point2 with `(xy_.x, xy_.y)`.
  constexpr explicit point<T, 2>(const vec<T, 2>& xy_);
  //! Constructs point2 with `(x_, y_)`.
  constexpr point<T, 2>(T x_, T y_);

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
  T operator[](index i) &&;

  //! Returns `2`.
  constexpr static index size();
  //! Returns `(0, 0)`.
  constexpr static point<T, 2> zero();
  //! Returns `(x, 0)`.
  //! \param x Optional parameter for the length of the axis, defaults to 1.
  constexpr static point<T, 2> axis_x(T x = T(1.0));
  //! Returns `(0, y)`.
  //! \param y Optional parameter for the length of the axis, defaults to 1.
  constexpr static point<T, 2> axis_y(T y = T(1.0));

  //! Returns a copy of the underlying vec2.
  //! \note Can only be called on an rvalue object.
  constexpr vec<T, 2> as_vec() &&;
  //! Returns a const reference to the underlying vec2.
  //! \note Can only be called on a const lvalue object.
  [[nodiscard]] constexpr const vec<T, 2>& as_vec() const&;

private:
  //! Returns the result of the right hand point2 subtracted from the left
  //! hand point2.
  friend constexpr const vec<T, 2> operator-(const point<T, 2>& lhs, const point<T, 2>& rhs);
  //! Returns the result of a vec2 added to a point2.
  friend constexpr const point<T, 2> operator+(const point<T, 2>& p, const vec<T, 2>& v);
  //! Performs addition assignment of a point2 and a vec2.
  friend constexpr point<T, 2>& operator+=(point<T, 2>& p, const vec<T, 2>& v);
  //! Returns the result of a vec2 subtracted from a point2.
  friend constexpr const point<T, 2> operator-(const point<T, 2>& p, const vec<T, 2>& v);
  //! Performs subtraction assignment of a point2 and a vec2.
  friend constexpr point<T, 2>& operator-=(point<T, 2>& p, const vec<T, 2>& v);
  //! Returns the negation of a point2.
  friend constexpr point<T, 2> operator-(const point<T, 2>& p);

  vec<T, 2> v; //!< point2 is implemented in terms of vec2.
};

//! Type alias for a two dimensional point of type ::real.
using point2 = point<real, 2>;
//! Type alias for a two dimensional point of type `float`.
using point2f = point<float, 2>;
//! Type alias for a two dimensional point of type `double`.
using point2d = point<double, 2>;
//! Type alias for a two dimensional point of type `int32_t`.
using point2i = point<int32_t, 2>;
//! Type alias for a two dimensional point of type `int64_t`.
using point2l = point<int64_t, 2>;

//! Represents a three dimensional point.
//! A point provides many of the same operations as a vector but has a more
//! restrictive interface. It is geometrically very different from a vector and
//! can be used to increase type safety and prevent erroneous operations.
template<typename T>
struct point<T, 3>
{
  //! Type alias for template parameter `T`.
  using value_type = T;

  point<T, 3>() noexcept = default;

  //! Constructs point3 with `(xyz_, xyz_, xyz_)`.
  constexpr explicit point<T, 3>(T xyz_);
  //! Constructs point3 with `(v_.x, v_.y, v_.z)`.
  constexpr explicit point<T, 3>(const vec<T, 3>& v_);
  //! Constructs point3 with `(x_, y_, z_)`.
  constexpr point<T, 3>(T x_, T y_, T z_);
  //! Constructs point3 with `(xy_.x, xy_.y, z_)`.
  constexpr point<T, 3>(const vec<T, 2>& xy_, T z_);

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
  T operator[](index i) &&;

  //! Returns `3`.
  constexpr static index size();

  //! Returns `(0, 0, 0)`.
  constexpr static point<T, 3> zero();
  //! Returns `(x, 0, 0)`.
  //! \param x Optional parameter for the length of the axis, defaults to 1.
  constexpr static point<T, 3> axis_x(T x = T(1.0));
  //! Returns `(0, y, 0)`.
  //! \param y Optional parameter for the length of the axis, defaults to 1.
  constexpr static point<T, 3> axis_y(T y = T(1.0));
  //! Returns `(0, 0, z)`.
  //! \param z Optional parameter for the length of the axis, defaults to 1.
  constexpr static point<T, 3> axis_z(T z = T(1.0));

  //! Returns a copy of the underlying vec3.
  //! \note Can only be called on an rvalue object.
  constexpr vec<T, 3> as_vec() &&;
  //! Returns a const reference to the underlying vec3.
  //! \note Can only be called on a const lvalue object.
  [[nodiscard]] constexpr const vec<T, 3>& as_vec() const&;

private:
  //! Returns the result of the right hand point3 subtracted from the left
  //! hand point3.
  friend constexpr const vec<T, 3> operator-(const point<T, 3>& lhs, const point<T, 3>& rhs);
  //! Returns the result of a vec3 added to a point3.
  friend constexpr const point<T, 3> operator+(const point<T, 3>& p, const vec<T, 3>& v);
  //! Performs addition assignment of a point3 and a vec3.
  friend constexpr point<T, 3>& operator+=(point<T, 3>& p, const vec<T, 3>& v);
  //! Returns the result of a vec3 subtracted from a point3.
  friend constexpr const point<T, 3> operator-(const point<T, 3>& p, const vec<T, 3>& v);
  //! Performs subtraction assignment of a point3 and a vec3.
  friend constexpr point<T, 3>& operator-=(point<T, 3>& p, const vec<T, 3>& v);
  //! Returns the negation of a point3.
  friend constexpr const point<T, 3> operator-(const point<T, 3>& p);

  vec<T, 3> v; //!< point3 is implemented in terms of vec3.
};

//! Type alias for a three dimensional point of type ::real.
using point3 = point<real, 3>;
//! Type alias for a three dimensional point of type `float`.
using point3f = point<float, 3>;
//! Type alias for a three dimensional point of type `double`.
using point3d = point<double, 3>;
//! Type alias for a three dimensional point of type `int32_t`.
using point3i = point<int32_t, 3>;
//! Type alias for a three dimensional point of type `int64_t`.
using point3l = point<int64_t, 3>;

} // namespace as

#include "as-point.inl"
